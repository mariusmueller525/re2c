/* Generated by re2c */

#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */

static void *read_file
    ( const char *fname
    , size_t unit
    , size_t padding
    , size_t *pfsize
    )
{
    void *buffer = NULL;
    size_t fsize = 0;

    /* open file */
    FILE *f = fopen(fname, "rb");
    if(f == NULL) {
        goto error;
    }

    /* get file size */
    fseek(f, 0, SEEK_END);
    fsize = (size_t) ftell(f) / unit;
    fseek(f, 0, SEEK_SET);

    /* allocate memory for file and padding */
    buffer = malloc(unit * (fsize + padding));
    if (buffer == NULL) {
        goto error;
    }

    /* read the whole file in memory */
    if (fread(buffer, unit, fsize, f) != fsize) {
        goto error;
    }

    fclose(f);
    *pfsize = fsize;
    return buffer;

error:
    fprintf(stderr, "error: cannot read file '%s'\n", fname);
    free(buffer);
    if (f != NULL) {
        fclose(f);
    }
    return NULL;
}

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYBACKUP() marker = cursor
#define YYRESTORE() cursor = marker
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_Normal
    ( unsigned *pkix
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const unsigned kix = *pkix;
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys[kix + 1];
    const YYKEYTYPE rule_exp = keys[kix + 2];
    *pkix = kix + 3;
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_Normal: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[kix];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_Normal: at position %ld (key %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , kix
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

static int check_key_count_line126_Normal(unsigned have, unsigned used, unsigned need)
{
    if (used + need <= have) return 0;
    fprintf(stderr, "error: lex_line126_Normal: not enough keys\n");
    return 1;
}

int lex_line126_Normal()
{
    const size_t padding = 4; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_Normal.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_Normal.keys"
        , sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && cursor < eof && i < keys_count;) {
        token = cursor;
        const YYCTYPE *marker = NULL;
        YYCTYPE yych;

        if (YYLESSTHAN (4)) YYFILL(4);
        yych = YYPEEK ();
        {
            static void *yytarget[256] = {
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy5, &&yy3, &&yy3, &&yy3, &&yy3, &&yy7,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy8,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy9,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3,
                &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3, &&yy3
            };
            goto *yytarget[yych];
        }
yy3:
        YYSKIP ();
yy4:
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 13);
        continue;
yy5:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 12);
        continue;
yy7:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '"') goto yy10;
        if (yych == '\\') goto yy12;
        goto yy4;
yy8:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '*') goto yy13;
        if (yych == '/') goto yy15;
        goto yy4;
yy9:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '?') goto yy17;
        goto yy4;
yy10:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\'') goto yy18;
yy11:
        YYRESTORE ();
        goto yy4;
yy12:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '"') goto yy10;
        goto yy11;
yy13:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 9);
        continue;
yy15:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 10);
        continue;
yy17:
        YYSKIP ();
        yych = YYPEEK ();
        {
            static void *yytarget[256] = {
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy20, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy22,
                &&yy24, &&yy26, &&yy11, &&yy11, &&yy11, &&yy28, &&yy11, &&yy30,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy32, &&yy34, &&yy36, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11,
                &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11, &&yy11
            };
            goto *yytarget[yych];
        }
yy18:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 11);
        continue;
yy20:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 7);
        continue;
yy22:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 6);
        continue;
yy24:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 0);
        continue;
yy26:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 1);
        continue;
yy28:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 8);
        continue;
yy30:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 5);
        continue;
yy32:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 2);
        continue;
yy34:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 4);
        continue;
yy36:
        YYSKIP ();
        status = check_key_count_line126_Normal(keys_count, i, 3)
             || action_line126_Normal(&i, keys, input, token, &cursor, 3);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_Normal: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_Normal: unused keys left after %u keys\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYFILL

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_Comment
    ( unsigned *pkix
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const unsigned kix = *pkix;
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys[kix + 1];
    const YYKEYTYPE rule_exp = keys[kix + 2];
    *pkix = kix + 3;
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_Comment: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[kix];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_Comment: at position %ld (key %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , kix
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

static int check_key_count_line126_Comment(unsigned have, unsigned used, unsigned need)
{
    if (used + need <= have) return 0;
    fprintf(stderr, "error: lex_line126_Comment: not enough keys\n");
    return 1;
}

int lex_line126_Comment()
{
    const size_t padding = 2; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_Comment.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_Comment.keys"
        , sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && cursor < eof && i < keys_count;) {
        token = cursor;
        YYCTYPE yych;

        if (YYLESSTHAN (2)) YYFILL(2);
        yych = YYPEEK ();
        if (yych == '*') goto yy43;
        YYSKIP ();
yy42:
        status = check_key_count_line126_Comment(keys_count, i, 3)
             || action_line126_Comment(&i, keys, input, token, &cursor, 1);
        continue;
yy43:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych != '/') goto yy42;
        YYSKIP ();
        status = check_key_count_line126_Comment(keys_count, i, 3)
             || action_line126_Comment(&i, keys, input, token, &cursor, 0);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_Comment: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_Comment: unused keys left after %u keys\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYLESSTHAN
#undef YYFILL

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYBACKUP() marker = cursor
#define YYRESTORE() cursor = marker
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_Skiptoeol
    ( unsigned *pkix
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const unsigned kix = *pkix;
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys[kix + 1];
    const YYKEYTYPE rule_exp = keys[kix + 2];
    *pkix = kix + 3;
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_Skiptoeol: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[kix];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_Skiptoeol: at position %ld (key %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , kix
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

static int check_key_count_line126_Skiptoeol(unsigned have, unsigned used, unsigned need)
{
    if (used + need <= have) return 0;
    fprintf(stderr, "error: lex_line126_Skiptoeol: not enough keys\n");
    return 1;
}

int lex_line126_Skiptoeol()
{
    const size_t padding = 5; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_Skiptoeol.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_Skiptoeol.keys"
        , sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && cursor < eof && i < keys_count;) {
        token = cursor;
        const YYCTYPE *marker = NULL;
        YYCTYPE yych;

        if (YYLESSTHAN (5)) YYFILL(5);
        yych = YYPEEK ();
        {
            static void *yytarget[256] = {
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy51, &&yy49, &&yy49, &&yy53, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy54,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy55, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49,
                &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49, &&yy49
            };
            goto *yytarget[yych];
        }
yy49:
        YYSKIP ();
yy50:
        status = check_key_count_line126_Skiptoeol(keys_count, i, 3)
             || action_line126_Skiptoeol(&i, keys, input, token, &cursor, 4);
        continue;
yy51:
        YYSKIP ();
        status = check_key_count_line126_Skiptoeol(keys_count, i, 3)
             || action_line126_Skiptoeol(&i, keys, input, token, &cursor, 3);
        continue;
yy53:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy56;
        goto yy50;
yy54:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '?') goto yy58;
        goto yy50;
yy55:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy60;
        if (yych == '\r') goto yy62;
        goto yy50;
yy56:
        YYSKIP ();
        status = check_key_count_line126_Skiptoeol(keys_count, i, 3)
             || action_line126_Skiptoeol(&i, keys, input, token, &cursor, 2);
        continue;
yy58:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '/') goto yy63;
yy59:
        YYRESTORE ();
        goto yy50;
yy60:
        YYSKIP ();
        status = check_key_count_line126_Skiptoeol(keys_count, i, 3)
             || action_line126_Skiptoeol(&i, keys, input, token, &cursor, 1);
        continue;
yy62:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy60;
        goto yy59;
yy63:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy64;
        if (yych == '\r') goto yy66;
        goto yy59;
yy64:
        YYSKIP ();
        status = check_key_count_line126_Skiptoeol(keys_count, i, 3)
             || action_line126_Skiptoeol(&i, keys, input, token, &cursor, 0);
        continue;
yy66:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy64;
        goto yy59;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_Skiptoeol: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_Skiptoeol: unused keys left after %u keys\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYFILL

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_String
    ( unsigned *pkix
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const unsigned kix = *pkix;
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys[kix + 1];
    const YYKEYTYPE rule_exp = keys[kix + 2];
    *pkix = kix + 3;
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_String: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[kix];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_String: at position %ld (key %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , kix
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

static int check_key_count_line126_String(unsigned have, unsigned used, unsigned need)
{
    if (used + need <= have) return 0;
    fprintf(stderr, "error: lex_line126_String: not enough keys\n");
    return 1;
}

int lex_line126_String()
{
    const size_t padding = 2; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_String.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.cgif--skeleton.c.line126_String.keys"
        , sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && cursor < eof && i < keys_count;) {
        token = cursor;
        YYCTYPE yych;

        if (YYLESSTHAN (2)) YYFILL(2);
        yych = YYPEEK ();
        if (yych == '"') goto yy72;
        if (yych == '\\') goto yy74;
        YYSKIP ();
yy71:
        status = check_key_count_line126_String(keys_count, i, 3)
             || action_line126_String(&i, keys, input, token, &cursor, 2);
        continue;
yy72:
        YYSKIP ();
        status = check_key_count_line126_String(keys_count, i, 3)
             || action_line126_String(&i, keys, input, token, &cursor, 1);
        continue;
yy74:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy71;
        YYSKIP ();
        status = check_key_count_line126_String(keys_count, i, 3)
             || action_line126_String(&i, keys, input, token, &cursor, 0);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_String: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_String: unused keys left after %u keys\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYLESSTHAN
#undef YYFILL

int main()
{
    if(lex_line126_Comment() != 0) {
        return 1;
    }
    if(lex_line126_Normal() != 0) {
        return 1;
    }
    if(lex_line126_Skiptoeol() != 0) {
        return 1;
    }
    if(lex_line126_String() != 0) {
        return 1;
    }
    return 0;
}
 	

***

'"'"'"
'\"'\"'\"
'\'\'\
'''
///
??????
???




??/
??/
??/
??????
???
\
\
\

                                                                                                                                                                                                                                                               