/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "./src/parser.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include "./dataset.h"
#include "lex.yy.c"
// #define YYDEBUG 1

//  #define YY_USER_ACTION                                  \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn;                  \
        yylloc.last_column = yycolumn + yyleng - 1;      \
        yycolumn += yyleng;


int yylex(void);
void yyerror(char *);

TNode* AST__ = NULL;
unsigned syn_error = 0;

// .y文件进行语法分析，通过产生式匹配，如果当前行匹配成功执行后面的函数

#line 89 "./src/syntex.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntex.tab.h".  */
#ifndef YY_YY_SRC_SYNTEX_TAB_H_INCLUDED
# define YY_YY_SRC_SYNTEX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE = 258,
    STRUCT = 259,
    RETURN = 260,
    IF = 261,
    ELSE = 262,
    WHILE = 263,
    ID = 264,
    SEMI = 265,
    COMMA = 266,
    RELOP = 267,
    ASSIGNOP = 268,
    PLUS = 269,
    MINUS = 270,
    STAR = 271,
    DIV = 272,
    AND = 273,
    OR = 274,
    DOT = 275,
    NOT = 276,
    LP = 277,
    RP = 278,
    LB = 279,
    RB = 280,
    LC = 281,
    RC = 282,
    INT = 283,
    FLOAT = 284,
    UMINUS = 285,
    LOWER_THAN_ELSE = 286
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "./src/parser.y" /* yacc.c:355  */

  TNode* t_node;

#line 165 "./src/syntex.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SRC_SYNTEX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 196 "./src/syntex.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   249

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    61,    62,    64,    65,    66,    67,    68,
      69,    70,    72,    73,    77,    78,    80,    81,    83,    84,
      86,    90,    91,    94,    95,    96,    98,    99,   101,   105,
     106,   108,   109,   111,   112,   113,   114,   115,   116,   118,
     119,   120,   124,   125,   127,   128,   130,   131,   133,   134,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   158,   159
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "STRUCT", "RETURN", "IF", "ELSE",
  "WHILE", "ID", "SEMI", "COMMA", "RELOP", "ASSIGNOP", "PLUS", "MINUS",
  "STAR", "DIV", "AND", "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC",
  "RC", "INT", "FLOAT", "UMINUS", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
# endif

#define YYPACT_NINF -76

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-76)))

#define YYTABLE_NINF -33

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     232,     9,   -76,    57,    63,   -76,   232,    81,   -76,   -76,
      49,    60,   -76,   -76,   -76,     7,    75,   -76,    82,   -10,
      21,   117,    72,   -76,   117,   -76,    70,   -76,    95,   105,
      72,   -76,   -76,    97,    83,   117,   -76,    50,   -76,    95,
     111,   124,   -76,   -76,   122,   138,    -1,   150,   151,   -76,
     -76,    54,    74,    10,    20,   127,    74,    74,    74,   -76,
     -76,   -76,   134,    50,    99,   163,   -76,   117,   -76,   -76,
      74,   -76,    95,   -76,   112,   167,    74,    79,    74,    39,
      -4,    -4,   153,   -76,   -76,   -76,    74,    74,    74,    74,
      74,    74,    74,    74,   191,    74,   -76,   192,   -76,   -76,
      79,   166,   -76,   179,   -76,   126,   152,   -76,   225,   192,
      33,    33,    -4,    -4,   214,   203,   -76,   139,   -76,    79,
      79,    74,   -76,   -76,   181,   -76,   -76,    79,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    14,    19,     0,     2,     0,     0,    15,    11,
      20,     0,    17,     1,     3,     0,    21,     6,     0,    12,
       0,    43,     0,    25,    43,     9,     0,     5,     0,     0,
      10,     8,     7,     0,     0,    43,    30,     0,    24,     0,
       0,    27,    21,    13,     0,     0,    48,     0,    46,    16,
      42,     0,     0,     0,     0,    65,     0,     0,     0,    66,
      67,    34,     0,     0,     0,    28,    23,     0,    22,    45,
       0,    44,     0,    39,     0,     0,     0,     0,     0,     0,
      59,    60,     0,    29,    31,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    49,    47,    35,
       0,     0,    41,     0,    62,    69,     0,    58,    53,    50,
      54,    55,    56,    57,    51,    52,    64,     0,    40,     0,
       0,     0,    61,    63,    36,    38,    68,     0,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   195,   -76,   185,     3,   -76,   -76,   -76,   -26,
     -76,   147,   -76,    -5,   159,   -75,    -7,   -76,   165,   -76,
     -52,   103
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    33,     8,    11,    12,    19,
      20,    40,    41,    61,    62,    63,    34,    35,    47,    48,
      64,   106
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    28,   102,     7,    80,    81,    82,    46,    22,     7,
      25,    75,    70,    65,    29,    32,    94,    37,    97,     9,
      95,    77,    30,    29,   101,   118,   103,   105,    50,    39,
      23,    31,    76,    24,   108,   109,   110,   111,   112,   113,
     114,   115,    78,   117,   124,   125,    46,    24,    55,    90,
      91,    51,   128,    94,    56,    52,    53,    95,    54,    55,
      57,    58,   104,    13,    73,    56,    10,    59,    60,   105,
      39,    57,    58,     2,     3,   -18,    24,   -32,    59,    60,
      51,    36,    15,    55,    52,    53,    21,    54,    55,    56,
      16,    17,    27,    38,    56,    57,    58,    26,    45,    36,
      57,    58,    59,    60,    42,    24,    42,    59,    60,    85,
      49,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       2,     3,    99,    95,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    44,    66,    67,    95,   121,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    68,    69,    79,
      95,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      71,    83,    72,    95,   123,    86,    87,    88,    89,    90,
      91,    92,    93,    94,   100,   122,   107,    95,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    29,   127,   119,
      95,    86,    87,    88,    89,    90,    91,    92,    93,    94,
     116,    14,   120,    95,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    43,    96,    86,    95,    88,    89,    90,
      91,    92,    84,    94,   126,     0,    86,    95,    88,    89,
      90,    91,    -4,     1,    94,     2,     3,    98,    95,    88,
      89,    90,    91,     0,     0,    94,     0,     0,     0,    95
};

static const yytype_int8 yycheck[] =
{
      52,    11,    77,     0,    56,    57,    58,    33,     1,     6,
      15,     1,    13,    39,    24,    20,    20,    24,    70,    10,
      24,     1,     1,    24,    76,   100,    78,    79,    35,    26,
      23,    10,    22,    26,    86,    87,    88,    89,    90,    91,
      92,    93,    22,    95,   119,   120,    72,    26,     9,    16,
      17,     1,   127,    20,    15,     5,     6,    24,     8,     9,
      21,    22,    23,     0,    10,    15,     9,    28,    29,   121,
      67,    21,    22,     3,     4,    26,    26,    27,    28,    29,
       1,    27,     1,     9,     5,     6,    26,     8,     9,    15,
       9,    10,    10,    23,    15,    21,    22,    22,     1,    27,
      21,    22,    28,    29,     9,    26,     9,    28,    29,    10,
      27,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       3,     4,    10,    24,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    28,    23,    11,    24,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    25,    10,    22,
      24,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      10,    27,    11,    24,    25,    12,    13,    14,    15,    16,
      17,    18,    19,    20,     7,    23,    23,    24,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    24,     7,    23,
      24,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       9,     6,    23,    24,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    28,    67,    12,    24,    14,    15,    16,
      17,    18,    63,    20,   121,    -1,    12,    24,    14,    15,
      16,    17,     0,     1,    20,     3,     4,    72,    24,    14,
      15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    33,    34,    35,    37,    38,    10,
       9,    39,    40,     0,    34,     1,     9,    10,    36,    41,
      42,    26,     1,    23,    26,    45,    22,    10,    11,    24,
       1,    10,    45,    37,    48,    49,    27,    48,    23,    37,
      43,    44,     9,    36,    28,     1,    41,    50,    51,    27,
      48,     1,     5,     6,     8,     9,    15,    21,    22,    28,
      29,    45,    46,    47,    52,    41,    23,    11,    25,    10,
      13,    10,    11,    10,    52,     1,    22,     1,    22,    22,
      52,    52,    52,    27,    46,    10,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    24,    43,    52,    50,    10,
       7,    52,    47,    52,    23,    52,    53,    23,    52,    52,
      52,    52,    52,    52,    52,    52,     9,    52,    47,    23,
      23,    11,    23,    25,    47,    47,    53,     7,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      35,    35,    36,    36,    37,    37,    38,    38,    39,    39,
      40,    41,    41,    42,    42,    42,    43,    43,    44,    45,
      45,    46,    46,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     3,
       3,     2,     1,     3,     1,     1,     5,     2,     1,     0,
       1,     1,     4,     4,     3,     2,     3,     1,     2,     4,
       2,     2,     0,     2,     1,     3,     5,     7,     5,     2,
       4,     3,     2,     0,     3,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     4,     3,     1,     1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 59 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode((yyvsp[0].t_node)?((yyvsp[0].t_node))->no_line:0, Program_, NULL); add_child((yyval.t_node), (yyvsp[0].t_node)); if(lex_error == 0 && syn_error == 0) AST__ = (yyval.t_node); }
#line 1473 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 61 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, ExtDefList_, NULL); add_child((yyval.t_node), (yyvsp[-1].t_node)); add_child( (yyval.t_node),  (yyvsp[0].t_node));}
#line 1479 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 62 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = NULL;}
#line 1485 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 64 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, ExtDef_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1491 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 65 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, ExtDef_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1497 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 66 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, ExtDef_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1503 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 67 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, ExtDef_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1509 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 68 "./src/parser.y" /* yacc.c:1646  */
    {syn_error = 1;}
#line 1515 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 69 "./src/parser.y" /* yacc.c:1646  */
    {syn_error = 1;}
#line 1521 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 70 "./src/parser.y" /* yacc.c:1646  */
    {syn_error = 1;}
#line 1527 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 72 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, ExtDecList_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1533 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 73 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, ExtDecList_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1539 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 77 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Specifier_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1545 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 78 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Specifier_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1551 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 80 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-4].t_node))->no_line, StructSpecifier_, NULL); add_child((yyval.t_node),  (yyvsp[-4].t_node));add_child((yyval.t_node),  (yyvsp[-3].t_node)); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1557 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 81 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, StructSpecifier_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1563 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 83 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, OptTag_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1569 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 84 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = NULL;}
#line 1575 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 86 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Tag_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1581 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 90 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, VarDec_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1587 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 91 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-3].t_node))->no_line, VarDec_, NULL); add_child((yyval.t_node),  (yyvsp[-3].t_node));add_child((yyval.t_node),  (yyvsp[-2].t_node)); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1593 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 94 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-3].t_node))->no_line, FunDec_, NULL); add_child((yyval.t_node),  (yyvsp[-3].t_node));add_child((yyval.t_node),  (yyvsp[-2].t_node)); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1599 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 95 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, FunDec_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1605 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 96 "./src/parser.y" /* yacc.c:1646  */
    {syn_error = 1;}
#line 1611 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 98 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, VarList_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1617 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 99 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, VarList_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1623 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 101 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, ParamDec_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1629 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 105 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-3].t_node))->no_line, CompSt_, NULL); add_child((yyval.t_node),  (yyvsp[-3].t_node));add_child((yyval.t_node),  (yyvsp[-2].t_node)); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1635 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 106 "./src/parser.y" /* yacc.c:1646  */
    {syn_error = 1;}
#line 1641 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 108 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, StmtList_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1647 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 109 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = NULL;}
#line 1653 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 111 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, Stmt_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1659 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 112 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Stmt_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1665 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 113 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Stmt_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1671 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 114 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-4].t_node))->no_line, Stmt_, NULL); add_child((yyval.t_node),  (yyvsp[-4].t_node));add_child((yyval.t_node),  (yyvsp[-3].t_node)); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1677 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 115 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-6].t_node))->no_line, Stmt_, NULL); add_child((yyval.t_node),  (yyvsp[-6].t_node));add_child((yyval.t_node),  (yyvsp[-5].t_node)); add_child((yyval.t_node),  (yyvsp[-4].t_node));add_child((yyval.t_node),  (yyvsp[-3].t_node));add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1683 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 116 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-4].t_node))->no_line, Stmt_, NULL); add_child((yyval.t_node),  (yyvsp[-4].t_node));add_child((yyval.t_node),  (yyvsp[-3].t_node)); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1689 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 118 "./src/parser.y" /* yacc.c:1646  */
    { syn_error = 1;}
#line 1695 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 119 "./src/parser.y" /* yacc.c:1646  */
    { syn_error = 1;}
#line 1701 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 120 "./src/parser.y" /* yacc.c:1646  */
    { syn_error = 1;}
#line 1707 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 124 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, DefList_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1713 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 125 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = NULL;}
#line 1719 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 127 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Def_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1725 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 128 "./src/parser.y" /* yacc.c:1646  */
    {syn_error = 1;}
#line 1731 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 130 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, DecList_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1737 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 131 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, DecList_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1743 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 133 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Dec_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1749 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 134 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Dec_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1755 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 138 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1761 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 139 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1767 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 140 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1773 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 141 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1779 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 142 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1785 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 143 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1791 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 144 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1797 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 145 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1803 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 146 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1809 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 147 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1815 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 148 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-1].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1821 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 149 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-3].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-3].t_node));add_child((yyval.t_node),  (yyvsp[-2].t_node)); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1827 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 150 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1833 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 151 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-3].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-3].t_node));add_child((yyval.t_node),  (yyvsp[-2].t_node)); add_child((yyval.t_node),  (yyvsp[-1].t_node));add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1839 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 152 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[-2].t_node));add_child((yyval.t_node),  (yyvsp[-1].t_node)); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1845 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 153 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1851 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 154 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1857 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 155 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Exp_, NULL); add_child((yyval.t_node),  (yyvsp[0].t_node));}
#line 1863 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 158 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[-2].t_node))->no_line, Args_, NULL); add_child( (yyval.t_node),  (yyvsp[-2].t_node));add_child( (yyval.t_node),  (yyvsp[-1].t_node)); add_child( (yyval.t_node),  (yyvsp[0].t_node));}
#line 1869 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 159 "./src/parser.y" /* yacc.c:1646  */
    { (yyval.t_node) = new_tnode(((yyvsp[0].t_node))->no_line, Args_, NULL); add_child( (yyval.t_node),  (yyvsp[0].t_node));}
#line 1875 "./src/syntex.tab.c" /* yacc.c:1646  */
    break;


#line 1879 "./src/syntex.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 161 "./src/parser.y" /* yacc.c:1906  */

void yyerror(char *str){
    // should add error message using ($1)->no_line, yycolumn
    printf("Error type B at Line %d: error around \"%s\"\n", yylineno, yytext);
}

int yywrap(){
    return 1;
}
