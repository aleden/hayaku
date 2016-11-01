
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 1 "./Hayaku.y"

#include "Common.h"
#include "ICode.h"
#include "ParseNode.h"
#include "Variable.h"
#include <stdio.h>
#include <string.h>

int yylex();

struct Function* currentFunction;
struct FunctionTable* functionTable;
struct SymbolTable* globalSymbolTable;
unsigned int row = 0, col = 0;
char identifierBuff[IDENTIFIER_NAME_MAX_LEN];
unsigned int identifierLen;

void yyerror(const char* msg);
void Count(void);
void Comment(void);
int CheckType(void);

#define YYMAXDEPTH 0x50000
#define YYINITDEPTH 0x100


struct SemanticValueStruct
{
	union
	{
		struct ParseNode* pn;

		struct Symbol* symbol;

		Float f;
		Float32 f32;
		Float64 f64;

		Int s;
		Int16 s16;
		Int32 s32;

		UInt u;
		UInt16 u16;
		UInt32 u32;
	};


	enum VARIABLE_TYPE_SPECIFIER vts;

	UInt pointerDegree;

	BOOL b;

	Int8 name[IDENTIFIER_NAME_MAX_LEN];

	Int8 parametersDefinitionsNames[IDENTIFIER_NAME_MAX_LEN][FUNCTION_PARAMETERS_SIZE];
	struct VariableType parametersDefinitions[FUNCTION_PARAMETERS_SIZE];
	union
	{
		struct ParseNode* parameters[FUNCTION_PARAMETERS_SIZE];
		struct ParseNode* compoundStatement[COMPOUND_STATEMENT_SIZE];
	};
	
	union
	{
		UInt numStatements;
		UInt numParameters;
	};
};


void SetParserFunctionTable(struct FunctionTable* ft)
{ functionTable = ft; }

void SetParserGlobalSymbolTable(struct SymbolTable* gst)
{ globalSymbolTable = gst; }

void SetParserCurrentFunction(struct Function* f)
{ currentFunction = f; }

struct FunctionTable* GetParserFunctionTable()
{ return functionTable; }

#define YYSTYPE struct SemanticValueStruct

static void PrintTokenValue(FILE* file, int type, YYSTYPE val);
#define YYPRINT(FILE, TYPE, VALUE) PrintTokenValue(FILE, TYPE, VALUE)

#ifdef _MSC_VER
#define BISON_PRINT(STRING, ...) printf("BISON: " STRING "\n", __VA_ARGS__)
#define FLEX_PRINT(STRING, ...) printf("FLEX : " STRING "\n", __VA_ARGS__)
#else
#define BISON_PRINT(STRING, ...) printf("BISON: " STRING "\n", ##__VA_ARGS__)
#define FLEX_PRINT(STRING, ...) printf("FLEX : " STRING "\n", ##__VA_ARGS__)
#endif

#define ADD_FUNCTION_DEFINITION_PARAMETER(SEMANTIC_VALUE, SPECIFIER, POINTER_DEGREE, NAME, PARSENODE)\
	SEMANTIC_VALUE.parametersDefinitions[SEMANTIC_VALUE.numParameters].specifier = SPECIFIER;\
	SEMANTIC_VALUE.parametersDefinitions[SEMANTIC_VALUE.numParameters].pointerDegree = POINTER_DEGREE;\
	strcpy(SEMANTIC_VALUE.parametersDefinitionsNames[SEMANTIC_VALUE.numParameters], NAME);\
	SEMANTIC_VALUE.parameters[SEMANTIC_VALUE.numParameters] = PARSENODE;\
	++SEMANTIC_VALUE.numParameters

#define ADD_FUNCTION_CALL_PARAMETER(SEMANTIC_VALUE, PARSENODE)\
	SEMANTIC_VALUE.parameters[SEMANTIC_VALUE.numParameters] = PARSENODE;\
	++SEMANTIC_VALUE.numParameters

#define ADD_TO_COMPOUND_STATEMENT(SEMANTIC_VALUE, PARSENODE)\
	SEMANTIC_VALUE.compoundStatement[SEMANTIC_VALUE.numStatements] = PARSENODE;\
	++SEMANTIC_VALUE.numStatements;

// Procedure for allocating functions:
// 1. Allocate one function always before
// 2. Parsing statementsEnd: Put them in the unnamed function
// 3. End parsing function: Add to symbol table


/* Line 189 of yacc.c  */
#line 192 "C:\\Dev\\Hayaku\\hc\\Source\\yaac.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
     IDENTIFIER = 258,
     INT_CONST = 259,
     FLOAT_CONST = 260,
     STRING_LITERAL = 261,
     SIZEOF = 262,
     PTR_OP = 263,
     INC_OP = 264,
     DEC_OP = 265,
     LEFT_OP = 266,
     RIGHT_OP = 267,
     LE_OP = 268,
     GE_OP = 269,
     EQ_OP = 270,
     NE_OP = 271,
     AND_OP = 272,
     OR_OP = 273,
     MUL_ASSIGN = 274,
     DIV_ASSIGN = 275,
     MOD_ASSIGN = 276,
     ADD_ASSIGN = 277,
     SUB_ASSIGN = 278,
     LEFT_ASSIGN = 279,
     RIGHT_ASSIGN = 280,
     AND_ASSIGN = 281,
     XOR_ASSIGN = 282,
     OR_ASSIGN = 283,
     TYPE_NAME = 284,
     ELLIPSIS = 285,
     TYPEDEF = 286,
     STATIC = 287,
     INLINE = 288,
     BOOL_TKN = 289,
     INT = 290,
     INT8 = 291,
     INT16 = 292,
     INT32 = 293,
     INT64 = 294,
     UINT = 295,
     UINT8 = 296,
     UINT16 = 297,
     UINT32 = 298,
     UINT64 = 299,
     FLOAT32 = 300,
     FLOAT64 = 301,
     FLOAT = 302,
     CONST = 303,
     VOLATILE = 304,
     VOID = 305,
     CLASS = 306,
     UNION = 307,
     ENUM = 308,
     CASE = 309,
     DEFAULT = 310,
     IF = 311,
     ELSE = 312,
     SWITCH = 313,
     WHILE = 314,
     DO = 315,
     FOR = 316,
     GOTO = 317,
     CONTINUE = 318,
     BREAK = 319,
     RETURN = 320
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 299 "C:\\Dev\\Hayaku\\hc\\Source\\yaac.tab.c"

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
# if YYENABLE_NLS
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
#define YYFINAL  34
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1512

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  230
/* YYNRULES -- Number of states.  */
#define YYNSTATES  401

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   320

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,     2,     2,     2,    82,    75,     2,
      67,    68,    76,    77,    74,    78,    71,    81,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    89,
      83,    19,    84,    87,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,    85,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    86,    73,    79,     2,     2,     2,
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
      15,    16,    17,    18,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    17,    21,    23,
      26,    28,    30,    32,    34,    38,    40,    45,    49,    54,
      58,    62,    65,    68,    75,    83,    85,    89,    91,    94,
      97,   100,   103,   108,   110,   112,   114,   116,   118,   120,
     122,   127,   129,   133,   137,   141,   143,   147,   151,   153,
     157,   161,   163,   167,   171,   175,   179,   181,   185,   189,
     191,   195,   197,   201,   203,   207,   209,   213,   215,   219,
     221,   227,   229,   233,   237,   241,   245,   249,   253,   257,
     261,   265,   269,   273,   275,   279,   281,   284,   288,   290,
     293,   295,   298,   300,   303,   305,   308,   310,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   336,
     338,   340,   342,   344,   350,   355,   358,   360,   362,   364,
     367,   371,   374,   376,   379,   381,   383,   387,   389,   392,
     396,   401,   407,   413,   420,   423,   425,   429,   431,   435,
     437,   439,   441,   444,   446,   448,   452,   458,   463,   468,
     475,   482,   488,   493,   497,   502,   507,   511,   513,   516,
     519,   523,   525,   528,   530,   534,   536,   540,   543,   546,
     548,   550,   554,   556,   559,   561,   563,   566,   570,   573,
     577,   581,   586,   590,   595,   598,   602,   606,   611,   613,
     617,   622,   624,   627,   631,   636,   639,   641,   644,   648,
     651,   653,   655,   657,   659,   661,   663,   667,   672,   676,
     679,   683,   685,   688,   690,   692,   694,   697,   703,   711,
     717,   723,   731,   738,   746,   753,   761,   765,   768,   771,
     774
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      91,     0,    -1,    92,    -1,    91,    92,    -1,    93,    -1,
     115,    -1,   116,   132,    94,   150,    -1,   116,   132,   150,
      -1,   115,    -1,    94,   115,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,    67,   113,    68,    -1,    95,    -1,
      96,    69,   113,    70,    -1,    96,    67,    68,    -1,    96,
      67,    97,    68,    -1,    96,    71,     3,    -1,    96,     8,
       3,    -1,    96,     9,    -1,    96,    10,    -1,    67,   140,
      68,    72,   144,    73,    -1,    67,   140,    68,    72,   144,
      74,    73,    -1,   112,    -1,    97,    74,   112,    -1,    96,
      -1,     9,    98,    -1,    10,    98,    -1,    99,   100,    -1,
       7,    98,    -1,     7,    67,   140,    68,    -1,    75,    -1,
      76,    -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,
      98,    -1,    67,   140,    68,   100,    -1,   100,    -1,   101,
      76,   100,    -1,   101,    81,   100,    -1,   101,    82,   100,
      -1,   101,    -1,   102,    77,   101,    -1,   102,    78,   101,
      -1,   102,    -1,   103,    11,   102,    -1,   103,    12,   102,
      -1,   103,    -1,   104,    83,   103,    -1,   104,    84,   103,
      -1,   104,    13,   103,    -1,   104,    14,   103,    -1,   104,
      -1,   105,    15,   104,    -1,   105,    16,   104,    -1,   105,
      -1,   106,    75,   105,    -1,   106,    -1,   107,    85,   106,
      -1,   107,    -1,   108,    86,   107,    -1,   108,    -1,   109,
      17,   108,    -1,   109,    -1,   110,    18,   109,    -1,   110,
      -1,   110,    87,   113,    88,   111,    -1,   111,    -1,    98,
      19,   112,    -1,    98,    23,   112,    -1,    98,    24,   112,
      -1,    98,    20,   112,    -1,    98,    21,   112,    -1,    98,
      22,   112,    -1,    98,    25,   112,    -1,    98,    26,   112,
      -1,    98,    27,   112,    -1,    98,    28,   112,    -1,    98,
      29,   112,    -1,   112,    -1,   113,    74,   112,    -1,   111,
      -1,   116,    89,    -1,   116,   117,    89,    -1,   118,    -1,
     118,   116,    -1,   119,    -1,   119,   116,    -1,   130,    -1,
     130,   116,    -1,   131,    -1,   131,   116,    -1,   132,    -1,
     132,    19,   143,    -1,    32,    -1,    33,    -1,    51,    -1,
      37,    -1,    38,    -1,    39,    -1,    36,    -1,    41,    -1,
      46,    -1,    47,    -1,    48,    -1,    35,    -1,   120,    -1,
     127,    -1,    30,    -1,   121,     3,    72,   122,    73,    -1,
     121,    72,   122,    73,    -1,   121,     3,    -1,    52,    -1,
      53,    -1,   123,    -1,   122,   123,    -1,   124,   125,    89,
      -1,   119,   124,    -1,   119,    -1,   130,   124,    -1,   130,
      -1,   126,    -1,   125,    74,   126,    -1,   132,    -1,    88,
     114,    -1,   132,    88,   114,    -1,    54,    72,   128,    73,
      -1,    54,     3,    72,   128,    73,    -1,    54,    72,   128,
      74,    73,    -1,    54,     3,    72,   128,    74,    73,    -1,
      54,     3,    -1,   129,    -1,   128,    74,   129,    -1,     3,
      -1,     3,    19,   114,    -1,    49,    -1,    50,    -1,    34,
      -1,   134,   133,    -1,   133,    -1,     3,    -1,    67,   132,
      68,    -1,   133,    69,   135,   112,    70,    -1,   133,    69,
     135,    70,    -1,   133,    69,   112,    70,    -1,   133,    69,
      33,   135,   112,    70,    -1,   133,    69,   135,    33,   112,
      70,    -1,   133,    69,   135,    76,    70,    -1,   133,    69,
      76,    70,    -1,   133,    69,    70,    -1,   133,    67,   136,
      68,    -1,   133,    67,   139,    68,    -1,   133,    67,    68,
      -1,    76,    -1,    76,   135,    -1,    76,   134,    -1,    76,
     135,   134,    -1,   130,    -1,   135,   130,    -1,   137,    -1,
     137,    74,    31,    -1,   138,    -1,   137,    74,   138,    -1,
     116,   132,    -1,   116,   141,    -1,   116,    -1,     3,    -1,
     139,    74,     3,    -1,   124,    -1,   124,   141,    -1,   134,
      -1,   142,    -1,   134,   142,    -1,    67,   141,    68,    -1,
      69,    70,    -1,    69,   112,    70,    -1,   142,    69,    70,
      -1,   142,    69,   112,    70,    -1,    69,    76,    70,    -1,
     142,    69,    76,    70,    -1,    67,    68,    -1,    67,   136,
      68,    -1,   142,    67,    68,    -1,   142,    67,   136,    68,
      -1,   112,    -1,    72,   144,    73,    -1,    72,   144,    74,
      73,    -1,   143,    -1,   145,   143,    -1,   144,    74,   143,
      -1,   144,    74,   145,   143,    -1,   146,    19,    -1,   147,
      -1,   146,   147,    -1,    69,   114,    70,    -1,    71,     3,
      -1,   149,    -1,   150,    -1,   153,    -1,   154,    -1,   155,
      -1,   156,    -1,     3,    88,   148,    -1,    55,   114,    88,
     148,    -1,    56,    88,   148,    -1,    72,    73,    -1,    72,
     151,    73,    -1,   152,    -1,   151,   152,    -1,   115,    -1,
     148,    -1,    89,    -1,   113,    89,    -1,    57,    67,   113,
      68,   148,    -1,    57,    67,   113,    68,   148,    58,   148,
      -1,    59,    67,   113,    68,   148,    -1,    60,    67,   113,
      68,   148,    -1,    61,   148,    60,    67,   113,    68,    89,
      -1,    62,    67,   153,   153,    68,   148,    -1,    62,    67,
     153,   153,   113,    68,   148,    -1,    62,    67,   115,   153,
      68,   148,    -1,    62,    67,   115,   153,   113,    68,   148,
      -1,    63,     3,    89,    -1,    64,    89,    -1,    65,    89,
      -1,    66,    89,    -1,    66,   113,    89,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   140,   144,   145,   149,   162,   190,   191,
     195,   202,   209,   216,   217,   224,   231,   232,   240,   252,
     253,   260,   261,   262,   263,   267,   272,   280,   281,   282,
     283,   284,   285,   288,   288,   288,   288,   288,   288,   292,
     293,   297,   298,   305,   312,   322,   323,   330,   340,   341,
     342,   346,   347,   355,   363,   371,   382,   383,   391,   395,
     396,   400,   401,   405,   406,   410,   411,   415,   416,   420,
     421,   425,   426,   436,   446,   456,   466,   476,   477,   478,
     479,   480,   481,   485,   486,   490,   494,   499,   520,   521,
     522,   523,   524,   525,   526,   527,   531,   536,   549,   550,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   570,   571,   572,   576,   577,   581,   582,
     586,   590,   591,   592,   593,   597,   598,   602,   603,   604,
     608,   609,   610,   611,   612,   616,   617,   621,   622,   626,
     627,   631,   635,   640,   645,   652,   653,   654,   655,   656,
     657,   658,   659,   660,   661,   687,   693,   702,   706,   710,
     714,   721,   722,   727,   728,   732,   742,   755,   762,   767,
     776,   783,   787,   788,   792,   793,   794,   798,   799,   800,
     801,   802,   803,   804,   805,   806,   807,   808,   812,   813,
     814,   818,   819,   820,   821,   825,   829,   830,   834,   835,
     839,   840,   841,   842,   843,   844,   848,   849,   850,   854,
     860,   871,   875,   882,   883,   887,   888,   892,   899,   900,
     904,   911,   912,   921,   930,   939,   951,   952,   953,   954,
     958
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INT_CONST", "FLOAT_CONST",
  "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP",
  "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "'='",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN",
  "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN",
  "TYPE_NAME", "ELLIPSIS", "TYPEDEF", "STATIC", "INLINE", "BOOL_TKN",
  "INT", "INT8", "INT16", "INT32", "INT64", "UINT", "UINT8", "UINT16",
  "UINT32", "UINT64", "FLOAT32", "FLOAT64", "FLOAT", "CONST", "VOLATILE",
  "VOID", "CLASS", "UNION", "ENUM", "CASE", "DEFAULT", "IF", "ELSE",
  "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "'('", "')'", "'['", "']'", "'.'", "'{'", "'}'", "','", "'&'", "'*'",
  "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "':'", "';'", "$accept", "translation_unit",
  "external_definition", "function_definition", "declaration_list",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator", "storage_class_specifier", "type_specifier",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "function_specifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    61,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,    40,    41,    91,
      93,    46,   123,   125,    44,    38,    42,    43,    45,   126,
      33,    47,    37,    60,    62,    94,   124,    63,    58,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      95,    95,    95,    95,    95,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    98,    98,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,   100,
     100,   101,   101,   101,   101,   102,   102,   102,   103,   103,
     103,   104,   104,   104,   104,   104,   105,   105,   105,   106,
     106,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   113,   113,   114,   115,   115,   116,   116,
     116,   116,   116,   116,   116,   116,   117,   117,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   121,   121,   122,   122,
     123,   124,   124,   124,   124,   125,   125,   126,   126,   126,
     127,   127,   127,   127,   127,   128,   128,   129,   129,   130,
     130,   131,   132,   132,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   134,   134,   134,
     134,   135,   135,   136,   136,   137,   137,   138,   138,   138,
     139,   139,   140,   140,   141,   141,   141,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   143,   143,
     143,   144,   144,   144,   144,   145,   146,   146,   147,   147,
     148,   148,   148,   148,   148,   148,   149,   149,   149,   150,
     150,   151,   151,   152,   152,   153,   153,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   156,   156,   156,   156,
     156
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     4,     3,     1,     2,
       1,     1,     1,     1,     3,     1,     4,     3,     4,     3,
       3,     2,     2,     6,     7,     1,     3,     1,     2,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     1,     2,     3,     1,     2,
       1,     2,     1,     2,     1,     2,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     1,     1,     1,     2,
       3,     2,     1,     2,     1,     1,     3,     1,     2,     3,
       4,     5,     5,     6,     2,     1,     3,     1,     3,     1,
       1,     1,     2,     1,     1,     3,     5,     4,     4,     6,
       6,     5,     4,     3,     4,     4,     3,     1,     2,     2,
       3,     1,     2,     1,     3,     1,     3,     2,     2,     1,
       1,     3,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     3,     4,     2,     3,     3,     4,     1,     3,
       4,     1,     2,     3,     4,     2,     1,     2,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     2,
       3,     1,     2,     1,     1,     1,     2,     5,     7,     5,
       5,     7,     6,     7,     6,     7,     3,     2,     2,     2,
       3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   112,    98,    99,   141,   109,   104,   101,   102,   103,
     105,   106,   107,   108,   139,   140,   100,   116,   117,     0,
       0,     2,     4,     5,     0,    88,    90,   110,     0,   111,
      92,    94,   134,     0,     1,     3,   144,     0,   157,    86,
       0,    96,   143,     0,    89,    91,   115,     0,    93,    95,
       0,   137,     0,   135,     0,   161,   159,   158,    87,     0,
       0,     0,     8,     0,     7,     0,     0,   142,     0,   122,
       0,   118,     0,   124,     0,     0,   130,     0,   145,   162,
     160,    10,    11,    12,    13,     0,     0,     0,     0,     0,
      33,    34,    35,    36,    37,    38,    15,    27,    39,     0,
      41,    45,    48,    51,    56,    59,    61,    63,    65,    67,
      69,    71,   188,    97,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   209,   215,    83,     0,
     213,   214,   200,   201,     0,   211,   202,   203,   204,   205,
       9,     6,    96,   170,   156,   169,     0,   163,   165,     0,
       0,   153,    34,     0,     0,     0,   121,   114,   119,     0,
       0,   125,   127,   123,   131,     0,    39,    85,   138,   132,
     136,     0,    31,     0,    28,    29,     0,   172,     0,     0,
       0,   191,     0,     0,     0,   196,     0,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   227,   228,   229,     0,     0,   216,   210,   212,
       0,     0,   167,   174,   168,   175,   154,     0,   155,     0,
       0,   152,   148,     0,   147,    34,     0,   113,   128,     0,
     120,     0,   133,     0,     0,    14,     0,   174,   173,     0,
       0,   199,   189,     0,   192,   195,   197,    20,    17,     0,
      25,     0,    19,    72,    75,    76,    77,    73,    74,    78,
      79,    80,    81,    82,    42,    43,    44,    46,    47,    49,
      50,    54,    55,    52,    53,    57,    58,    60,    62,    64,
      66,    68,     0,   206,     0,   208,     0,     0,     0,     0,
       0,     0,   226,   230,    84,   184,     0,     0,   178,    34,
       0,   176,     0,     0,   164,   166,   171,     0,     0,   151,
     146,   126,   129,    32,     0,     0,    40,   198,   190,   193,
       0,    18,     0,    16,     0,   207,     0,     0,     0,     0,
       0,     0,   185,   177,   182,   179,   186,     0,   180,    34,
       0,   149,   150,     0,   194,    26,    70,   217,   219,   220,
       0,     0,     0,     0,     0,   187,   183,   181,    23,     0,
       0,     0,   224,     0,   222,     0,    24,   218,   221,   225,
     223
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    22,    61,    96,    97,   279,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   128,   129,   168,    23,    63,    40,    25,    26,
      27,    28,    70,    71,    72,   160,   161,    29,    52,    53,
      30,    31,    54,    42,    43,    57,   326,   147,   148,   149,
     178,   327,   245,   181,   182,   183,   184,   185,   131,   132,
     133,   134,   135,   136,   137,   138,   139
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -260
static const yytype_int16 yypact[] =
{
    1433,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,    46,
    1103,  -260,  -260,  -260,    18,  1433,  1433,  -260,    48,  -260,
    1433,  1433,   -31,    42,  -260,  -260,  -260,    55,   -10,  -260,
     -17,  1237,   172,    24,  -260,  -260,     4,  1458,  -260,  -260,
      42,    -3,   119,  -260,    20,  -260,  -260,   -10,  -260,   846,
     318,  1356,  -260,    18,  -260,  1212,   674,   172,  1458,  1458,
    1300,  -260,   120,  1458,   194,  1050,  -260,    14,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  1095,  1109,  1109,   622,   800,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,   190,   285,  1050,
    -260,   -19,   192,   267,    66,   268,     6,    39,    49,    88,
      34,  -260,  -260,  -260,    83,  1050,    91,   134,   142,   149,
     526,   154,   222,   162,   166,   489,  -260,  -260,  -260,   -30,
    -260,  -260,  -260,  -260,   396,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,   253,  -260,  -260,    26,   206,   171,  -260,     9,
     241,  -260,   210,   216,   706,  1328,  -260,  -260,  -260,  1050,
     -28,  -260,   188,  -260,  -260,    19,  -260,  -260,  -260,  -260,
    -260,   622,  -260,   622,  -260,  -260,   108,   114,   220,  1050,
     257,  -260,   224,   846,    13,  -260,   290,  -260,  -260,   880,
    1050,   292,  1050,  1050,  1050,  1050,  1050,  1050,  1050,  1050,
    1050,  1050,  1050,  -260,  1050,  1050,  1050,  1050,  1050,  1050,
    1050,  1050,  1050,  1050,  1050,  1050,  1050,  1050,  1050,  1050,
    1050,  1050,  1050,   526,   230,   526,  1050,  1050,  1050,   266,
     474,   240,  -260,  -260,  -260,   -20,  1050,  -260,  -260,  -260,
    1160,   924,  -260,    65,  -260,   177,  -260,  1408,  -260,   327,
     832,  -260,  -260,  1050,  -260,   264,   265,  -260,  -260,   120,
    -260,  1050,  -260,   269,   273,  -260,  1264,   185,  -260,   958,
     272,  -260,  -260,   722,  -260,  -260,  -260,  -260,  -260,   110,
    -260,    77,  -260,  -260,  -260,  -260,  -260,  -260,  -260,  -260,
    -260,  -260,  -260,  -260,  -260,  -260,  -260,   -19,   -19,   192,
     192,   267,   267,   267,   267,    66,    66,   268,     6,    39,
      49,    88,   -14,  -260,   526,  -260,   121,   145,   146,   276,
     567,   567,  -260,  -260,  -260,  -260,   277,   278,  -260,   274,
     279,   177,  1383,   972,  -260,  -260,  -260,   288,   293,  -260,
    -260,  -260,  -260,   275,   275,   800,  -260,  -260,  -260,  -260,
     846,  -260,  1050,  -260,  1050,  -260,   526,   526,   526,  1050,
    1002,  1017,  -260,  -260,  -260,  -260,  -260,   308,  -260,   316,
     317,  -260,  -260,   226,  -260,  -260,  -260,   330,  -260,  -260,
     156,   526,   158,   526,   168,  -260,  -260,  -260,  -260,   754,
     526,   300,  -260,   526,  -260,   526,  -260,  -260,  -260,  -260,
    -260
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -260,  -260,   372,  -260,  -260,  -260,  -260,  -260,   -51,  -260,
     -92,    94,   107,    51,   124,   187,   191,   189,   193,   195,
    -260,   -73,   -56,     1,  -109,   -23,     0,  -260,  -260,    31,
    -260,  -260,   342,   -59,     2,  -260,   152,  -260,   362,   -62,
     165,  -260,   -16,   -38,   -29,   -53,   -61,  -260,   167,  -260,
      85,  -122,  -200,   -58,    72,  -259,  -260,   234,  -108,  -260,
      12,  -260,   286,  -211,  -260,  -260,  -260
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      24,   113,   167,   112,   146,    67,   224,   203,    41,    56,
     153,   158,   229,   154,   350,   170,    75,    51,    62,   321,
      24,    36,    51,   244,   166,    44,    45,    36,    80,    36,
      48,    49,   275,   112,   172,   174,   175,   130,   140,    14,
      15,    50,   167,   331,   236,    51,   259,   142,   166,    32,
     258,    46,   221,    64,   236,   268,   162,   204,    36,   237,
     236,   260,   205,   206,   166,   145,    38,   331,    36,   323,
     270,   156,    58,   141,   354,   163,    68,   248,    69,   211,
     212,   217,   179,   249,   180,    37,   167,   169,    78,   176,
     177,    37,   262,   240,    38,   241,   158,   250,   256,    69,
      69,    69,    38,   170,    69,   220,   167,    39,   166,   360,
     361,   130,   294,   295,   296,   313,   243,   315,    33,    69,
      47,   222,    37,    36,   218,   274,   235,   112,   166,   242,
     350,    38,   240,   280,   241,   219,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   353,   267,   213,
     214,   236,   342,   166,   166,   166,   166,   166,   166,   166,
     166,   166,   166,   166,   166,   166,   166,   166,   166,   166,
     166,   223,   176,   177,   176,   177,   265,   346,   351,   225,
     324,   266,   236,   241,   352,   330,    69,    37,   167,   356,
      38,   281,    76,    77,   337,   236,    38,   338,   186,   187,
     188,   226,    69,    55,    69,    67,   355,   320,   159,   227,
     166,   243,    73,   357,   358,   349,   228,   112,   166,   236,
     236,   230,    79,   312,   391,   231,   393,   316,   317,   318,
     236,    55,   236,    73,    73,    73,   395,   267,    73,    65,
     145,    66,   236,   162,   332,   247,   333,   145,   377,   378,
     379,   232,   266,    73,   241,   233,   263,   189,   264,   190,
     271,   191,   301,   302,   303,   304,   145,   164,   165,   207,
     208,   367,    59,   392,   246,   394,   261,   370,   209,   210,
     251,   376,   397,   215,   216,   399,   252,   400,   269,   112,
      14,    15,   374,   277,   112,   282,   375,   272,   273,   388,
     389,   297,   298,   166,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,    55,   299,   300,   314,    79,
      73,   114,    82,    83,    84,    85,   319,    86,    87,   322,
     336,   349,   145,   112,   339,   340,    73,   343,    73,   305,
     306,   344,   347,   359,   364,   362,   363,   345,     1,   365,
       2,     3,     4,     5,     6,     7,     8,     9,   371,    10,
     380,   382,   384,   372,    11,    12,    13,    14,    15,    16,
      17,    18,    19,   115,   116,   117,   385,   118,   119,   120,
     121,   122,   123,   124,   125,    88,   386,   387,   390,   398,
      60,   126,    35,    90,    91,    92,    93,    94,    95,   114,
      82,    83,    84,    85,   307,    86,    87,   127,   309,   308,
     155,   341,    74,   310,   335,    79,   311,   373,   276,     0,
     239,     0,     0,     0,     0,     0,     1,     0,     2,     3,
       4,     5,     6,     7,     8,     9,     0,    10,     0,     0,
       0,     0,    11,    12,    13,    14,    15,    16,    17,    18,
      19,   115,   116,   117,     0,   118,   119,   120,   121,   122,
     123,   124,   125,    88,     0,     0,     0,     0,    60,   238,
       0,    90,    91,    92,    93,    94,    95,    81,    82,    83,
      84,    85,     0,    86,    87,   127,     0,     0,     0,     0,
       0,     0,    81,    82,    83,    84,    85,     0,    86,    87,
       0,     0,     0,     0,     1,     0,     2,     3,     4,     5,
       6,     7,     8,     9,     0,    10,     0,     0,     0,     0,
      11,    12,    13,    14,    15,    16,    17,    18,    19,   114,
      82,    83,    84,    85,     0,    86,    87,     0,     0,     0,
       0,    88,     0,     0,     0,     0,     0,     0,     0,    90,
      91,    92,    93,    94,    95,     0,    88,     0,     0,     0,
       0,     0,     0,   127,    90,    91,    92,    93,    94,    95,
      81,    82,    83,    84,    85,     0,    86,    87,   234,     0,
       0,   115,   116,   117,     0,   118,   119,   120,   121,   122,
     123,   124,   125,    88,     0,     0,     0,     0,    60,     0,
       0,    90,    91,    92,    93,    94,    95,     0,     0,     0,
       0,     0,     0,     0,     0,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,    82,    83,    84,    85,
       0,    86,    87,     0,    88,     0,     0,     0,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,     0,     0,
       0,     0,     1,     0,     0,     0,   127,     5,     6,     7,
       8,     9,     0,    10,     0,     0,     0,     0,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    81,    82,    83,
      84,    85,     0,    86,    87,     0,     0,     0,     0,    88,
       0,     0,     0,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    95,     0,     0,     0,     0,   150,     0,    81,
      82,    83,    84,    85,     0,    86,    87,     0,     0,     0,
       0,     0,     0,    14,    15,    81,    82,    83,    84,    85,
       0,    86,    87,     0,     0,     0,     0,     0,     0,   253,
       0,    88,     0,     0,   151,     0,     0,     0,     0,    90,
     152,    92,    93,    94,    95,    14,    15,    81,    82,    83,
      84,    85,     0,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,    88,     0,     0,   254,     0,     0,     0,
       0,    90,   255,    92,    93,    94,    95,     0,     0,    88,
       0,   179,     0,   180,    89,   348,     0,    90,    91,    92,
      93,    94,    95,    81,    82,    83,    84,    85,     0,    86,
      87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,   179,     0,   180,    89,   396,     0,    90,
      91,    92,    93,    94,    95,    81,    82,    83,    84,    85,
       0,    86,    87,     0,     0,     0,     0,     0,     0,    81,
      82,    83,    84,    85,     0,    86,    87,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,   179,
       0,   180,    89,     0,     0,    90,    91,    92,    93,    94,
      95,    14,    15,    81,    82,    83,    84,    85,     0,    86,
      87,     0,     0,     0,     0,     0,     0,     0,     0,    88,
       0,     0,     0,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    95,    88,     0,     0,     0,     0,    89,     0,
       0,    90,    91,    92,    93,    94,    95,    81,    82,    83,
      84,    85,     0,    86,    87,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,   278,     0,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,    81,    82,    83,    84,    85,     0,    86,    87,     0,
       0,     0,     0,     0,     0,    81,    82,    83,    84,    85,
       0,    86,    87,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,     0,   328,     0,     0,     0,     0,    90,
     329,    92,    93,    94,    95,    81,    82,    83,    84,    85,
       0,    86,    87,     0,     0,     0,     0,     0,     0,     0,
      81,    82,    83,    84,    85,    88,    86,    87,     0,     0,
     345,     0,     0,    90,    91,    92,    93,    94,    95,    88,
       0,     0,   368,     0,     0,     0,     0,    90,   369,    92,
      93,    94,    95,    81,    82,    83,    84,    85,     0,    86,
      87,     0,     0,     0,     0,     0,     0,     0,     0,    88,
     381,     0,     0,     0,     0,     0,     0,    90,    91,    92,
      93,    94,    95,     0,    88,   383,     0,     0,     0,     0,
       0,     0,    90,    91,    92,    93,    94,    95,    81,    82,
      83,    84,    85,    34,    86,    87,     0,     0,     0,     0,
       0,     0,    81,    82,    83,    84,    85,    88,    86,    87,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
      95,     0,     0,     1,     0,     2,     3,     4,     5,     6,
       7,     8,     9,     0,    10,     0,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,   171,    36,     0,     0,     0,     0,     0,     0,
      90,    91,    92,    93,    94,    95,   173,     0,     0,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,    95,
       1,     0,     2,     3,     4,     5,     6,     7,     8,     9,
       0,    10,     0,     0,     0,     0,    11,    12,    13,    14,
      15,    16,    17,    18,    19,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   240,   325,   241,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,     1,     0,     2,     3,     4,     5,     6,     7,
       8,     9,     0,    10,     0,     0,    59,     0,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     1,     0,     2,
       3,     4,     5,     6,     7,     8,     9,     0,    10,     0,
     144,     0,     0,    11,    12,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     1,     0,     2,     3,     4,     5,
       6,     7,     8,     9,     0,    10,     0,     0,     0,    60,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,   266,   325,   241,     0,     5,     6,     7,     8,     9,
      38,    10,     0,     0,     0,     0,    11,    12,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     1,     0,
       0,     0,     0,     5,     6,     7,     8,     9,     0,    10,
       0,     0,     0,   157,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     1,     0,     2,     3,
       4,     5,     6,     7,     8,     9,     0,    10,     0,     0,
       0,   257,    11,    12,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     1,     0,     2,     3,     4,     5,     6,
       7,     8,     9,     0,    10,     0,     0,     0,    60,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     1,   334,
       2,     3,     4,     5,     6,     7,     8,     9,     0,    10,
       0,   366,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    19,     1,     0,     2,     3,     4,     5,     6,
       7,     8,     9,     0,    10,     0,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    19,     1,     0,
       0,     0,     0,     5,     6,     7,     8,     9,     0,    10,
       0,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    19
};

static const yytype_int16 yycheck[] =
{
       0,    59,    75,    59,    65,    43,   115,    99,    24,    38,
      66,    70,   120,    66,   273,    77,    19,     3,    41,   230,
      20,     3,     3,   145,    75,    25,    26,     3,    57,     3,
      30,    31,    19,    89,    85,    86,    87,    60,    61,    49,
      50,    72,   115,   243,    74,     3,    74,    63,    99,     3,
     159,     3,    18,    41,    74,   177,    72,    76,     3,    89,
      74,    89,    81,    82,   115,    65,    76,   267,     3,    89,
     179,    69,    89,    61,    88,    73,    72,    68,    47,    13,
      14,    75,    69,    74,    71,    67,   159,    73,    68,    88,
      88,    67,    73,    67,    76,    69,   155,   150,   154,    68,
      69,    70,    76,   165,    73,    17,   179,    89,   159,   320,
     321,   134,   204,   205,   206,   223,   145,   225,    72,    88,
      72,    87,    67,     3,    85,   183,   125,   183,   179,   145,
     389,    76,    67,   189,    69,    86,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,    70,   177,    83,
      84,    74,   261,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,    88,   171,   171,   173,   173,    68,   269,    68,    88,
     236,    67,    74,    69,    74,   241,   155,    67,   261,    68,
      76,   190,    73,    74,   250,    74,    76,   253,     8,     9,
      10,    67,   171,    38,   173,   243,   314,   230,    88,    67,
     261,   240,    47,    68,    68,   273,    67,   273,   269,    74,
      74,    67,    57,   222,    68,     3,    68,   226,   227,   228,
      74,    66,    74,    68,    69,    70,    68,   266,    73,    67,
     240,    69,    74,   259,    67,    74,    69,   247,   356,   357,
     358,    89,    67,    88,    69,    89,   171,    67,   173,    69,
       3,    71,   211,   212,   213,   214,   266,    73,    74,    77,
      78,   332,    19,   381,    68,   383,    88,   333,    11,    12,
      70,   354,   390,    15,    16,   393,    70,   395,    68,   345,
      49,    50,   350,     3,   350,     3,   352,    73,    74,    73,
      74,   207,   208,   354,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,   150,   209,   210,    88,   154,
     155,     3,     4,     5,     6,     7,    60,     9,    10,    89,
       3,   389,   332,   389,    70,    70,   171,    68,   173,   215,
     216,    68,    70,    67,    70,    68,    68,    72,    30,    70,
      32,    33,    34,    35,    36,    37,    38,    39,    70,    41,
     359,   360,   361,    70,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    68,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    70,    70,    58,    89,
      72,    73,    20,    75,    76,    77,    78,    79,    80,     3,
       4,     5,     6,     7,   217,     9,    10,    89,   219,   218,
      68,   259,    50,   220,   247,   250,   221,   345,   184,    -1,
     134,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    -1,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,     3,     4,     5,
       6,     7,    -1,     9,    10,    89,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    -1,    -1,    -1,    -1,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     3,
       4,     5,     6,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    -1,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    75,    76,    77,    78,    79,    80,
       3,     4,     5,     6,     7,    -1,     9,    10,    89,    -1,
      -1,    55,    56,    57,    -1,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    67,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    89,    35,    36,    37,
      38,    39,    -1,    41,    -1,    -1,    -1,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    33,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    49,    50,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    -1,    -1,    67,
      -1,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    69,
      -1,    71,    72,    -1,    -1,    75,    76,    77,    78,    79,
      80,    49,    50,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    67,    -1,    -1,    -1,    -1,    72,    -1,
      -1,    75,    76,    77,    78,    79,    80,     3,     4,     5,
       6,     7,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,     3,     4,     5,     6,     7,    -1,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,    -1,    70,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,     3,     4,     5,     6,     7,
      -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    67,     9,    10,    -1,    -1,
      72,    -1,    -1,    75,    76,    77,    78,    79,    80,    67,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,     3,     4,     5,     6,     7,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    -1,    67,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,     3,     4,
       5,     6,     7,     0,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    67,     9,    10,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    -1,    -1,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      -1,    -1,    67,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      30,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    52,    53,    54,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    -1,    -1,    19,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    41,    -1,
      68,    -1,    -1,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    -1,    -1,    -1,    72,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    67,    68,    69,    -1,    35,    36,    37,    38,    39,
      76,    41,    -1,    -1,    -1,    -1,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,    41,
      -1,    -1,    -1,    73,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    -1,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    -1,    -1,
      -1,    73,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    -1,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    -1,    -1,    -1,    72,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    41,
      -1,    68,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    -1,    -1,    -1,    -1,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    30,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    -1,    41,
      -1,    -1,    -1,    -1,    46,    47,    48,    49,    50,    51,
      52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    32,    33,    34,    35,    36,    37,    38,    39,
      41,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      91,    92,    93,   115,   116,   118,   119,   120,   121,   127,
     130,   131,     3,    72,     0,    92,     3,    67,    76,    89,
     117,   132,   133,   134,   116,   116,     3,    72,   116,   116,
      72,     3,   128,   129,   132,   130,   134,   135,    89,    19,
      72,    94,   115,   116,   150,    67,    69,   133,    72,   119,
     122,   123,   124,   130,   128,    19,    73,    74,    68,   130,
     134,     3,     4,     5,     6,     7,     9,    10,    67,    72,
      75,    76,    77,    78,    79,    80,    95,    96,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   143,     3,    55,    56,    57,    59,    60,
      61,    62,    63,    64,    65,    66,    73,    89,   112,   113,
     115,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     115,   150,   132,     3,    68,   116,   136,   137,   138,   139,
      33,    70,    76,   112,   135,   122,   124,    73,   123,    88,
     125,   126,   132,   124,    73,    74,    98,   111,   114,    73,
     129,    67,    98,    67,    98,    98,   113,   124,   140,    69,
      71,   143,   144,   145,   146,   147,     8,     9,    10,    67,
      69,    71,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,   100,    76,    81,    82,    77,    78,    11,
      12,    13,    14,    83,    84,    15,    16,    75,    85,    86,
      17,    18,    87,    88,   114,    88,    67,    67,    67,   148,
      67,     3,    89,    89,    89,   113,    74,    89,    73,   152,
      67,    69,   132,   134,   141,   142,    68,    74,    68,    74,
     135,    70,    70,    33,    70,    76,   112,    73,   114,    74,
      89,    88,    73,   140,   140,    68,    67,   134,   141,    68,
     114,     3,    73,    74,   143,    19,   147,     3,    68,    97,
     112,   113,     3,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   100,   100,   100,   101,   101,   102,
     102,   103,   103,   103,   103,   104,   104,   105,   106,   107,
     108,   109,   113,   148,    88,   148,   113,   113,   113,    60,
     115,   153,    89,    89,   112,    68,   136,   141,    70,    76,
     112,   142,    67,    69,    31,   138,     3,   112,   112,    70,
      70,   126,   114,    68,    68,    72,   100,    70,    73,   143,
     145,    68,    74,    70,    88,   148,    68,    68,    68,    67,
     153,   153,    68,    68,    70,    70,    68,   136,    70,    76,
     112,    70,    70,   144,   143,   112,   111,   148,   148,   148,
     113,    68,   113,    68,   113,    68,    70,    70,    73,    74,
      58,    68,   148,    68,   148,    68,    73,   148,    89,   148,
     148
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
# if YYLTYPE_IS_TRIVIAL
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
        case 6:

/* Line 1455 of yacc.c  */
#line 150 "./Hayaku.y"
    {
		// Function
		struct VariableType returnType = {(yyvsp[(1) - (4)]).vts, (yyvsp[(1) - (4)]).pointerDegree};
		char* name = (yyvsp[(2) - (4)]).name;

		AddFunctionSymbol(globalSymbolTable, (yyvsp[(2) - (4)]).name, currentFunction);
		++functionTable->numFunctions;

		ALLOC_FUNCTION(functionTable);

		currentFunction = functionTable->functions[functionTable->numFunctions];
	;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 163 "./Hayaku.y"
    {
		struct VariableType* p;
		struct Symbol* functionSymbol;

		// Function
		currentFunction->returnType.specifier = (yyvsp[(1) - (3)]).vts;
		currentFunction->returnType.pointerDegree = (yyvsp[(1) - (3)]).pointerDegree;
		currentFunction->body = PSUB_PARSENODE((yyvsp[(3) - (3)]).pn, struct CompoundStatementParseNode);
		memcpy(currentFunction->parametersStart, (yyvsp[(2) - (3)]).parametersDefinitions, (yyvsp[(2) - (3)]).numParameters * sizeof(struct VariableType));
		currentFunction->parametersEnd += (yyvsp[(2) - (3)]).numParameters;

		currentFunction->sizeOfParameters = 0;

		for (p = currentFunction->parametersStart; p < currentFunction->parametersEnd; ++p)
			currentFunction->sizeOfParameters += variableTypeSizes[p->specifier];

		functionSymbol = AddFunctionSymbol(globalSymbolTable, (yyvsp[(2) - (3)]).name, currentFunction);
		currentFunction->name = functionSymbol->name;
		++functionTable->numFunctions;

		ALLOC_FUNCTION(functionTable);

		currentFunction = functionTable->functions[functionTable->numFunctions];
	;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 196 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct IdentifierParseNode);
		PN_SET_TYPE((yyval).pn, PNT_IDENTIFIER);
		strcpy(PSUB_PARSENODE((yyval).pn, struct IdentifierParseNode)->name, (yyvsp[(1) - (1)]).name);
		PSUB_PARSENODE((yyval).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (1)]).name);
	;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 203 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ConstParseNode);
		PN_SET_TYPE((yyval).pn, PNT_CONST);
		PSUB_PARSENODE((yyval).pn, struct ConstParseNode)->value.i32 = (yyvsp[(1) - (1)]).s;
		PSUB_PARSENODE((yyval).pn, struct ConstParseNode)->value.type = CT_INT;
	;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 210 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ConstParseNode);
		PN_SET_TYPE((yyval).pn, PNT_CONST);
		PSUB_PARSENODE((yyval).pn, struct ConstParseNode)->value.f32 = (yyvsp[(1) - (1)]).f;
		PSUB_PARSENODE((yyval).pn, struct ConstParseNode)->value.type = CT_FLOAT;
	;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 218 "./Hayaku.y"
    {
		(yyval).pn = (yyvsp[(2) - (3)]).pn;
	;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 225 "./Hayaku.y"
    {
		char* name = (yyvsp[(1) - (1)]).name;
		struct IdentifierParseNode* ips = PSUB_PARSENODE((yyvsp[(1) - (1)]).pn, struct IdentifierParseNode);
		char* name2 = ips->name;
		UInt breakHere = 0xABCDEFAB;
	;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 233 "./Hayaku.y"
    {
		// Function call
		PN_ALLOC((yyval).pn, struct CallParseNode);
		PN_SET_TYPE((yyval).pn, PNT_CALL);
		PSUB_PARSENODE((yyval).pn, struct CallParseNode)->function = PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode);
		PSUB_PARSENODE((yyval).pn, struct CallParseNode)->parametersEnd = PSUB_PARSENODE((yyval).pn, struct CallParseNode)->parametersStart;
	;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 241 "./Hayaku.y"
    {
		char* name = (yyvsp[(1) - (4)]).name;
		struct IdentifierParseNode* ips = PSUB_PARSENODE((yyvsp[(1) - (4)]).pn, struct IdentifierParseNode);

		// Function call
		PN_ALLOC((yyval).pn, struct CallParseNode);
		PN_SET_TYPE((yyval).pn, PNT_CALL);
		PSUB_PARSENODE((yyval).pn, struct CallParseNode)->function = PSUB_PARSENODE((yyvsp[(1) - (4)]).pn, struct IdentifierParseNode);
		memcpy(PSUB_PARSENODE((yyval).pn, struct CallParseNode)->parametersStart, (yyvsp[(3) - (4)]).parameters, (yyvsp[(3) - (4)]).numParameters * sizeof(struct ParseNode*));
		PSUB_PARSENODE((yyval).pn, struct CallParseNode)->parametersEnd = PSUB_PARSENODE((yyval).pn, struct CallParseNode)->parametersStart + (yyvsp[(3) - (4)]).numParameters;
	;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 254 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct IdentifierParseNode);
		PN_SET_TYPE((yyval).pn, PNT_IDENTIFIER);
		PSUB_PARSENODE((yyval).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (3)]).name);
		strcpy((yyval).name, (yyvsp[(1) - (3)]).name);
	;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 268 "./Hayaku.y"
    {
		// Add function call parameter
		ADD_FUNCTION_CALL_PARAMETER((yyval), (yyvsp[(1) - (1)]).pn);
	;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 273 "./Hayaku.y"
    {
		// Add function call parameter
		ADD_FUNCTION_CALL_PARAMETER((yyval), (yyvsp[(3) - (3)]).pn);
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 299 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct MulParseNode);
		PN_SET_TYPE((yyval).pn, PNT_MUL);
		PSUB_PARSENODE((yyval).pn, struct MulParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct MulParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 306 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct DivParseNode);
		PN_SET_TYPE((yyval).pn, PNT_DIV);
		PSUB_PARSENODE((yyval).pn, struct MulParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct MulParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 313 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct DivParseNode);
		PN_SET_TYPE((yyval).pn, PNT_DIV);
		PSUB_PARSENODE((yyval).pn, struct MulParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct MulParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 324 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct AddParseNode);
		PN_SET_TYPE((yyval).pn, PNT_ADD);
		PSUB_PARSENODE((yyval).pn, struct AddParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct AddParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 331 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct SubParseNode);
		PN_SET_TYPE((yyval).pn, PNT_SUB);
		PSUB_PARSENODE((yyval).pn, struct SubParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct SubParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 348 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct EqualityParseNode);
		PN_SET_TYPE((yyval).pn, PNT_EQUALITY);
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->eqType = ET_L;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 356 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct EqualityParseNode);
		PN_SET_TYPE((yyval).pn, PNT_EQUALITY);
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->eqType = ET_G;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 364 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct EqualityParseNode);
		PN_SET_TYPE((yyval).pn, PNT_EQUALITY);
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->eqType = ET_LE;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 372 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct EqualityParseNode);
		PN_SET_TYPE((yyval).pn, PNT_EQUALITY);
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->eqType = ET_GE;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 384 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct EqualityParseNode);
		PN_SET_TYPE((yyval).pn, PNT_EQUALITY);
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->eqType = ET_E;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct EqualityParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 427 "./Hayaku.y"
    {
		if (!PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier)
			PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (3)]).name);

		PN_ALLOC((yyval).pn, struct AssignParseNode);
		PN_SET_TYPE((yyval).pn, PNT_ASSIGN);
		PSUB_PARSENODE((yyval).pn, struct AssignParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct AssignParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 437 "./Hayaku.y"
    {
		if (!PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier)
			PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (3)]).name);

		PN_ALLOC((yyval).pn, struct AddAssignParseNode);
		PN_SET_TYPE((yyval).pn, PNT_ADD_ASSIGN);
		PSUB_PARSENODE((yyval).pn, struct AddAssignParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct AddAssignParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 447 "./Hayaku.y"
    {
		if (!PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier)
			PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (3)]).name);

		PN_ALLOC((yyval).pn, struct SubAssignParseNode);
		PN_SET_TYPE((yyval).pn, PNT_SUB_ASSIGN);
		PSUB_PARSENODE((yyval).pn, struct SubAssignParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct SubAssignParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 457 "./Hayaku.y"
    {
		if (!PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier)
			PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (3)]).name);

		PN_ALLOC((yyval).pn, struct MulAssignParseNode);
		PN_SET_TYPE((yyval).pn, PNT_MUL_ASSIGN);
		PSUB_PARSENODE((yyval).pn, struct MulAssignParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct MulAssignParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 467 "./Hayaku.y"
    {
		if (!PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier)
			PSUB_PARSENODE((yyvsp[(1) - (3)]).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (3)]).name);

		PN_ALLOC((yyval).pn, struct DivAssignParseNode);
		PN_SET_TYPE((yyval).pn, PNT_DIV_ASSIGN);
		PSUB_PARSENODE((yyval).pn, struct DivAssignParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct DivAssignParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;
	;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 495 "./Hayaku.y"
    {
		// Should never go here...
		ASSERT(0);
	;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 500 "./Hayaku.y"
    {
		struct IdentifierParseNode* ipn;
		struct VariableType vt = {(yyvsp[(1) - (3)]).vts, 0};

		if ((yyvsp[(2) - (3)]).b)
			ipn = PSUB_PARSENODE(PSUB_PARSENODE((yyvsp[(2) - (3)]).pn, struct AssignParseNode)->arg0, struct IdentifierParseNode);
		else
			ipn = PSUB_PARSENODE((yyvsp[(2) - (3)]).pn, struct IdentifierParseNode);

		if (!ipn->identifier)
		{
			struct Variable* v = AddLocalVariable(vt.specifier, vt.pointerDegree, currentFunction);
			ipn->identifier = AddVariableSymbol(currentFunction, ipn->name, v);
		}

		(yyval).pn = (yyvsp[(2) - (3)]).pn;
	;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 532 "./Hayaku.y"
    {
		(yyval).pn = (yyvsp[(1) - (1)]).pn;
		(yyval).b = FALSE;
	;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 537 "./Hayaku.y"
    {
		// Here we are sending "up" the id parse node without a variable symbol & variable. The upper creates that.
		PN_ALLOC((yyval).pn, struct AssignParseNode);
		PN_SET_TYPE((yyval).pn, PNT_ASSIGN);
		PSUB_PARSENODE((yyval).pn, struct AssignParseNode)->arg0 = (yyvsp[(1) - (3)]).pn;
		PSUB_PARSENODE((yyval).pn, struct AssignParseNode)->arg1 = (yyvsp[(3) - (3)]).pn;

		(yyval).b = TRUE;
	;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 554 "./Hayaku.y"
    { (yyval).vts = VTS_VOID; ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 555 "./Hayaku.y"
    { (yyval).vts = VTS_INT8; ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 556 "./Hayaku.y"
    { (yyval).vts = VTS_INT16; ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 557 "./Hayaku.y"
    { (yyval).vts = VTS_INT32; ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 558 "./Hayaku.y"
    { (yyval).vts = VTS_INT; ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 559 "./Hayaku.y"
    { (yyval).vts = VTS_UINT; ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 560 "./Hayaku.y"
    { (yyval).vts = VTS_FLOAT32; ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 561 "./Hayaku.y"
    { (yyval).vts = VTS_FLOAT64; ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 562 "./Hayaku.y"
    { (yyval).vts = VTS_FLOAT; ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 563 "./Hayaku.y"
    { (yyval).vts = VTS_UINT; ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 636 "./Hayaku.y"
    {
		(yyval).pointerDegree = (yyvsp[(1) - (2)]).pointerDegree;
		strcpy((yyval).name, (yyvsp[(2) - (2)]).name);
	;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 646 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct IdentifierParseNode);
		PN_SET_TYPE((yyval).pn, PNT_IDENTIFIER);
		PSUB_PARSENODE((yyval).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (1)]).name);
		strcpy(PSUB_PARSENODE((yyval).pn, struct IdentifierParseNode)->name, (yyvsp[(1) - (1)]).name);
	;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 662 "./Hayaku.y"
    {
		// Function definition, has parameters. identifier is $1
		UInt i;

		strcpy((yyval).name, (yyvsp[(1) - (4)]).name);
		COPY_C_ARRAY((yyval).parametersDefinitions, (yyval).numParameters,
			         (yyvsp[(3) - (4)]).parametersDefinitions, (yyvsp[(3) - (4)]).numParameters,
					 sizeof(struct VariableType));

		COPY_C_ARRAY((yyval).parametersDefinitionsNames, (yyval).numParameters,
			         (yyvsp[(3) - (4)]).parametersDefinitionsNames, (yyvsp[(3) - (4)]).numParameters,
					 IDENTIFIER_NAME_MAX_LEN);

		COPY_C_ARRAY((yyval).parameters, (yyval).numParameters,
			         (yyvsp[(3) - (4)]).parameters, (yyvsp[(3) - (4)]).numParameters,
					 sizeof(struct ParseNode*));

		for (i = 0; i < (yyval).numParameters; ++i)
		{
			struct Variable* v;

			v = AddLocalParameter((yyval).parametersDefinitions[i].specifier, (yyval).parametersDefinitions[i].pointerDegree, currentFunction);
			AddVariableSymbol(currentFunction, (yyval).parametersDefinitionsNames[i], v);
		}
	;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 688 "./Hayaku.y"
    {
		// Function definition
		char* name = (yyvsp[(1) - (4)]).name;
		UInt breakHere = 0xDEADFACE;
	;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 694 "./Hayaku.y"
    {
		// Function definition
		char* name = (yyvsp[(1) - (3)]).name;
		UInt breakHere = 0xDEADFACE;
	;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 703 "./Hayaku.y"
    {
		++(yyval).pointerDegree;
	;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 707 "./Hayaku.y"
    {
		++(yyval).pointerDegree;
	;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 711 "./Hayaku.y"
    {
		(yyval).pointerDegree = (yyvsp[(2) - (2)]).pointerDegree + 1;
	;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 715 "./Hayaku.y"
    {
		++(yyval).pointerDegree;
	;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 733 "./Hayaku.y"
    {
		// Add parameter
		COPY_C_ARRAY((yyval).parametersDefinitions, (yyval).numParameters,
			         (yyvsp[(1) - (1)]).parametersDefinitions, (yyvsp[(1) - (1)]).numParameters,
					 sizeof(struct VariableType));
		memcpy((yyval).parametersDefinitionsNames, (yyvsp[(1) - (1)]).parametersDefinitionsNames, (yyvsp[(1) - (1)]).numParameters * IDENTIFIER_NAME_MAX_LEN);

		ADD_FUNCTION_DEFINITION_PARAMETER((yyval), (yyvsp[(1) - (1)]).vts, (yyvsp[(1) - (1)]).pointerDegree, (yyvsp[(1) - (1)]).name, (yyvsp[(1) - (1)]).pn);
 	;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 743 "./Hayaku.y"
    {
		// Add parameter
		COPY_C_ARRAY((yyval).parametersDefinitions, (yyval).numParameters,
			         (yyvsp[(1) - (3)]).parametersDefinitions, (yyvsp[(1) - (3)]).numParameters,
					 sizeof(struct VariableType));
		memcpy((yyval).parametersDefinitionsNames, (yyvsp[(1) - (3)]).parametersDefinitionsNames, (yyvsp[(1) - (3)]).numParameters * IDENTIFIER_NAME_MAX_LEN);

		ADD_FUNCTION_DEFINITION_PARAMETER((yyval), (yyvsp[(3) - (3)]).vts, (yyvsp[(3) - (3)]).pointerDegree, (yyvsp[(3) - (3)]).name, (yyvsp[(3) - (3)]).pn);
	;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 756 "./Hayaku.y"
    {
		(yyval).vts = (yyvsp[(1) - (2)]).vts;
		(yyval).pointerDegree = (yyvsp[(2) - (2)]).pointerDegree;
		(yyval).pn = (yyvsp[(2) - (2)]).pn;
		strcpy((yyval).name, (yyvsp[(2) - (2)]).name);
	;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 763 "./Hayaku.y"
    {
		(yyval).vts = (yyvsp[(1) - (2)]).vts;
		(yyval).pointerDegree = (yyvsp[(2) - (2)]).pointerDegree;
	;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 768 "./Hayaku.y"
    {
		enum VARIABLE_TYPE_SPECIFIER vts = (yyvsp[(1) - (1)]).vts;
		UInt pointerDegree = (yyvsp[(1) - (1)]).pointerDegree;
		UInt breakHere = 0xDEADFACE;
	;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 777 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct IdentifierParseNode);
		PN_SET_TYPE((yyval).pn, PNT_IDENTIFIER);
		PSUB_PARSENODE((yyval).pn, struct IdentifierParseNode)->identifier = FindIdentifierSymbol(globalSymbolTable, &currentFunction->symbolTable, (yyvsp[(1) - (1)]).name);
		strcpy((yyval).name, (yyvsp[(1) - (1)]).name);
	;}
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 855 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct CompoundStatementParseNode);
		PN_SET_TYPE((yyval).pn, PNT_COMPOUND_STATEMENT);
		PSUB_PARSENODE((yyval).pn, struct CompoundStatementParseNode)->statements[0] = NULL;
	;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 861 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct CompoundStatementParseNode);
		PN_SET_TYPE((yyval).pn, PNT_COMPOUND_STATEMENT);
		memcpy(PSUB_PARSENODE((yyval).pn, struct CompoundStatementParseNode)->statements,
			(yyvsp[(2) - (3)]).compoundStatement, (yyvsp[(2) - (3)]).numStatements * sizeof(struct ParseNode*));
		PSUB_PARSENODE((yyval).pn, struct CompoundStatementParseNode)->statements[(yyvsp[(2) - (3)]).numStatements] = NULL;
	;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 872 "./Hayaku.y"
    {
		ADD_TO_COMPOUND_STATEMENT((yyval), (yyvsp[(1) - (1)]).pn);
	;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 876 "./Hayaku.y"
    {
		ADD_TO_COMPOUND_STATEMENT((yyval), (yyvsp[(2) - (2)]).pn);
	;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 893 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct IfParseNode);
		PN_SET_TYPE((yyval).pn, PNT_IF);
		PSUB_PARSENODE((yyval).pn, struct IfParseNode)->conditionalExpression = (yyvsp[(3) - (5)]).pn;
		PSUB_PARSENODE((yyval).pn, struct IfParseNode)->bodyCompoundStatement = (yyvsp[(5) - (5)]).pn;
	;}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 905 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct WhileParseNode);
		PN_SET_TYPE((yyval).pn, PNT_WHILE);
		PSUB_PARSENODE((yyval).pn, struct WhileParseNode)->conditionalExpression = (yyvsp[(3) - (5)]).pn;
		PSUB_PARSENODE((yyval).pn, struct WhileParseNode)->bodyCompoundStatement = (yyvsp[(5) - (5)]).pn;
	;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 913 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ForParseNode);
		PN_SET_TYPE((yyval).pn, PNT_FOR);
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->initStatement = (yyvsp[(3) - (6)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->conditionalExpression = (yyvsp[(4) - (6)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->countingStatement = NULL;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->bodyCompoundStatement = (yyvsp[(6) - (6)]).pn;
	;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 922 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ForParseNode);
		PN_SET_TYPE((yyval).pn, PNT_FOR);
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->initStatement = (yyvsp[(3) - (7)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->conditionalExpression = (yyvsp[(4) - (7)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->countingStatement = (yyvsp[(5) - (7)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->bodyCompoundStatement = (yyvsp[(7) - (7)]).pn;
	;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 931 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ForParseNode);
		PN_SET_TYPE((yyval).pn, PNT_FOR);
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->initStatement = (yyvsp[(3) - (6)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->conditionalExpression = (yyvsp[(4) - (6)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->countingStatement = NULL;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->bodyCompoundStatement = (yyvsp[(6) - (6)]).pn;
	;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 940 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ForParseNode);
		PN_SET_TYPE((yyval).pn, PNT_FOR);
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->initStatement = (yyvsp[(3) - (7)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->conditionalExpression = (yyvsp[(4) - (7)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->countingStatement = (yyvsp[(5) - (7)]).pn;
		PSUB_PARSENODE((yyval).pn, struct ForParseNode)->bodyCompoundStatement = (yyvsp[(7) - (7)]).pn;
	;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 955 "./Hayaku.y"
    {
		PLAIN_PN_ALLOC((yyval).pn, PNT_RET_VOID);
	;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 959 "./Hayaku.y"
    {
		PN_ALLOC((yyval).pn, struct ReturnParseNode);
		PN_SET_TYPE((yyval).pn, PNT_RET);
		PSUB_PARSENODE((yyval).pn, struct ReturnParseNode)->returnValue = (yyvsp[(2) - (3)]).pn;
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2951 "C:\\Dev\\Hayaku\\hc\\Source\\yaac.tab.c"
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



/* Line 1675 of yacc.c  */
#line 966 "./Hayaku.y"


void yyerror(const char* s)
{
	fflush(stdout);
	COMPILER_ERRORF("r:%u.c:%u - %s", row, col, s);
}

static void PrintTokenValue(FILE* file, int type, YYSTYPE value)
{
	if (type == IDENTIFIER)
		fprintf(file, "%s", value.name);
	else if (type == INT_CONST)
		fprintf(file, "%d", value.s);
}

#include "lex.yy.c"
