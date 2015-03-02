/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */



/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>

#include "globals.h"
#include "parser.h"
#include "basics.h"
#include "dfa.h"
#include "smart_ptr.h"

#define YYMALLOC malloc
#define YYFREE free

using namespace re2c;

extern "C"
{
int yylex();
void yyerror(const char*);
}

static re2c::uint       accept;
static re2c::RegExpMap  specMap;
static RegExp           *spec = NULL, *specNone = NULL;
static RuleOpList       specStar;
static Scanner          *in = NULL;
static Scanner::ParseMode  parseMode;
static SetupMap            ruleSetupMap;
static Token               *ruleDefault = NULL;
static DefaultMap          ruleDefaultMap;
static bool                foundRules;

/* Bison version 1.875 emits a definition that is not working
 * with several g++ version. Hence we disable it here.
 */
#if defined(__GNUC__)
#define __attribute__(x)
#endif

/* strdup() isn't standard C, so if we don't have it, we'll create our
 * own version
 */
#if !defined(HAVE_STRDUP)
static char* strdup(const char* s)
{
	char* rv = (char*)malloc(strlen(s) + 1);

	if (rv == NULL)
	{
		return NULL;
	}
	strcpy(rv, s);
	return rv;
}
#endif

void context_check(CondList *clist)
{
	if (!cFlag)
	{
		delete clist;
		in->fatal("conditions are only allowed when using -c switch");
	}
}

void context_none(CondList *clist)
{
	delete clist;
	context_check(NULL);
	in->fatal("no expression specified");
}

void context_rule(CondList *clist, RegExp *expr, RegExp *look, Str *newcond, Token *code)
{
	context_check(clist);
	const RegExp::InsAccess ins_access = clist->size() > 1
		? RegExp::PRIVATE
		: RegExp::SHARED;
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		//Str *condcpy = newcond ? new Str(*newcond) : newcond;
		Token *token = new Token(code, in->get_fname (), in->get_cline (), newcond);//condcpy);
		RuleOp *rule = new RuleOp(expr, look, token, accept++, ins_access);

		RegExpMap::iterator itRE = specMap.find(*it);

		if (itRE != specMap.end())
		{
			itRE->second.second = mkAlt(itRE->second.second, rule);
		}
		else
		{
			size_t nIndex = specMap.size() + 1; // 0 is reserved for "0"-spec
			assert( nIndex < 1u << 31);
			specMap[*it] = std::make_pair(int(nIndex), rule);
		}
		
	}
	delete clist;
	delete newcond;
	delete code;
}

void setup_rule(CondList *clist, Token *code)
{
	assert(clist);
	assert(code);
	context_check(clist);
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		if (ruleSetupMap.find(*it) != ruleSetupMap.end())
		{
			in->fatalf_at(code->line, "code to setup rule '%s' is already defined", it->c_str());
		}
		ruleSetupMap[*it] = std::make_pair(code->line, code->text.to_string());
	}
	delete clist;
	delete code;
}

void default_rule(CondList *clist, Token *code)
{
	assert(clist);
	assert(code);
	context_check(clist);
	for(CondList::const_iterator it = clist->begin(); it != clist->end(); ++it)
	{
		if (ruleDefaultMap.find(*it) != ruleDefaultMap.end())
		{
			in->fatalf_at(code->line, "code to default rule '%s' is already defined", it->c_str());
		}
		ruleDefaultMap[*it] = code;
	}
	delete clist;
}




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLOSESIZE = 258,
     CLOSE = 259,
     STAR = 260,
     NOCOND = 261,
     ID = 262,
     CODE = 263,
     RANGE = 264,
     STRING = 265,
     CONFIG = 266,
     VALUE = 267,
     NUMBER = 268,
     SETUP = 269,
     FID = 270
   };
#endif
/* Tokens.  */
#define CLOSESIZE 258
#define CLOSE 259
#define STAR 260
#define NOCOND 261
#define ID 262
#define CODE 263
#define RANGE 264
#define STRING 265
#define CONFIG 266
#define VALUE 267
#define NUMBER 268
#define SETUP 269
#define FID 270




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


	re2c::Symbol	*symbol;
	re2c::RegExp	*regexp;
	re2c::Token 	*token;
	char        	op;
	int         	number;
	re2c::ExtOp 	extop;
	re2c::Str   	*str;
	re2c::CondList	*clist;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNRULES -- Number of states.  */
#define YYNSTATES  97

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   270

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,    26,     2,     2,    22,     2,     2,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    21,    17,
      19,    16,    20,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    24,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    23,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    15,    18,    23,    27,
      32,    37,    41,    44,    52,    60,    67,    74,    80,    88,
      96,   103,   110,   116,   120,   124,   129,   134,   135,   137,
     139,   143,   144,   148,   149,   152,   154,   158,   160,   164,
     166,   169,   171,   174,   177,   179,   181,   184,   187,   189,
     191,   193
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      28,     0,    -1,    -1,    28,    30,    -1,    28,    29,    -1,
       7,    16,    35,    17,    -1,    15,    35,    -1,     7,    16,
      35,    18,    -1,    15,    35,    18,    -1,    11,    16,    12,
      17,    -1,    11,    16,    13,    17,    -1,    35,    34,     8,
      -1,     5,     8,    -1,    19,    31,    20,    35,    34,    33,
       8,    -1,    19,    31,    20,    35,    34,    21,    33,    -1,
      19,    31,    20,    34,    33,     8,    -1,    19,    31,    20,
      34,    21,    33,    -1,    19,    31,    20,     5,     8,    -1,
      19,     5,    20,    35,    34,    33,     8,    -1,    19,     5,
      20,    35,    34,    21,    33,    -1,    19,     5,    20,    34,
      33,     8,    -1,    19,     5,    20,    34,    21,    33,    -1,
      19,     5,    20,     5,     8,    -1,     6,    33,     8,    -1,
       6,    21,    33,    -1,    14,     5,    20,     8,    -1,    14,
      31,    20,     8,    -1,    -1,    32,    -1,     7,    -1,    32,
      22,     7,    -1,    -1,    16,    20,     7,    -1,    -1,    18,
      35,    -1,    36,    -1,    35,    23,    36,    -1,    37,    -1,
      36,    24,    37,    -1,    38,    -1,    37,    38,    -1,    40,
      -1,    40,    39,    -1,    40,     3,    -1,     4,    -1,     5,
      -1,    39,     4,    -1,    39,     5,    -1,     7,    -1,     9,
      -1,    10,    -1,    25,    35,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   181,   181,   183,   187,   191,   200,   209,   213,   217,
     223,   231,   240,   249,   253,   258,   263,   269,   273,   281,
     289,   294,   300,   306,   318,   330,   336,   344,   347,   354,
     359,   368,   371,   379,   382,   389,   393,   400,   404,   415,
     419,   426,   430,   445,   452,   456,   460,   464,   471,   479,
     483,   487
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLOSESIZE", "CLOSE", "STAR", "NOCOND",
  "ID", "CODE", "RANGE", "STRING", "CONFIG", "VALUE", "NUMBER", "SETUP",
  "FID", "'='", "';'", "'/'", "'<'", "'>'", "':'", "','", "'|'", "'\\\\'",
  "'('", "')'", "$accept", "spec", "decl", "rule", "cond", "clist",
  "newcond", "look", "expr", "diff", "term", "factor", "close", "primary", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,    61,    59,    47,    60,
      62,    58,    44,   124,    92,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    27,    28,    28,    28,    29,    29,    29,    29,    29,
      29,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    31,    31,    32,
      32,    33,    33,    34,    34,    35,    35,    36,    36,    37,
      37,    38,    38,    38,    39,    39,    39,    39,    40,    40,
      40,    40
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     4,     2,     4,     3,     4,
       4,     3,     2,     7,     7,     6,     6,     5,     7,     7,
       6,     6,     5,     3,     3,     4,     4,     0,     1,     1,
       3,     0,     3,     0,     2,     1,     3,     1,     3,     1,
       2,     1,     2,     2,     1,     1,     2,     2,     1,     1,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,    31,    48,    49,    50,     0,    27,
       0,    27,     0,     4,     3,    33,    35,    37,    39,    41,
      12,     0,    31,     0,     0,     0,     0,    29,     0,    28,
      48,     6,     0,     0,     0,     0,     0,     0,     0,    40,
      43,    44,    45,    42,     0,    24,    23,     0,     0,     0,
       0,     0,     0,     8,    33,    33,    51,    34,    36,    11,
      38,    46,    47,    32,     5,     7,     9,    10,    25,    26,
      30,     0,    31,    33,     0,    31,    33,    22,    31,     0,
      31,    17,    31,     0,    31,    21,    20,    31,     0,    16,
      15,    31,     0,    19,    18,    14,    13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    13,    14,    28,    29,    23,    37,    15,    16,
      17,    18,    43,    19
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yytype_int8 yypact[] =
{
     -37,     2,   -37,    -2,   -11,     9,   -37,   -37,    19,    73,
      13,    76,    13,   -37,   -37,     6,   -10,    13,   -37,    71,
     -37,    22,    39,    59,    13,    72,    57,   -37,    62,    48,
     -37,    16,    68,    69,    28,    13,    13,    83,    13,   -37,
     -37,   -37,   -37,    82,    85,   -37,   -37,    26,    77,    78,
      88,    89,    86,   -37,    23,    54,   -37,    67,   -10,   -37,
      13,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,    90,    15,     6,    91,    36,     6,   -37,    39,    92,
      50,   -37,    39,    93,    52,   -37,   -37,    39,    94,   -37,
     -37,    39,    95,   -37,   -37,   -37,   -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -37,    96,   -37,   -22,   -36,    -9,    70,
      66,   -13,   -37,   -37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      45,    31,     2,    34,    39,    21,    20,     3,     4,     5,
      22,     6,     7,     8,    38,    47,     9,    10,    72,    75,
      30,    11,     6,     7,    35,    24,    57,    12,    71,    36,
      30,    21,     6,     7,    53,    25,    78,    80,    12,    36,
      84,    35,    44,    64,    65,    73,    76,    39,    12,    36,
      79,    36,    21,    83,    56,    21,    85,    82,    88,    74,
      89,    30,    92,     6,     7,    93,    21,    46,    21,    95,
      52,    87,    35,    91,    40,    41,    42,    50,    26,    12,
      27,    32,    51,    27,    48,    49,    61,    62,    54,    55,
      36,    59,    63,    70,    66,    67,    68,    69,    77,    81,
      86,    90,    94,    96,    60,     0,    58,    33
};

static const yytype_int8 yycheck[] =
{
      22,    10,     0,    12,    17,    16,     8,     5,     6,     7,
      21,     9,    10,    11,    24,    24,    14,    15,    54,    55,
       7,    19,     9,    10,    18,    16,    35,    25,     5,    23,
       7,    16,     9,    10,    18,    16,    21,    73,    25,    23,
      76,    18,    20,    17,    18,    54,    55,    60,    25,    23,
      72,    23,    16,    75,    26,    16,    78,    21,    80,     5,
      82,     7,    84,     9,    10,    87,    16,     8,    16,    91,
      22,    21,    18,    21,     3,     4,     5,    20,     5,    25,
       7,     5,    20,     7,    12,    13,     4,     5,    20,    20,
      23,     8,     7,     7,    17,    17,     8,     8,     8,     8,
       8,     8,     8,     8,    38,    -1,    36,    11
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,     0,     5,     6,     7,     9,    10,    11,    14,
      15,    19,    25,    29,    30,    35,    36,    37,    38,    40,
       8,    16,    21,    33,    16,    16,     5,     7,    31,    32,
       7,    35,     5,    31,    35,    18,    23,    34,    24,    38,
       3,     4,     5,    39,    20,    33,     8,    35,    12,    13,
      20,    20,    22,    18,    20,    20,    26,    35,    36,     8,
      37,     4,     5,     7,    17,    18,    17,    17,     8,     8,
       7,     5,    34,    35,     5,    34,    35,     8,    21,    33,
      34,     8,    21,    33,    34,    33,     8,    21,    33,    33,
       8,    21,    33,    33,     8,    33,     8
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    {
		}
    break;

  case 3:

    {
			foundRules = true;
		}
    break;

  case 5:

    {
			if ((yyvsp[(1) - (4)].symbol)->re)
			{
				in->fatal("sym already defined");
			}
			(yyvsp[(3) - (4)].regexp)->ins_access = RegExp::PRIVATE;
			(yyvsp[(1) - (4)].symbol)->re = (yyvsp[(3) - (4)].regexp);
		}
    break;

  case 6:

    {
			if ((yyvsp[(1) - (2)].symbol)->re)
			{
				in->fatal("sym already defined");
			}
			(yyvsp[(2) - (2)].regexp)->ins_access = RegExp::PRIVATE;
			(yyvsp[(1) - (2)].symbol)->re = (yyvsp[(2) - (2)].regexp);
		}
    break;

  case 7:

    {
			in->fatal("trailing contexts are not allowed in named definitions");
		}
    break;

  case 8:

    {
			in->fatal("trailing contexts are not allowed in named definitions");
		}
    break;

  case 9:

    {
			in->config(*(yyvsp[(1) - (4)].str), *(yyvsp[(3) - (4)].str));
			delete (yyvsp[(1) - (4)].str);
			delete (yyvsp[(3) - (4)].str);
		}
    break;

  case 10:

    {
			in->config(*(yyvsp[(1) - (4)].str), (yyvsp[(3) - (4)].number));
			delete (yyvsp[(1) - (4)].str);
		}
    break;

  case 11:

    {
			if (cFlag)
			{
				in->fatal("condition or '<*>' required when using -c switch");
			}
			(yyval.regexp) = new RuleOp((yyvsp[(1) - (3)].regexp), (yyvsp[(2) - (3)].regexp), (yyvsp[(3) - (3)].token), accept++, RegExp::SHARED);
			spec = spec? mkAlt(spec, (yyval.regexp)) : (yyval.regexp);
		}
    break;

  case 12:

    {
			if (cFlag)
				in->fatal("condition or '<*>' required when using -c switch");
			if (ruleDefault != NULL)
				in->fatal("code to default rule is already defined");
			else
				ruleDefault = (yyvsp[(2) - (2)].token);
		}
    break;

  case 13:

    {
			context_rule((yyvsp[(2) - (7)].clist), (yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), (yyvsp[(6) - (7)].str), (yyvsp[(7) - (7)].token));
		}
    break;

  case 14:

    {
			assert((yyvsp[(7) - (7)].str));
			context_rule((yyvsp[(2) - (7)].clist), (yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), (yyvsp[(7) - (7)].str), NULL);
		}
    break;

  case 15:

    {
			context_none((yyvsp[(2) - (6)].clist));
			delete (yyvsp[(5) - (6)].str);
		}
    break;

  case 16:

    {
			assert((yyvsp[(6) - (6)].str));
			context_none((yyvsp[(2) - (6)].clist));
			delete (yyvsp[(6) - (6)].str);
		}
    break;

  case 17:

    {
			default_rule((yyvsp[(2) - (5)].clist), (yyvsp[(5) - (5)].token));
		}
    break;

  case 18:

    {
			context_check(NULL);
			Token *token = new Token((yyvsp[(7) - (7)].token), (yyvsp[(7) - (7)].token)->source, (yyvsp[(7) - (7)].token)->line, (yyvsp[(6) - (7)].str));
			delete (yyvsp[(7) - (7)].token);
			delete (yyvsp[(6) - (7)].str);
			specStar.push_back(new RuleOp((yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), token, accept++, RegExp::PRIVATE));
		}
    break;

  case 19:

    {
			assert((yyvsp[(7) - (7)].str));
			context_check(NULL);
			Token *token = new Token(NULL, in->get_fname (), in->get_cline (), (yyvsp[(7) - (7)].str));
			delete (yyvsp[(7) - (7)].str);
			specStar.push_back(new RuleOp((yyvsp[(4) - (7)].regexp), (yyvsp[(5) - (7)].regexp), token, accept++, RegExp::PRIVATE));
		}
    break;

  case 20:

    {
			context_none(NULL);
			delete (yyvsp[(5) - (6)].str);
		}
    break;

  case 21:

    {
			assert((yyvsp[(6) - (6)].str));
			context_none(NULL);
			delete (yyvsp[(6) - (6)].str);
		}
    break;

  case 22:

    {
			CondList *clist = new CondList();
			clist->insert("*");
			default_rule(clist, (yyvsp[(5) - (5)].token));
		}
    break;

  case 23:

    {
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			Token *token = new Token((yyvsp[(3) - (3)].token), (yyvsp[(3) - (3)].token)->source, (yyvsp[(3) - (3)].token)->line, (yyvsp[(2) - (3)].str));
			delete (yyvsp[(2) - (3)].str);
			delete (yyvsp[(3) - (3)].token);
			(yyval.regexp) = specNone = new RuleOp(new NullOp(), new NullOp(), token, accept++, RegExp::SHARED);
		}
    break;

  case 24:

    {
			assert((yyvsp[(3) - (3)].str));
			context_check(NULL);
			if (specNone)
			{
				in->fatal("code to handle illegal condition already defined");
			}
			Token *token = new Token(NULL, in->get_fname (), in->get_cline (), (yyvsp[(3) - (3)].str));
			delete (yyvsp[(3) - (3)].str);
			(yyval.regexp) = specNone = new RuleOp(new NullOp(), new NullOp(), token, accept++, RegExp::SHARED);
		}
    break;

  case 25:

    {
			CondList *clist = new CondList();
			clist->insert("*");
			setup_rule(clist, (yyvsp[(4) - (4)].token));
		}
    break;

  case 26:

    {
			setup_rule((yyvsp[(2) - (4)].clist), (yyvsp[(4) - (4)].token));
		}
    break;

  case 27:

    {
			in->fatal("unnamed condition not supported");
		}
    break;

  case 28:

    {
			(yyval.clist) = (yyvsp[(1) - (1)].clist);
		}
    break;

  case 29:

    {
			(yyval.clist) = new CondList();
			(yyval.clist)->insert((yyvsp[(1) - (1)].symbol)->GetName().to_string());
		}
    break;

  case 30:

    {
			(yyvsp[(1) - (3)].clist)->insert((yyvsp[(3) - (3)].symbol)->GetName().to_string());
			(yyval.clist) = (yyvsp[(1) - (3)].clist);
		}
    break;

  case 31:

    {
			(yyval.str) = NULL;
		}
    break;

  case 32:

    {
			(yyval.str) = new Str((yyvsp[(3) - (3)].symbol)->GetName().to_string().c_str());
		}
    break;

  case 33:

    {
			(yyval.regexp) = new NullOp;
		}
    break;

  case 34:

    {
			(yyval.regexp) = (yyvsp[(2) - (2)].regexp);
		}
    break;

  case 35:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		}
    break;

  case 36:

    {
			(yyval.regexp) = mkAlt((yyvsp[(1) - (3)].regexp), (yyvsp[(3) - (3)].regexp));
		}
    break;

  case 37:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		}
    break;

  case 38:

    {
			(yyval.regexp) = mkDiff((yyvsp[(1) - (3)].regexp), (yyvsp[(3) - (3)].regexp));
			if(!(yyval.regexp))
			{
				in->fatal("can only difference char sets");
			}
		}
    break;

  case 39:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		}
    break;

  case 40:

    {
			(yyval.regexp) = new CatOp((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].regexp));
		}
    break;

  case 41:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		}
    break;

  case 42:

    {
			switch((yyvsp[(2) - (2)].op))
			{
			case '*':
				(yyval.regexp) = mkAlt(new CloseOp((yyvsp[(1) - (2)].regexp)), new NullOp());
				break;
			case '+':
				(yyval.regexp) = new CloseOp((yyvsp[(1) - (2)].regexp));
				break;
			case '?':
				(yyval.regexp) = mkAlt((yyvsp[(1) - (2)].regexp), new NullOp());
				break;
			}
		}
    break;

  case 43:

    {
			(yyval.regexp) = new CloseVOp((yyvsp[(1) - (2)].regexp), (yyvsp[(2) - (2)].extop).minsize, (yyvsp[(2) - (2)].extop).maxsize);
		}
    break;

  case 44:

    {
			(yyval.op) = (yyvsp[(1) - (1)].op);
		}
    break;

  case 45:

    {
			(yyval.op) = (yyvsp[(1) - (1)].op);
		}
    break;

  case 46:

    {
			(yyval.op) = ((yyvsp[(1) - (2)].op) == (yyvsp[(2) - (2)].op)) ? (yyvsp[(1) - (2)].op) : '*';
		}
    break;

  case 47:

    {
			(yyval.op) = ((yyvsp[(1) - (2)].op) == (yyvsp[(2) - (2)].op)) ? (yyvsp[(1) - (2)].op) : '*';
		}
    break;

  case 48:

    {
			if(!(yyvsp[(1) - (1)].symbol)->re)
			{
				in->fatal("can't find symbol");
			}
			(yyval.regexp) = (yyvsp[(1) - (1)].symbol)->re;
		}
    break;

  case 49:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		}
    break;

  case 50:

    {
			(yyval.regexp) = (yyvsp[(1) - (1)].regexp);
		}
    break;

  case 51:

    {
			(yyval.regexp) = (yyvsp[(2) - (3)].regexp);
		}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}





extern "C" {
void yyerror(const char* s)
{
	in->fatal(s);
}

int yylex(){
	return in ? in->scan() : 0;
}
} // end extern "C"

namespace re2c
{

void parse(Scanner& i, Output & o)
{
	std::map<std::string, smart_ptr<DFA> >  dfa_map;
	ScannerState rules_state;

	in = &i;

	output_version_time (o.source.fragment ());
	output_line_info (o.source.fragment (), in->get_cline (), in->get_fname ().c_str ());

	Enc encodingOld = encoding;
	
	while ((parseMode = i.echo()) != Scanner::Stop)
	{
		o.source.new_block ();
		bool bPrologBrace = false;
		ScannerState curr_state;

		i.save_state(curr_state);
		foundRules = false;

		if (rFlag && parseMode == Scanner::Rules && dfa_map.size())
		{
			in->fatal("cannot have a second 'rules:re2c' block");
		}
		if (parseMode == Scanner::Reuse)
		{
			if (dfa_map.empty())
			{
				in->fatal("got 'use:re2c' without 'rules:re2c'");
			}
		}
		else if (parseMode == Scanner::Rules)
		{
			i.save_state(rules_state);
		}
		else
		{
			dfa_map.clear();
		}
		accept = 0;
		spec = NULL;
		ruleDefault = NULL;
		in->set_in_parse(true);
		yyparse();
		in->set_in_parse(false);
		if (rFlag && parseMode == Scanner::Reuse)
		{
			if (foundRules || encoding != encodingOld)
			{
				// Re-parse rules
				parseMode = Scanner::Parse;
				i.restore_state(rules_state);
				i.reuse();
				dfa_map.clear();
				parse_cleanup();
				spec = NULL;
				accept = 0;
				ruleDefault = NULL;
				in->set_in_parse(true);
				yyparse();
				in->set_in_parse(false);

				// Now append potential new rules
				i.restore_state(curr_state);
				parseMode = Scanner::Parse;
				in->set_in_parse(true);
				yyparse();
				in->set_in_parse(false);
			}
			encodingOld = encoding;
		}
		if (cFlag)
		{
			RegExpMap::iterator it;
			SetupMap::const_iterator itRuleSetup;
			DefaultMap::const_iterator itRuleDefault;

			if (parseMode != Scanner::Reuse)
			{
				if (!specStar.empty())
				{
					for (it = specMap.begin(); it != specMap.end(); ++it)
					{
						assert(it->second.second);
						for (RuleOpList::const_iterator itOp = specStar.begin(); itOp != specStar.end(); ++itOp)
						{
							it->second.second = mkAlt((*itOp)->copy(accept++), it->second.second);
						}
					}
				}
	
				if (specNone)
				{
					// After merging star rules merge none code to specmap
					// this simplifies some stuff.
					// Note that "0" inserts first, which is important.
					specMap["0"] = std::make_pair(0, specNone);
				}
				else
				{
					// We reserved 0 for specNone but it is not present,
					// so we can decrease all specs.
					for (it = specMap.begin(); it != specMap.end(); ++it)
					{
						it->second.first--;
					}
				}
			}

			size_t nCount = specMap.size();

			for (it = specMap.begin(); it != specMap.end(); ++it)
			{
				assert(it->second.second);

				if (parseMode != Scanner::Reuse)
				{
					itRuleSetup = ruleSetupMap.find(it->first);				
					if (itRuleSetup != ruleSetupMap.end())
					{
						yySetupRule = itRuleSetup->second.second;
					}
					else
					{
						itRuleSetup = ruleSetupMap.find("*");
						if (itRuleSetup != ruleSetupMap.end())
						{
							yySetupRule = itRuleSetup->second.second;
						}
						else
						{
							yySetupRule = "";
						}
					}
					itRuleDefault = ruleDefaultMap.find(it->first);
					if (itRuleDefault != ruleDefaultMap.end())
					{
						RuleOp * def = new RuleOp(in->mkDefault(), new NullOp(), itRuleDefault->second, accept++, RegExp::SHARED);
						it->second.second = it->second.second ? mkAlt(def, it->second.second) : def;
					}
					else
					{
						itRuleDefault = ruleDefaultMap.find("*");
						if (itRuleDefault != ruleDefaultMap.end())
						{
							RuleOp * def = new RuleOp(in->mkDefault(), new NullOp(), itRuleDefault->second, accept++, RegExp::SHARED);
							it->second.second = it->second.second ? mkAlt(def, it->second.second) : def;
						}
					}
					dfa_map[it->first] = genCode(it->second.second);
					dfa_map[it->first]->prepare(o.max_fill);
				}
				if (parseMode != Scanner::Rules && dfa_map.find(it->first) != dfa_map.end())
				{
					dfa_map[it->first]->emit(o, topIndent, &specMap, it->first, !--nCount, bPrologBrace);
				}
			}

			genTypes (o, specMap);
		}
		else
		{
			if (ruleDefault != NULL && parseMode != Scanner::Reuse)
			{
				RuleOp * def = new RuleOp(in->mkDefault(), new NullOp(), ruleDefault, accept++, RegExp::SHARED);
				spec = spec ? mkAlt(def, spec) : def;
			}
			if (spec || !dfa_map.empty())
			{
				if (parseMode != Scanner::Reuse)
				{
					dfa_map[""] = genCode(spec);
					dfa_map[""]->prepare(o.max_fill);
				}
				if (parseMode != Scanner::Rules && dfa_map.find("") != dfa_map.end())
				{
					dfa_map[""]->emit(o, topIndent, NULL, "", 0, bPrologBrace);
				}
			}
		}
		output_line_info (o.source.fragment (), in->get_cline (), in->get_fname ().c_str ());
		/* restore original char handling mode*/
		encoding = encodingOld;
	}

	if (cFlag)
	{
		SetupMap::const_iterator itRuleSetup;
		for (itRuleSetup = ruleSetupMap.begin(); itRuleSetup != ruleSetupMap.end(); ++itRuleSetup)
		{
			if (itRuleSetup->first != "*" && specMap.find(itRuleSetup->first) == specMap.end())
			{
				in->fatalf_at(itRuleSetup->second.first, "setup for non existing rule '%s' found", itRuleSetup->first.c_str());
			}
		}
		if (specMap.size() < ruleSetupMap.size())
		{
			uint line = in->get_cline();
			itRuleSetup = ruleSetupMap.find("*");
			if (itRuleSetup != ruleSetupMap.end())
			{
				line = itRuleSetup->second.first;
			}
			in->fatalf_at(line, "setup for all rules with '*' not possible when all rules are setup explicitly");
		}
	}

	parse_cleanup();
	in = NULL;
}

void parse_cleanup()
{
	RegExp::vFreeList.clear();
	Range::vFreeList.clear();
	Symbol::ClearTable();
	specMap.clear();
	specStar.clear();
	specNone = NULL;
}

} // end namespace re2c

