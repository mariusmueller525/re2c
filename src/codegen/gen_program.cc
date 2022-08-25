#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include <iomanip>

#include "config.h"
#include "src/codegen/code.h"
#include "src/codegen/helpers.h"
#include "src/msg/msg.h"
#include "src/msg/warn.h"
#include "src/options/opt.h"
#include "src/encoding/enc.h"
#include "src/util/check.h"
#include "src/util/file_utils.h"
#include "src/util/string_utils.h"

namespace re2c {

static uint32_t write_converting_newlines(const std::string& str, FILE* f) {
    const char* s = str.c_str(), *e = s + str.length();
    uint32_t lines = 0;

    // In order to maintain consistency we convert all newlines to LF when writing output to file.
    // Some newlines originate in user-defined code (including semantic actions and code fragments
    // in configurations and directives), and some are generated by re2c itself.
    for (const char* p = s;; ++p) {
        size_t l = static_cast<size_t>(p - s);
        if (p == e) {
            fwrite(s, 1, l, f);
            break;
        } else if (*p == '\n') {
            ++lines;
            if (p > s && p[-1] == '\r') --l;
            fwrite(s, 1, l, f);
            s = p;
        }
    }

    return lines;
}

OutputBlock::OutputBlock(InputBlock kind, const std::string& name, const loc_t& loc)
    : kind(kind),
      name(name),
      loc(loc),
      fragments(),
      used_yyaccept(false),
      have_user_code(false),
      conds(),
      stags(),
      mtags(),
      opts(nullptr),
      max_fill(1),
      max_nmatch(1),
      start_label(nullptr),
      fill_index(0),
      fill_state(0),
      fill_goto() {}

OutputBlock::~OutputBlock() {
    delete opts;
}

Output::Output(Msg& msg)
    : cblocks(),
      hblocks(),
      pblocks(&cblocks),
      label_counter(0),
      state_goto(false),
      cond_enum_autogen(true),
      cond_goto(false),
      warn_condition_order(true),
      need_header(false),
      done_mtag_defs(false),
      msg(msg),
      skeletons(),
      allocator(),
      scratchbuf(allocator),
      total_fill_index(0),
      total_opts(nullptr) {}

Output::~Output() {
    for (OutputBlock* b : cblocks) delete b;
    for (OutputBlock* b : hblocks) delete b;
}

void Output::header_mode(bool on) {
    pblocks = on ? &hblocks : &cblocks;
}

bool Output::in_header() const {
    return pblocks == &hblocks;
}

OutputBlock& Output::block() {
    return *pblocks->back();
}

void Output::wraw(const uint8_t* s, const uint8_t* e, bool newline) {
    if (s != e && block().opts->target == Target::CODE) {
        // scan for non-whitespace characters
        bool& code = block().have_user_code;
        for (const uint8_t* p = s; !code && p < e; ++p) {
            code = !isspace(*p);
        }
        wdelay_stmt(0, code_raw(allocator, s, static_cast<size_t>(e - s)));
    }
    if (newline && e > s && e[-1] != '\n') {
        // Insert newline unless the block ends in a newline.
        wdelay_stmt(0, code_newline(allocator));
    }
}

void Output::wversion_time() {
    output_version_time(scratchbuf.stream(), block().opts);
    wdelay_stmt(0, code_textraw(allocator, scratchbuf.flush()));
}

void Output::wdelay_stmt(uint32_t ind, Code* stmt) {
    block().fragments.push_back({stmt, ind});
}

Ret Output::new_block(Opt& opts, InputBlock kind, std::string name, const loc_t& loc) {
    // Prefix autogenerated names with a special symbol to avoid collision with user-defined names.
    // Embed line information in the autogenerated name to make it easier to correlate names with
    // source code.
    if (kind == InputBlock::USE) {
        // `use:re2c` blocks have autogenerated names that differ from the name of the `rules:re2c`
        // block that they are using, so the user cannot reference a `use:re2c` block in any way.
        // (They can easily achieve the same goal with the help of the `!use` directive in a normal
        // block.)
        name = "#line_" + to_string(loc.line) + "_block_use_" + name;
    } else if (name.empty()) {
        // Append block number, as the line may be non-unique (it is possible to have multiple
        // blocks on the same line, included files may define blocks at the same line, and line
        // directives may reset line number).
        name = "#line_" + to_string(loc.line) + "_block_" + to_string(pblocks->size());
    }

    // Check that the new block has a unique name.
    for (const OutputBlock* b : *pblocks) {
        if (b->name == name) {
            RET_FAIL(msg.error(loc,
                               "block named '%s' is already defined on line %u",
                               name.c_str(), b->loc.line));
        }
    }

    OutputBlock* block = new OutputBlock(kind, name, loc);
    pblocks->push_back(block);

    CHECK_RET(opts.snapshot(block->opts));

    block->fill_index = total_fill_index;

    // start label hapens to be the only option that must be reset for each new block
    opts.reset_group_label_start();

    return Ret::OK;
}

void Output::gather_info_from_block() {
    DCHECK(!pblocks->empty());
    const OutputBlock* b = pblocks->back();
    total_fill_index = b->fill_index;
}

static void fix_first_block_opts(const blocks_t& blocks) {
    // If the initial block contains only whitespace and no user code, then re2c options specified
    // in the first re2c block are also applied to the initial block.
    if (blocks.size() >= 2) {
        const OutputBlock* fst = blocks[0], *snd = blocks[1];
        if (!fst->have_user_code) {
            *const_cast<opt_t*>(fst->opts) = *snd->opts;
        }
    }
}

Ret Output::emit_blocks(const std::string& fname, const CodegenCtxGlobal& globalctx) {
    const blocks_t& blocks = *globalctx.pblocks;

    fix_first_block_opts(blocks);

    // First code generation pass: expand all delayed code blocks except labels. Labels need to wait
    // until the next pass because the first pass may add transitions to previously unused labels
    // (e.g. start label of a block that is specified in a `getstate:re2c` directive).
    for (const OutputBlock* b : blocks) {
        CodegenCtxPass1 gctx = {&globalctx, b};
        for (const OutputFragment& f : b->fragments) {
            CHECK_RET(expand_pass_1(gctx, f.code));
        }
    }

    FILE* file = nullptr, *temp = nullptr;
    std::string filename = fname, tempname = fname;

    if (filename.empty()) {
        filename = "<stdout>";
        file = stdout;
    } else if ((temp = temp_file(tempname))) {
        file = temp;
    } else if (!(file = fopen(filename.c_str(), "w"))) {
        RET_FAIL(error("cannot open output file %s", filename.c_str()));
    }
    filename = escape_backslashes(filename);

    // Second code generation pass: expand labels, combine/simplify statements, convert newlines,
    // write the generated code to a file.
    unsigned int line_count = 1;
    for (const OutputBlock* b : blocks) {
        CodegenCtxPass2 gctx = {allocator, scratchbuf, b->opts};

        for (const OutputFragment& f : b->fragments) {
            std::ostringstream os;
            RenderContext rctx = {os, b->opts, msg, f.indent, filename.c_str(), line_count};

            expand_pass_2(gctx, f.code);
            remove_empty(gctx, f.code);
            combine(gctx, f.code);
            render(rctx, f.code);
            write_converting_newlines(os.str(), file);
        }
    }

    fclose(file);
    if (temp && !overwrite_file(tempname.c_str(), fname.c_str())) {
        error("cannot rename or write temporary file %s to output file %s",
              tempname.c_str(),
              fname.c_str());
        remove(tempname.c_str());
        return Ret::FAIL;
    }
    return Ret::OK;
}

Ret Output::emit() {
    CHECK_RET(msg.warn.check());

    CodegenCtxGlobal ctx = {allocator,
                            scratchbuf,
                            msg,
                            total_opts,
                            cblocks,
                            hblocks,
                            /*pblocks*/ nullptr,
                            /*tmpblocks*/ blocks_t(),
                            warn_condition_order};

    // global options are last block's options
    const opt_t* opts = block().opts;

    // Emit header file.
    if (!opts->header_file.empty() || need_header) {
        if (opts->start_conditions && this->cond_enum_autogen) {
            // Old-style -t, --type-headers usage implies condition enum.
            header_mode(true);
            wdelay_stmt(0, code_newline(allocator));
            wdelay_stmt(0, code_fmt(allocator, CodeKind::COND_ENUM, nullptr, nullptr, nullptr));
            header_mode(false);
        }
        ctx.pblocks = &hblocks;
        CHECK_RET(emit_blocks(opts->header_file, ctx));
    }

    // Emit output file.
    ctx.pblocks = &cblocks;
    return emit_blocks(opts->output_file, ctx);
}

void output_version_time(std::ostream& os, const opt_t* opts) {
    os << (opts->lang == Lang::GO ? "// Code generated" : "/* Generated") << " by re2c";
    if (opts->version) {
        os << " " << PACKAGE_VERSION;
    }
    if (opts->date) {
        os << " on ";
        time_t now = time(nullptr);
        os.write(ctime(&now), 24);
    }
    os << (opts->lang == Lang::GO ? ", DO NOT EDIT." : " */");
}

Scratchbuf& Scratchbuf::yybm_char(uint32_t u, const opt_t* opts, int width) {
    if (opts->bitmaps_hex) {
        print_hex(os, u, opts->encoding.cunit_size());
    } else {
        u32_width(u, width);
    }
    return *this;
}

Scratchbuf& Scratchbuf::u32_width(uint32_t u, int width) {
    os << std::setw(width);
    os << u;
    return *this;
}

Scratchbuf& Scratchbuf::exact_uint(size_t width) {
    if (width == sizeof(char)) {
        os << "unsigned char";
    } else if (width == sizeof(short)) {
        os << "unsigned short";
    } else if (width == sizeof(int)) {
        os << "unsigned int";
    } else if (width == sizeof(long)) {
        os << "unsigned long";
    } else {
        os << "uint" << width * 8 << "_t";
    }
    return *this;
}

const char* Scratchbuf::flush() {
    const size_t len = os.str().length();
    char* e = alc.alloct<char>(len + 1);
    memcpy(e, os.str().c_str(), len);
    e[len] = 0;
    os.str("");
    return e;
}

} // namespace re2c
