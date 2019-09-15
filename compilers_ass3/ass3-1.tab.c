/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "ass3-1.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <bits/stdc++.h>
	#include "definition.h"
	using namespace std;

	vector<func_name_table> global_func;
	vector<quadruple> quad_table;
	vector<struct_name_table> global_struct;
	variable *vn, *pn, *vnptr, *pnptr;
	int active_func_ptr = -1, call_func_ptr = -1, level = 0, namptr = -1, fnptr = -1,active_struct_ptr = -1,strptr = -1;
	bool found, ok;
	int nextquad = 0, temp_var = 0;

	void yyerror(char *s);
	int yylex();
	int get_size(enum t type);
	void patchtype(enum t type,vector <variable*> &namelist,string name);
	void backpatch(vector<int> list, int quad_number);
	void gen(quadruple quad);
	void newtemp(variable *var);
	void error (string err);
	enum t not_compatible(enum t type);
	enum t compare_types(enum t type1,enum t type2);
	void search_func(string name, bool &found, int &namptr);
	void enter_func(string name, enum t type, int &namptr, string struct_name);
	void search_var(string name, int active_func_ptr, int level, bool &found, variable* &vn);
	void enter_var(string name, int level, int active_func_ptr, variable* &namptr, vector<int> dimlist, int pointer);
	void search_param(string name, int active_func_ptr, bool &found, variable* &pn);
	void delete_var_list(int active_func_ptr, int level);
	void enter_param(string name, enum t type, int active_func_ptr, string struct_name, int pointer, vector<int> dimlist);
	enum t get_result_type(int fnptr);
	void check_param_type(int call_func_ptr, int param_no, variable* var, bool &ok);
	enum t get_variable_type(string name, int active_func_ptr, int level);
	void search_struct(string name,bool &found, int &strptr);
	void enter_struct(string name ,int &strptr);
	void search_struct_var(string name, int active_struct_ptr , bool &found, variable* &vn);
	void enter_struct_var(string name, int active_struct_ptr, variable * &vnptr, vector<int> dimlist, int pointer);
	void conv_float_quad(variable *a,variable *operand1);
	void conv_int_quad(variable *a,variable *operand1);
	void conv_bool_quad(variable *a,variable *operand1);
	bool coercible(enum t type_1, enum t type_2);
	bool compatible_arithop(enum t type_1, enum t type_2);

#line 113 "ass3-1.tab.c" /* yacc.c:339  */

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
    PLUS = 258,
    MINUS = 259,
    STAR = 260,
    SLASH = 261,
    LEFT_CURLY_BRACKET = 262,
    RIGHT_CURLY_BRACKET = 263,
    LEFT_CLOSED_BRACKET = 264,
    RIGHT_CLOSED_BRACKET = 265,
    LEFT_OPEN_BRACKET = 266,
    RIGHT_OPEN_BRACKET = 267,
    IDENTIFIER = 268,
    NUMBER_INT = 269,
    NUMBER_FLOAT = 270,
    TYPEDEF = 271,
    INTEGER = 272,
    FLOAT = 273,
    CHAR = 274,
    VOID = 275,
    STRUCT = 276,
    SEMICOLON = 277,
    OR = 278,
    AND = 279,
    EQUALS = 280,
    LESS_THAN = 281,
    GREATER_THAN = 282,
    IF = 283,
    NOT = 284,
    WHILE = 285,
    CHARACTER = 286,
    QUOT = 287,
    RETURN = 288,
    COMMA = 289,
    ELSE = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 48 "ass3-1.y" /* yacc.c:355  */

	res* reslt;
	string* val;
	variable * var;
	vector<int> *list;
	int int_val;
	float float_val;
	while_struct *wstruct;
	lhs* lhs_var;

#line 197 "ass3-1.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 212 "ass3-1.tab.c" /* yacc.c:358  */

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   109,   110,   111,   114,   120,   135,   142,
     152,   158,   164,   170,   191,   197,   203,   209,   215,   223,
     224,   225,   226,   229,   243,   253,   258,   263,   270,   276,
     277,   281,   284,   295,   304,   310,   316,   322,   330,   344,
     361,   389,   419,   429,   442,   447,   455,   455,   464,   470,
     477,   482,   493,   511,   523,   528,   543,   548,   553,   578,
     596,   601,   608,   642,   674,   710,   734,   776,   833,   898,
     954,   961,   966,  1024,  1029,  1100,  1171,  1242,  1313,  1384,
    1455,  1476,  1547,  1618,  1625,  1696,  1767,  1774,  1784,  1794,
    1817,  1844,  1900,  1925,  1934,  1941,  1986,  1991,  1996,  2013
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PLUS", "MINUS", "STAR", "SLASH",
  "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET", "LEFT_CLOSED_BRACKET",
  "RIGHT_CLOSED_BRACKET", "LEFT_OPEN_BRACKET", "RIGHT_OPEN_BRACKET",
  "IDENTIFIER", "NUMBER_INT", "NUMBER_FLOAT", "TYPEDEF", "INTEGER",
  "FLOAT", "CHAR", "VOID", "STRUCT", "SEMICOLON", "OR", "AND", "EQUALS",
  "LESS_THAN", "GREATER_THAN", "IF", "NOT", "WHILE", "CHARACTER", "QUOT",
  "RETURN", "COMMA", "ELSE", "$accept", "code", "code_do", "struct_decl",
  "str_head", "func_defn_decl", "func_body", "optional_stmt", "func_head",
  "res_id", "result", "decl_plist", "decl_param", "decl_ids", "mult_star",
  "br_param", "dslist", "var_decl", "struct_declaration", "declaration",
  "type", "struct_list_id", "list_id", "id_arr", "br_dimlist", "body",
  "$@1", "stmt_list", "stmt", "n_inter", "m_inter", "matched_stmt",
  "ifexp", "whileexp", "asg", "lhs", "br_elist", "exp", "aa_exp", "d_exp",
  "pm_exp", "t_exp", "f_exp", "func_call", "paramlist", "plist", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -106

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-106)))

#define YYTABLE_NINF -98

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     127,  -106,  -106,  -106,  -106,    -3,    17,  -106,   127,    15,
     127,    42,    26,    60,    81,  -106,  -106,   137,  -106,     8,
    -106,   132,    60,    58,  -106,  -106,  -106,    66,    49,  -106,
      60,  -106,    21,    84,  -106,    40,    89,  -106,  -106,    60,
    -106,    91,  -106,  -106,     8,   100,    92,    90,   113,   103,
    -106,   114,    94,    60,  -106,  -106,  -106,   115,  -106,   116,
     -14,  -106,     8,    87,    79,    87,   128,    87,  -106,  -106,
    -106,   125,   129,   144,    30,   135,  -106,    56,  -106,    72,
    -106,   -10,  -106,     8,  -106,   126,  -106,  -106,    87,   151,
    -106,  -106,   132,  -106,   149,  -106,   154,  -106,    60,   156,
     142,   -16,   155,  -106,    11,    87,    35,   153,    87,    21,
     158,  -106,  -106,   146,   147,   119,   119,   145,    95,   107,
     148,   119,   119,  -106,    60,  -106,   139,   142,    87,  -106,
     163,   161,  -106,  -106,  -106,    87,  -106,  -106,    38,  -106,
     167,   158,    63,   151,    87,    87,  -106,  -106,   119,   119,
     101,   119,   101,   119,  -106,  -106,  -106,  -106,   142,   164,
    -106,   169,  -106,  -106,  -106,   135,  -106,   101,   101,   101,
     101,     8,   170,   154,  -106,   163,  -106,  -106
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,    14,    15,    16,    17,     0,     0,     2,     5,     0,
       5,     0,     0,    26,    18,     1,     3,     0,     4,    11,
       8,    22,    26,     0,    34,    35,    36,     0,     0,    29,
      26,    46,    65,     0,    54,    26,     0,    61,    31,    26,
      60,    54,    49,    50,     0,     0,     0,     0,     0,     0,
      21,     0,    20,    26,    25,    13,    37,     0,    30,     0,
       0,    38,    11,    26,    26,    26,     0,    26,    87,    88,
      59,     0,     0,     0,     0,    70,    71,    73,    83,    86,
       9,     0,    40,     0,    51,    50,    55,    56,    26,    66,
      57,    12,    22,    23,     0,     6,    43,    32,    26,     0,
      68,    99,     0,    96,     0,    26,     0,    90,    26,    89,
      91,    93,    58,     0,     0,    26,    26,     0,    26,    26,
       0,    26,    26,    33,    26,    48,     0,    64,    26,    19,
      28,     0,    42,    39,    47,    26,    95,    62,     0,    94,
       0,    92,     0,     0,    26,    26,    81,    82,    26,    26,
      77,    26,    74,    26,    84,    85,    41,    54,    67,     0,
      24,     0,    98,    63,    80,    69,    72,    76,    78,    79,
      75,     0,     0,    44,    52,    28,    45,    27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,    64,  -106,  -106,  -106,  -106,   120,  -106,  -106,
    -106,    85,  -106,  -106,   -11,     6,  -106,  -106,   157,  -106,
     -12,  -106,  -106,   -35,    10,   141,  -106,  -106,   -44,  -106,
     -40,   140,  -106,  -106,  -106,  -106,   -67,   -32,    43,    44,
    -105,    20,  -106,   117,  -106,    53
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    20,    36,    11,    12,
      13,    51,    52,    93,    73,   160,    28,    37,    29,    38,
      39,    60,    81,    61,   132,    40,    62,    41,    42,   126,
      66,    43,    44,    45,    46,    47,    48,   101,    75,    76,
      77,    78,    79,    49,   102,   103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,    83,    23,    74,    82,    30,   110,   113,    97,    53,
      14,    54,   123,   150,   152,    31,    30,    15,   135,    59,
      98,    32,    17,   137,   124,    24,    25,    26,    59,    27,
      63,   100,    64,   104,   113,   106,    33,    21,    34,   125,
     141,    35,    94,   167,   168,    22,   169,   139,   170,    19,
     163,    67,   112,   113,    68,    69,   127,    57,   113,   115,
     116,   113,    70,   133,    71,    22,    24,    25,    26,    72,
      27,    55,    16,   138,    18,   164,   142,   121,   122,    56,
      53,   117,   118,   119,    22,   120,   113,    59,    -7,   156,
      67,   -97,    22,    68,    69,    65,   158,    80,    67,   -10,
      22,    68,    69,    71,   115,   116,    67,    31,    72,    68,
      69,    71,    22,    59,    87,    88,    72,   171,    67,    71,
     149,    68,    69,    89,    22,    90,    91,   174,    92,    96,
      67,    71,   151,    68,    69,   146,   147,    95,   107,   105,
     108,   154,   155,    71,     1,     2,     3,     4,     5,    24,
      25,    26,    50,    27,    24,    25,    26,   109,    27,   114,
     128,   -53,   130,   131,   134,   113,   140,   136,   143,   144,
     148,   145,   159,   153,   157,   161,    63,   129,   172,   173,
     175,   177,    99,   176,    85,    58,    86,   165,   162,   166,
     111
};

static const yytype_uint8 yycheck[] =
{
      44,    41,    13,    35,    39,    17,    73,    23,    22,    21,
      13,    22,    22,   118,   119,     7,    28,     0,    34,    30,
      34,    13,     7,    12,    34,    17,    18,    19,    39,    21,
       9,    63,    11,    65,    23,    67,    28,    11,    30,    83,
     107,    33,    53,   148,   149,     5,   151,    12,   153,     7,
      12,    11,    22,    23,    14,    15,    88,     8,    23,     3,
       4,    23,    22,    98,    24,     5,    17,    18,    19,    29,
      21,    13,     8,   105,    10,    12,   108,     5,     6,    13,
      92,    25,    26,    27,     5,    29,    23,    98,     7,   124,
      11,    12,     5,    14,    15,    11,   128,     8,    11,     8,
       5,    14,    15,    24,     3,     4,    11,     7,    29,    14,
      15,    24,     5,   124,    22,    25,    29,   157,    11,    24,
      25,    14,    15,    10,     5,    22,    12,   171,    34,    13,
      11,    24,    25,    14,    15,   115,   116,    22,    13,    11,
      11,   121,   122,    24,    17,    18,    19,    20,    21,    17,
      18,    19,    20,    21,    17,    18,    19,    13,    21,    24,
       9,    35,    13,     9,     8,    23,    13,    12,    10,    23,
      25,    24,     9,    25,    35,    14,     9,    92,    14,    10,
      10,   175,    62,   173,    44,    28,    45,   144,   135,   145,
      73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    18,    19,    20,    21,    37,    38,    39,    40,
      41,    44,    45,    46,    13,     0,    38,     7,    38,     7,
      42,    11,     5,    50,    17,    18,    19,    21,    52,    54,
      56,     7,    13,    28,    30,    33,    43,    53,    55,    56,
      61,    63,    64,    67,    68,    69,    70,    71,    72,    79,
      20,    47,    48,    56,    50,    13,    13,     8,    54,    50,
      57,    59,    62,     9,    11,    11,    66,    11,    14,    15,
      22,    24,    29,    50,    73,    74,    75,    76,    77,    78,
       8,    58,    59,    66,    64,    67,    61,    22,    25,    10,
      22,    12,    34,    49,    50,    22,    13,    22,    34,    43,
      73,    73,    80,    81,    73,    11,    73,    13,    11,    13,
      72,    79,    22,    23,    24,     3,     4,    25,    26,    27,
      29,     5,     6,    22,    34,    64,    65,    73,     9,    47,
      13,     9,    60,    59,     8,    34,    12,    12,    73,    12,
      13,    72,    73,    10,    23,    24,    77,    77,    25,    25,
      76,    25,    76,    25,    77,    77,    59,    35,    73,     9,
      51,    14,    81,    12,    12,    74,    75,    76,    76,    76,
      76,    66,    14,    10,    64,    10,    60,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    38,    39,    40,    41,    42,
      43,    43,    44,    45,    46,    46,    46,    46,    46,    47,
      47,    47,    47,    48,    49,    50,    50,    51,    51,    52,
      52,    53,    54,    55,    56,    56,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    62,    61,    63,    63,
      64,    64,    64,    65,    66,    67,    67,    67,    67,    67,
      67,    67,    68,    69,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    76,    77,    77,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    79,    80,    80,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     5,     2,     2,     3,
       1,     0,     4,     3,     1,     1,     1,     1,     2,     3,
       1,     1,     0,     2,     3,     2,     0,     4,     0,     1,
       2,     1,     3,     3,     1,     1,     1,     2,     1,     3,
       1,     3,     3,     2,     3,     4,     0,     4,     3,     1,
       1,     2,     6,     0,     0,     2,     2,     2,     3,     2,
       1,     1,     4,     5,     3,     1,     2,     4,     3,     4,
       1,     1,     4,     1,     3,     4,     4,     3,     4,     4,
       4,     3,     3,     1,     3,     3,     1,     1,     1,     2,
       2,     2,     3,     2,     3,     4,     1,     0,     3,     1
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 100 "ass3-1.y" /* yacc.c:1646  */
    {
														for(int i = 0; i < quad_table.size(); i++)
														{
															quadruple q;
															q = quad_table[i];
															cout<<"L"<<i<<": "<<q.s1<<" "<<q.oprnd_1<<" "<<q.s2<<" "<<q.oprnd_2<<" "<<q.s3<<" "<<q.oprnd_3<<" "<<q.s4<<endl;
														}
													}
#line 1427 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 115 "ass3-1.y" /* yacc.c:1646  */
    {
														active_struct_ptr = -1;
													}
#line 1435 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 121 "ass3-1.y" /* yacc.c:1646  */
    {
														search_struct(*((yyvsp[0].val)),found,strptr);
														if (found)
														{
															error("Structure already declared");
														}
														else 
														{
															enter_struct(*((yyvsp[0].val)),strptr);
														}
														active_struct_ptr = strptr;
													}
#line 1452 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 136 "ass3-1.y" /* yacc.c:1646  */
    {
														active_func_ptr = -1;
														level = 0;
													}
#line 1461 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 143 "ass3-1.y" /* yacc.c:1646  */
    {
														backpatch(*(yyvsp[-1].list), nextquad);
														quadruple q;
														q.s1 = "func end";
														q.oprnd_1 = q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
														gen(q);
													}
#line 1473 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 153 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = (*(yyvsp[0].list));
													}
#line 1482 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 158 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).clear();
													}
#line 1491 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 165 "ass3-1.y" /* yacc.c:1646  */
    {
														level = 2;
													}
#line 1499 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 171 "ass3-1.y" /* yacc.c:1646  */
    {
														search_func(*(yyvsp[0].val), found, namptr);
														if(found)
														{
															error("Function already declared");
														}
														else
														{
															enter_func(*(yyvsp[0].val), (yyvsp[-2].reslt)->type, namptr, (yyvsp[-2].reslt)->struct_name);
															quadruple q;
															q.s1 = "func begin";
															q.oprnd_1 = *(yyvsp[0].val);
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
														}
														active_func_ptr = namptr;
														level = 1;
													}
#line 1522 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 192 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = INT;
														(yyval.reslt)->struct_name = "";
													}
#line 1532 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 198 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = REAL;
														(yyval.reslt)->struct_name = "";
													}
#line 1542 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 204 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = CHA;
														(yyval.reslt)->struct_name = "";
													}
#line 1552 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 210 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = VOI;
														(yyval.reslt)->struct_name = "";
													}
#line 1562 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 216 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = STRUC;
														(yyval.reslt)->struct_name = *(yyvsp[0].val);
													}
#line 1572 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 230 "ass3-1.y" /* yacc.c:1646  */
    {
														search_param((yyvsp[0].var)->name, active_func_ptr, found, pnptr);
														if(found)
														{
															error("Parameter already declared");
														}
														else
														{
															enter_param((yyvsp[0].var)->name, (yyvsp[-1].reslt)->type, active_func_ptr, (yyvsp[-1].reslt)->struct_name, (yyvsp[0].var)->pointer, *((yyvsp[0].var)->dimlist));
														}
													}
#line 1588 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 244 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->name = *((yyvsp[-1].val));
														(yyval.var)->pointer = (yyvsp[-2].int_val);
														(yyval.var)->dimlist = new vector<int>;
														*((yyval.var)->dimlist) = *((yyvsp[0].list));
													}
#line 1600 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 254 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = 1 + (yyvsp[0].int_val);
													}
#line 1608 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 258 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = 0;
													}
#line 1616 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 264 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = *(yyvsp[0].list);
														(*(yyval.list)).insert((*(yyval.list)).begin(), (yyvsp[-2].int_val));
													}
#line 1626 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 270 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).clear();
													}
#line 1635 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 285 "ass3-1.y" /* yacc.c:1646  */
    {
														if((yyvsp[-2].reslt)->type!=STRUC)
															patchtype ((yyvsp[-2].reslt)->type,(yyvsp[-1].reslt)->namelist,"");
														else 
															patchtype((yyvsp[-2].reslt)->type,(yyvsp[-1].reslt)->namelist,(yyvsp[-2].reslt)->struct_name);   //todo //function table variablelist and its level
													}
#line 1646 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 296 "ass3-1.y" /* yacc.c:1646  */
    {
														if((yyvsp[-2].reslt)->type!=STRUC)
															patchtype ((yyvsp[-2].reslt)->type,(yyvsp[-1].reslt)->namelist,"");
														else 
															patchtype((yyvsp[-2].reslt)->type,(yyvsp[-1].reslt)->namelist,(yyvsp[-2].reslt)->struct_name);   //todo //function table variablelist and its level
													}
#line 1657 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 305 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = INT;
														(yyval.reslt)->struct_name = "";
													}
#line 1667 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 311 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = REAL;
														(yyval.reslt)->struct_name = "";
													}
#line 1677 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 317 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = CHA;
														(yyval.reslt)->struct_name = "";
													}
#line 1687 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 323 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.reslt) = new res;
														(yyval.reslt)->type = STRUC;
														(yyval.reslt)->struct_name = *(yyvsp[0].val);
													}
#line 1697 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 331 "ass3-1.y" /* yacc.c:1646  */
    {
														search_struct_var(((yyvsp[0].var))->name, active_struct_ptr, found, vn);
														(yyval.reslt)=new res;
														if(found)
														{
															error("Variable already declared in the structure");
														}
														else
														{
															enter_struct_var(((yyvsp[0].var))->name, active_struct_ptr, vnptr, *(((yyvsp[0].var))->dimlist), (yyvsp[0].var)->pointer);
															((yyval.reslt)->namelist).push_back(vnptr);
														}
													}
#line 1715 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 345 "ass3-1.y" /* yacc.c:1646  */
    {
														search_struct_var(((yyvsp[0].var))->name, active_struct_ptr, found, vn);
														(yyval.reslt)=new res;
														(yyval.reslt)->namelist = (yyvsp[-2].reslt)->namelist;
														if(found)
														{
															error("Variable already declared in the structure");
														}																	
														else
														{
															enter_struct_var(((yyvsp[0].var))->name, active_struct_ptr, vnptr, *(((yyvsp[0].var))->dimlist), (yyvsp[0].var)->pointer);
															((yyval.reslt)->namelist).push_back(vnptr);
														}
													}
#line 1734 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 362 "ass3-1.y" /* yacc.c:1646  */
    {
														search_var(((yyvsp[0].var))->name, active_func_ptr, level, found, vn);
														(yyval.reslt)=new res;
														
														if(found && vn->level == level)
														{
															error("Variable already declared at same level");
														}
														else if(level == 2)
														{
															search_param(((yyvsp[0].var))->name, active_func_ptr, found, pn);
															if(found)
															{
																error("Redeclaration of parameter as a variable");
															}
															else
															{
																enter_var(((yyvsp[0].var))->name, level, active_func_ptr, vnptr, *(((yyvsp[0].var))->dimlist), ((yyvsp[0].var))->pointer);
																((yyval.reslt)->namelist).push_back(vnptr);
															}
														}
														else
														{
															enter_var(((yyvsp[0].var))->name, level, active_func_ptr, vnptr, *(((yyvsp[0].var))->dimlist), ((yyvsp[0].var))->pointer);
															((yyval.reslt)->namelist).push_back(vnptr);
														}
													}
#line 1766 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 390 "ass3-1.y" /* yacc.c:1646  */
    {
														search_var(((yyvsp[0].var))->name, active_func_ptr, level, found, vn);
														(yyval.reslt)=new res;
														(yyval.reslt)->namelist = (yyvsp[-2].reslt)->namelist;
														if(found && vn->level == level)
														{
															error("Variable already declared at same level");
														}
														else if(level == 2)
														{
															search_param(((yyvsp[0].var))->name, active_func_ptr, found, pn);
															if(found)
															{
																error("Redeclaration of parameter as a variable");
															}
															else
															{
																enter_var(((yyvsp[0].var))->name, level, active_func_ptr, vnptr, *(((yyvsp[0].var))->dimlist), ((yyvsp[0].var))->pointer);
																((yyval.reslt)->namelist).push_back(vnptr);
															}
														}
														else
														{
															enter_var(((yyvsp[0].var))->name, level, active_func_ptr, vnptr, *(((yyvsp[0].var))->dimlist), ((yyvsp[0].var))->pointer);
															((yyval.reslt)->namelist).push_back(vnptr);
														}
													}
#line 1798 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 420 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->name = *(yyvsp[-1].val);
														(yyval.var)->type = 1;
														(yyval.var)->pointer = (yyvsp[-2].int_val);
														(yyval.var)->dimlist = new vector<int>;
														// $$->var_type = 1; 
														*((yyval.var)->dimlist) = *((yyvsp[0].list));
													}
#line 1812 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 430 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->name = *(yyvsp[0].val);
														(yyval.var)->type = 0;
														(yyval.var)->pointer = (yyvsp[-1].int_val);
														(yyval.var)->dimlist = new vector<int>;
														(*((yyval.var)->dimlist)).clear();
														// $$->var_type = 1;    //todo level 
													}
#line 1826 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 443 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).insert((*(yyval.list)).begin(),(yyvsp[-1].int_val));
													}
#line 1835 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 448 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = *(yyvsp[0].list);
														(*(yyval.list)).insert((*(yyval.list)).begin(),(yyvsp[-2].int_val));
													}
#line 1845 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 455 "ass3-1.y" /* yacc.c:1646  */
    {level++;}
#line 1851 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 456 "ass3-1.y" /* yacc.c:1646  */
    {
														delete_var_list(active_func_ptr, level);
														level--;
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = (*(yyvsp[-1].list));
													}
#line 1862 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 465 "ass3-1.y" /* yacc.c:1646  */
    {
														backpatch(*(yyvsp[-2].list), (yyvsp[-1].int_val));
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = (*(yyvsp[0].list));
													}
#line 1872 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 471 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														*((yyval.list)) = *((yyvsp[0].list));
													}
#line 1881 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 478 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = (*(yyvsp[0].list));
													}
#line 1890 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 483 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														// (*$$).reserve((*$1).size() + (*$2).size());
														for(int i =0;i<(*(yyvsp[0].list)).size();i++)
															(*(yyval.list)).push_back((*(yyvsp[0].list))[i]);
														for(int i =0;i<(*(yyvsp[-1].list)).size();i++)
															(*(yyval.list)).push_back((*(yyvsp[-1].list))[i]);
														// (*$$).insert((*$$).end(), (*$2).begin(), (*$2).end());
														// (*$$).insert((*$$).end(), (*$1).begin(), (*$1).end());
													}
#line 1905 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 494 "ass3-1.y" /* yacc.c:1646  */
    {
														backpatch(*(yyvsp[-5].list), (yyvsp[-1].int_val));
														(yyval.list) = new vector<int>;
														for(int i =0;i<(*(yyvsp[-4].list)).size();i++)
															(*(yyval.list)).push_back((*(yyvsp[-4].list))[i]);
														for(int i =0;i<(*(yyvsp[-3].list)).size();i++)
															(*(yyval.list)).push_back((*(yyvsp[-3].list))[i]);
														for(int i =0;i<(*(yyvsp[0].list)).size();i++)
															(*(yyval.list)).push_back((*(yyvsp[0].list))[i]);
														// (*$$).reserve((*$2).size() + (*$3).size() + (*$6).size());
														// (*$$).insert((*$$).end(), (*$2).begin(), (*$2).end());
														// (*$$).insert((*$$).end(), (*$3).begin(), (*$3).end());
														// (*$$).insert((*$$).end(), (*$6).begin(), (*$6).end());
													}
#line 1924 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 511 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).push_back(nextquad);
														quadruple q;
														q.s1 = "goto";
														q.oprnd_1 = "__";
														q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
														gen(q);
													}
#line 1938 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 523 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = nextquad;
													}
#line 1946 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 529 "ass3-1.y" /* yacc.c:1646  */
    {
														quadruple q;
														q.s1 = "goto";
														q.oprnd_1 = (yyvsp[-1].wstruct)->begin;
														q.s2 = "";
														q.oprnd_2 = "0";
														q.s3 = "";
														q.oprnd_3 = "";
														q.s4 = "";
														gen(q);
														backpatch(*(yyvsp[0].list), (yyvsp[-1].wstruct)->begin);
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = ((yyvsp[-1].wstruct)->falselist);
													}
#line 1965 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 544 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).clear();
													}
#line 1974 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 549 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).clear();
													}
#line 1983 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 554 "ass3-1.y" /* yacc.c:1646  */
    {
														enum t type = get_result_type(active_func_ptr);
														if(type != (yyvsp[-1].var)->eletype)
														{
															error("Return type mismatch");
														}
														else
														{
															if((type != STRUC) || ((yyvsp[-1].var)->struct_name == global_func[active_func_ptr].struct_name))
															{
																quadruple q;
																q.s1 = "return";
																q.oprnd_1 = (yyvsp[-1].var)->name;
																q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
																gen(q);
																(yyval.list) = new vector<int>;
																(*(yyval.list)).clear();
															}
															else
															{
																error("Return type mismatch");
															}
														}
													}
#line 2012 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 579 "ass3-1.y" /* yacc.c:1646  */
    {
														enum t type = get_result_type(active_func_ptr);
														if(type != VOI)
														{
															error("Return type mismatch");
														}
														else
														{
															quadruple q;
															q.s1 = "return";
															q.oprnd_1 = "";
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
															(yyval.list) = new vector<int>;
															(*(yyval.list)).clear();
														}
													}
#line 2034 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 597 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)) = (*(yyvsp[0].list));
													}
#line 2043 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 602 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														(*(yyval.list)).clear();
													}
#line 2052 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 609 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.list) = new vector<int>;
														if((yyvsp[-1].var)->eletype==ERRORTYPE)
														{
															error("Wrong type in IF statement");
														}
														else
														{
															(*(yyval.list)).clear();
															(*(yyval.list)).push_back(nextquad);
															quadruple q;
															variable *operand1;
															operand1 = new variable;
															if((yyvsp[-1].var)->eletype != INT)
															{
																conv_int_quad((yyvsp[-1].var),operand1);
															}
															else
															{
																*operand1 = *(yyvsp[-1].var);
															}
															q.s1 = "if";
															q.oprnd_1 = operand1->name;
															q.s2 = "<=";
															q.oprnd_2 = "0";
															q.s3 = "goto";
															q.oprnd_3 = "__";
															q.s4 = "";
															gen(q);
														}
													}
#line 2088 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 643 "ass3-1.y" /* yacc.c:1646  */
    {
														if((yyvsp[-1].var)->eletype==ERRORTYPE)
															error("Wrong type in WHILE statement");
														else
														{
															(yyval.wstruct) = new while_struct;
															((yyval.wstruct)->falselist).push_back(nextquad);
															quadruple q;
															variable *operand1;
															operand1 = new variable;
															if((yyvsp[-1].var)->eletype != INT)
															{
																conv_int_quad((yyvsp[-1].var),operand1);
															}
															else
															{
																*operand1 = *(yyvsp[-1].var);
															}
															q.s1 = "if";
															q.oprnd_1 = operand1->name;
															q.s2 = "<=";
															q.oprnd_2 = "0";
															q.s3 = "goto";
															q.oprnd_3 = "__";
															q.s4 = "";
															gen(q);
															(yyval.wstruct)->begin = (yyvsp[-3].int_val);
														}
													}
#line 2122 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 675 "ass3-1.y" /* yacc.c:1646  */
    {
														if(((yyvsp[-2].lhs_var)->place)->eletype!=ERRORTYPE && (yyvsp[0].var)->eletype!=ERRORTYPE)
														{	
															if(!coercible(((yyvsp[-2].lhs_var)->place)->eletype , (yyvsp[0].var)->eletype))
																	error("TYPE MISMATCH");
															else if((*((yyvsp[-2].lhs_var)->place->dimlist)).size() == 0)
															{
																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyvsp[-2].lhs_var)->place->name;
																q.s2 = "=";
																q.oprnd_2 = (yyvsp[0].var)->name;
																q.s3 = q.oprnd_3 = q.s4 = "";
																gen(q);
															}
															else
															{
																quadruple q;
																q.s1 = "";
																q.oprnd_1 = ((yyvsp[-2].lhs_var)->place)->name;
																q.s2 = "[";
																q.oprnd_2 = ((yyvsp[-2].lhs_var)->offset)->name;
																q.s3 = "]";
																q.oprnd_3 = (yyvsp[0].var)->name;
																q.s4 = "";
																gen(q);
															}
														}
														else 
														{
															//
														}
													}
#line 2160 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 711 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.lhs_var) = new lhs;
														(yyval.lhs_var)->offset = NULL;
														(yyval.lhs_var)->place = new variable;
														search_var(*(yyvsp[0].val), active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*(yyvsp[0].val), active_func_ptr, found, pn);
															if(!found)
															{
																((yyval.lhs_var)->place)->eletype = ERRORTYPE;
																error("Identifier " + *(yyvsp[0].val) + " not declared");
															}
															else
															{
																*((yyval.lhs_var)->place) = *pn;
															}
														}
														else
														{
															*((yyval.lhs_var)->place) = *vn;
														}
													}
#line 2188 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 735 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.lhs_var) = new lhs;
														(yyval.lhs_var)->place = new variable;
														*((yyval.lhs_var)->place) = *((yyvsp[-1].lhs_var)->place);
														(yyval.lhs_var)->offset = new variable;
														((yyval.lhs_var)->offset)->eletype = INT;
														((yyval.lhs_var)->offset)->type = 0;
														((yyval.lhs_var)->offset)->level = level;
														((yyval.lhs_var)->offset)->struct_name = "";
														newtemp((yyval.lhs_var)->offset);
														quadruple q;
														q.s1 = "";
														q.oprnd_1 = ((yyval.lhs_var)->offset)->name;
														q.s2 = "=";
														q.oprnd_2 = ((yyvsp[-1].lhs_var)->offset)->name;
														q.s3 = "*";
														q.oprnd_3 = get_size(((yyval.lhs_var)->place)->eletype);
														q.s4 = "";
														gen(q);
														// search_var(*$1, active_func_ptr, level, found, vn);
														// if(!found)
														// {
														// 	search_param(*$1, active_func_ptr, found, pn);
														// 	if(!found)
														// 	{
														// 		$$->eletype = ERRORTYPE;
														// 		error("Identifier " + *$1 + " not declared");
														// 	}
														// 	else
														// 	{
														// 		*($$->place) = *pn;
														// 	}
														// }
														// else
														// {
														// 	*($$->place) = *vn;
														// }
														// *($$->offset) = *$2;
													}
#line 2232 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 777 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.lhs_var) = new lhs;
														(yyval.lhs_var)->dimnum = (yyvsp[-3].lhs_var)->dimnum + 1;
														(yyval.lhs_var)->place = new variable;
														*((yyval.lhs_var)->place) = *((yyvsp[-3].lhs_var)->place);
														int num_elem;
														search_var(((yyvsp[-3].lhs_var)->place)->name, active_func_ptr, level, found, vn);
														if(found)
														{
															if((*(vn->dimlist)).size() >= (yyval.lhs_var)->dimnum)
																num_elem = (*(vn->dimlist))[(yyval.lhs_var)->dimnum];
															else
															{
																error("Dimension given high.");
															}
														}
														else
														{
															search_param(((yyvsp[-3].lhs_var)->place)->name, active_func_ptr, found, pn);
															if(found)
															{
																if((*(pn->dimlist)).size() >= (yyval.lhs_var)->dimnum)
																	num_elem = (*(pn->dimlist))[(yyval.lhs_var)->dimnum];
																else
																{
																	error("Dimension given high.");
																}
															}
														}
														((yyval.lhs_var)->offset) = new variable;
														((yyval.lhs_var)->offset)->type = 0;
														((yyval.lhs_var)->offset)->eletype = INT;
														((yyval.lhs_var)->offset)->struct_name = "";
														((yyval.lhs_var)->offset)->level = level;
														newtemp((yyval.lhs_var)->offset);
														variable *temp = new variable;
														temp->type = 0;
														temp->eletype = INT;
														temp->struct_name = "";
														temp->level = level;
														newtemp(temp);
														quadruple q;
														q.s1 = "";
														q.oprnd_1 = temp->name;
														q.s2 = "=";
														q.oprnd_2 = ((yyvsp[-3].lhs_var)->offset)->name;
														q.s3 = "*";
														q.oprnd_3 = num_elem;
														q.s4 = "";
														gen(q);
														q.oprnd_1 = ((yyval.lhs_var)->offset)->name;
														q.oprnd_2 = temp->name;
														q.s3 = "+";
														q.oprnd_3 = (yyvsp[0].var)->name;
														gen(q);
													}
#line 2293 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 834 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.lhs_var) = new lhs;
														(yyval.lhs_var)->dimnum = 1;
														(yyval.lhs_var)->place = new variable;
														(yyval.lhs_var)->offset = new variable;
														search_var(*(yyvsp[-2].val), active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*(yyvsp[-2].val), active_func_ptr, found, pn);
															if(!found)
															{
																((yyval.lhs_var)->place)->eletype = ERRORTYPE;
																error("Identifier " + *(yyvsp[-2].val) + " not declared");
															}
															else
															{
																*((yyval.lhs_var)->place) = *pn;
															}
														}
														else
														{
															*((yyval.lhs_var)->place) = *vn;
														}
														if((*((yyval.lhs_var)->place->dimlist)).size() > 0)
															*((yyval.lhs_var)->offset) = *(yyvsp[0].var);
														else
														{
															error(*(yyvsp[-2].val) + "can't be indexed");
														}
													}
#line 2328 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 899 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-3].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));


																if((yyvsp[-3].var)->eletype!=BOOL)
																{
																	conv_bool_quad((yyvsp[-3].var),operand1);
																}
																else
																{
																	*operand1 = *(yyvsp[-3].var);	
																}

																if((yyvsp[0].var)->eletype!=BOOL)
																{
																	conv_bool_quad((yyvsp[0].var),operand2);
																}
																else
																{
																	*operand2 = *(yyvsp[0].var);	
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "||";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2388 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 955 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[0].var);
													}
#line 2397 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 962 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[0].var);
													}
#line 2406 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 967 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-3].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));


																if((yyvsp[-3].var)->eletype!=BOOL)
																{
																	conv_bool_quad((yyvsp[-3].var),operand1);
																}
																else
																{
																	*operand1 = *(yyvsp[-3].var);	
																}

																if((yyvsp[0].var)->eletype!=BOOL)
																{
																	conv_bool_quad((yyvsp[0].var),operand2);
																}
																else
																{
																	*operand2 = *(yyvsp[0].var);	
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "&&";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2466 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1025 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[0].var);
													}
#line 2475 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1030 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-2].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-2].var)->eletype == INT && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var), operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyvsp[0].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var),operand1);
																}
																else 
																{
																	*operand1 = *(yyvsp[-2].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyvsp[-2].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-2].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-2].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else 
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = ">";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2550 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1101 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-3].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-3].var)->eletype == INT && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var), operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var),operand1);
																}
																else 
																{
																	*operand1 = *(yyvsp[-3].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else 
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "!=";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2625 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1172 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-3].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-3].var)->eletype == INT && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var), operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == (yyvsp[0].var)->eletype)
																{
																	*operand1 = *(yyvsp[-3].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyvsp[-3].var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "==";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2700 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1243 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-2].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-2].var)->eletype == INT && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var), operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyvsp[0].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var),operand1);
																}
																else
																{
																	*operand1 = *(yyvsp[-2].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyvsp[-2].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-2].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-2].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "<";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2775 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1314 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-3].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-3].var)->eletype == INT && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var), operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == (yyvsp[0].var)->eletype)
																{
																	*operand1 = *(yyvsp[-3].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyvsp[-3].var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "<=";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2850 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1385 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-3].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-3].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = BOOL;
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-3].var)->eletype == INT && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var), operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == CHA && (yyvsp[0].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-3].var),operand1);
																}
																else if((yyvsp[-3].var)->eletype == (yyvsp[0].var)->eletype)
																{
																	*operand1 = *(yyvsp[-3].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyvsp[-3].var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyvsp[-3].var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = ">=";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 2925 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1456 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[-1].var);
														(yyval.var)->type = ((yyvsp[-1].var)->eletype == ERRORTYPE) ? ERRORTYPE : BOOL;
														newtemp((yyval.var));
														if((yyval.var)->type != ERRORTYPE)
														{
															quadruple q;
															q.s1 = "";
															q.oprnd_1 = (yyval.var)->name;
															q.s2 = "= !";
															q.oprnd_2 = (yyvsp[-1].var)->name;
															q.s3 = "";
															q.oprnd_3 = "";
															q.s4 = "";
															gen(q);
														}
													}
#line 2948 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1477 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-2].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = compare_types((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype);
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-2].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var), operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == (yyval.var)->eletype)
																{
																	*operand1 = *(yyvsp[-2].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyval.var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "+";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 3023 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1548 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-2].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = compare_types((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype);
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-2].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var), operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == (yyval.var)->eletype)
																{
																	*operand1 = *(yyvsp[-2].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyval.var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "-";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 3098 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1619 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[0].var);
													}
#line 3107 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1626 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-2].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = compare_types((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype);
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-2].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var), operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == (yyval.var)->eletype)
																{
																	*operand1 = *(yyvsp[-2].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyval.var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "*";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 3182 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1697 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if((yyvsp[-2].var)->eletype != ERRORTYPE && (yyvsp[0].var)->eletype != ERRORTYPE)
														{
															if(!coercible((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype) || !compatible_arithop((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype))
															{
																error("Type mismatch");
																(yyval.var)->eletype = ERRORTYPE;
															}
															else
															{
																(yyval.var)->eletype = compare_types((yyvsp[-2].var)->eletype, (yyvsp[0].var)->eletype);
																(yyval.var)->type = 0;
																(yyval.var)->struct_name = "";
																(yyval.var)->level = level;
																newtemp((yyval.var));

																if((yyvsp[-2].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var), operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[-2].var),operand1);
																}
																else if((yyvsp[-2].var)->eletype == (yyval.var)->eletype)
																{
																	*operand1 = *(yyvsp[-2].var);
																}

																if((yyvsp[0].var)->eletype == INT && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var), operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == INT)
																{
																	conv_int_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == CHA && (yyval.var)->eletype == REAL)
																{
																	conv_float_quad((yyvsp[0].var),operand2);
																}
																else if((yyvsp[0].var)->eletype == (yyval.var)->eletype)
																{
																	*operand2 = *(yyvsp[0].var);
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "/";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															(yyval.var)->eletype = ERRORTYPE;
														}
													}
#line 3257 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1768 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[0].var);
													}
#line 3266 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1775 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->eletype = INT;
														(yyval.var)->name = to_string((yyvsp[0].int_val));
														(yyval.var)->type = 0;
														(yyval.var)->dimlist = NULL;
														(yyval.var)->level = 1;
														(yyval.var)->struct_name = "";
													}
#line 3280 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1785 "ass3-1.y" /* yacc.c:1646  */
    {	
														(yyval.var) = new variable;
														(yyval.var)->eletype = REAL;
														(yyval.var)->name = to_string((yyvsp[0].float_val));
														(yyval.var)->type = 0;
														(yyval.var)->dimlist = NULL;
														(yyval.var)->level = 1;
														(yyval.var)->struct_name = "";
													}
#line 3294 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1795 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->pointer = 1;
														search_var(*(yyvsp[0].val), active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*(yyvsp[0].val), active_func_ptr, found, pn);
															if(!found)
															{
																(yyval.var)->eletype = ERRORTYPE;
																error("Identifier " + *(yyvsp[0].val) + " not declared");
															}
															else
															{
																(*(yyval.var)) = *pn;
															}
														}
														else
														{
															*(yyval.var) = *vn;
														}
													}
#line 3321 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1818 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->pointer = 0;
														search_var(*(yyvsp[0].val), active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*(yyvsp[0].val), active_func_ptr, found, pn);
															if(!found)
															{
																(yyval.var)->eletype = ERRORTYPE;
																error("Identifier " + *(yyvsp[0].val) + " not declared");
															}
															else
															{
																//$$->eletype = pn->eletype;
																(*(yyval.var)) = *pn;
																(yyval.var)->pointer = pn->pointer + 1;
															}
														}
														else
														{
															//$$->pointer = vn->pointer + 1;
															(*(yyval.var)) = *vn;
															(yyval.var)->eletype = vn->eletype;
														}
													}
#line 3352 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1845 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->pointer = (yyvsp[-1].int_val);
														search_var((yyvsp[0].lhs_var)->place->name, active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param((yyvsp[0].lhs_var)->place->name, active_func_ptr, found, pn);
															if(!found)
															{
																(yyval.var)->eletype = ERRORTYPE;
																error("Identifier " + (yyvsp[0].lhs_var)->place->name + " not declared");
															}
															else
															{
																(yyval.var)->eletype = pn->eletype;
																(yyval.var)->pointer = pn->pointer - (yyvsp[-1].int_val);
															}
														}
														else
														{
															(yyval.var)->pointer = vn->pointer - (yyvsp[-1].int_val);
															(yyval.var)->eletype = vn->eletype;
														}

														if((yyval.var)->eletype != ERRORTYPE)
														{
															(yyval.var)->type = 0;
															(yyval.var)->level = level;
															(yyval.var)->struct_name = "";
															variable *temp = new variable;
															temp->type = 0;
															temp->eletype = INT;
															temp->struct_name = "";
															temp->level = level;
															newtemp(temp);
															quadruple q;
															q.s1 = "";
															q.oprnd_1 = temp->name;
															q.s2 = "=";
															q.oprnd_2 = (yyvsp[0].lhs_var)->offset->name;
															q.s3 = "*";
															q.oprnd_3 = get_size((yyval.var)->eletype);
															q.s4 = "";
															gen(q);
															newtemp((yyval.var));
															q.s1 = "";
															q.oprnd_1 = (yyval.var)->name;
															q.s2 = "=";
															q.oprnd_2 = (yyvsp[0].lhs_var)->place->name;
															q.s3 = "[";
															q.oprnd_3 = temp->name;
															q.s4 = "]";
															gen(q);
														}
													}
#line 3412 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1901 "ass3-1.y" /* yacc.c:1646  */
    {
														// $$ = new variable;
														// $$->pointer = 0;
														// search_var($2->place->name, active_func_ptr, level, found, vn);
														// if(!found)
														// {
														// 	search_param($2->place->name, active_func_ptr, found, pn);
														// 	if(!found)
														// 	{
														// 		$$->eletype = ERRORTYPE;
														// 		error("Identifier " + *$2 + " not declared");
														// 	}
														// 	else
														// 	{
														// 		$$->eletype = pn->eletype;
														// 		$$->pointer = pn->pointer + 1;
														// 	}
														// }
														// else
														// {
														// 	$$->pointer = vn->pointer + 1;
														// 	$$->eletype = vn->eletype;
														// }
													}
#line 3441 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1926 "ass3-1.y" /* yacc.c:1646  */
    {//pointers to be handled
														if((yyvsp[-1].int_val) > 0)
														{
															error("Invalid");//to be more precise
														}
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[0].var);
													}
#line 3454 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1935 "ass3-1.y" /* yacc.c:1646  */
    {//pointers
														(yyval.var) = new variable;
														*(yyval.var) = *(yyvsp[-1].var);
													}
#line 3463 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1942 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.var) = new variable;
														(yyval.var)->type = 0;
														search_func(*(yyvsp[-3].val), found, fnptr);
														if(!found)
														{
															(yyval.var)->eletype = ERRORTYPE;
															error("Function not declared");
															call_func_ptr = -1;
														}
														else
														{
															(yyval.var)->eletype = get_result_type(fnptr);
															if((yyval.var)->eletype == STRUC)
															{
																(yyval.var)->struct_name = global_func[fnptr].struct_name;
															}
															else
															{
																(yyval.var)->struct_name = "";
															}
															call_func_ptr = fnptr;
															if(global_func[call_func_ptr].num_param != ((yyvsp[-1].int_val)))
															{
																error("Mismatch in number of parameters");
															}
															else
															{
																newtemp((yyval.var));
																quadruple q;
																q.s1 = "refparam";
																q.oprnd_1 = (yyval.var)->name;
																q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
																gen(q);
																q.s1 = "call";
																q.oprnd_1 = *(yyvsp[-3].val);
																q.s2 = "";
																q.oprnd_2 = (yyvsp[-1].int_val) + 1;
																q.s3 = q.oprnd_3 = q.s4 = "";
															}
														}
													}
#line 3510 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1987 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = (yyvsp[0].int_val);
													}
#line 3518 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1991 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = 0;
													}
#line 3526 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1997 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = (yyvsp[0].int_val) + 1;
														check_param_type(call_func_ptr, (yyval.int_val), (yyvsp[-2].var), ok);
														if(!ok)
														{
															error("Parameter type mismatch");
														}
														else
														{
															quadruple q;
															q.s1 = "param";
															q.oprnd_1 = (yyvsp[-2].var)->name;
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
														}
													}
#line 3547 "ass3-1.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 2014 "ass3-1.y" /* yacc.c:1646  */
    {
														(yyval.int_val) = 1;
														check_param_type(call_func_ptr, 1, (yyvsp[0].var), ok);
														if(!ok)
														{
															error("Parameter type mismatch");
														}
														else
														{
															quadruple q;
															q.s1 = "param";
															q.oprnd_1 = (yyvsp[0].var)->name;
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
														}
													}
#line 3568 "ass3-1.tab.c" /* yacc.c:1646  */
    break;


#line 3572 "ass3-1.tab.c" /* yacc.c:1646  */
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 2034 "ass3-1.y" /* yacc.c:1906  */


void yyerror(char *s)
{
	printf("ERROR: %s\n",s);
}
int main()
{
	return yyparse();
}

void conv_float_quad(variable *a,variable *operand1)
{
	operand1->eletype = REAL;
	operand1->type = 0;
	operand1->level = level;
	operand1->struct_name = "";
	newtemp(operand1);
	quadruple q;
	q.s1 = "";
	q.oprnd_1 = operand1->name;
	q.s2 = "= cnvrt_float(";
	q.oprnd_2 = a->name;
	q.s3 = ")";
	q.oprnd_3 = q.s4 = "";
	gen(q);
}

void conv_int_quad(variable *a,variable *operand1)
{
	operand1->eletype = INT;
	operand1->type = 0;
	operand1->level = level;
	operand1->struct_name = "";
	newtemp(operand1);
	quadruple q;
	q.s1 = "";
	q.oprnd_1 = operand1->name;
	q.s2 = "= cnvrt_int(";
	q.oprnd_2 = a->name;
	q.s3 = ")";
	q.oprnd_3 = q.s4 = "";
	gen(q);
}

void conv_bool_quad(variable *a,variable *operand1)
{
	operand1->eletype = BOOL;
	operand1->type = 0;
	operand1->level = level;
	operand1->struct_name = "";
	newtemp(operand1);
	quadruple q;
	q.s1 = "";
	q.oprnd_1 = operand1->name;
	q.s2 = "= cnvrt_bool(";
	q.oprnd_2 = a->name;
	q.s3 = ")";
	q.oprnd_3 = q.s4 = "";
	gen(q);
}

bool coercible(enum t type_1, enum t type_2)
{
	if((type_1==INT || type_1 == CHA || type_1 == REAL || type_1 == BOOL) &&
		(type_2==INT || type_2 == CHA || type_2 == REAL || type_2 == BOOL))
		return true;
	return false;
}

bool compatible_arithop(enum t type_1, enum t type_2)
{
	if((type_1==INT || type_1 == CHA || type_1 == REAL) &&
		(type_2==INT || type_2 == CHA || type_2 == REAL))
		return true;
	return false;
}

void patchtype(enum t type,vector <variable*> &namelist,string name)
{
	for(int i=0;i<namelist.size();i++)
	{
		namelist[i]->eletype = type;
		if(type==STRUC)
		{
			namelist[i]->struct_name = name;
		}
	}
}
void error (string err)
{
	cout<<err<<endl;

}

enum t not_compatible(enum t type)
{
	if(type == ERRORTYPE || type == REAL)
		return ERRORTYPE;
	else
		return type;
}

enum t compare_types(enum t type1,enum t type2)
{
	if(type1 == REAL || type2 == REAL)
		return REAL;
	else if(type1 == INT || type2 == INT)
		return INT;
	else if(type1 == CHA || type2 == CHA)
		return CHA;
}

void search_func(string name, bool &found, int &namptr)
{
	found = false;
	namptr = -1;
	for(int i = 0; i < global_func.size(); i++)
	{
		if(global_func[i].name == name)
		{
			found = true;
			namptr = i;
			return;
		}
	}
}

void enter_func(string name, enum t type, int &namptr, string struct_name)
{
	func_name_table temp;
	temp.name = name;
	temp.res_type = type;
	temp.num_param = 0;
	temp.param_list.clear();
	temp.var_list.clear();
	temp.struct_name = struct_name;
	global_func.push_back(temp);
	namptr = global_func.size() - 1;
}

bool compare(variable &a, variable &b)
{
	if(a.level < b.level)
		return true;
	return false;
}

void search_var(string name, int active_func_ptr, int level, bool &found, variable* &vn)
{
	found = false;
	vn = NULL;
	int cur_level = -1;
	// sort(global_func[active_func_ptr].var_list.begin(), global_func[active_func_ptr].var_list.end(), compare);
	for(int i = global_func[active_func_ptr].var_list.size() - 1; i >= 0; i--)
	{
		if(level < global_func[active_func_ptr].var_list[i].level)
		{
			continue;
		}
		if(global_func[active_func_ptr].var_list[i].name == name)
		{
			if(cur_level < global_func[active_func_ptr].var_list[i].level)
			{
				cur_level = global_func[active_func_ptr].var_list[i].level;
				vn = &global_func[active_func_ptr].var_list[i];
				found = true;
			}
		}
	}
}

void enter_var(string name, int level, int active_func_ptr, variable* &namptr, vector<int> dimlist, int pointer)
{
	variable temp;
	temp.name = name;
	temp.level = level;
	temp.pointer = pointer;
	temp.dimlist = new vector<int>;
	*temp.dimlist = dimlist;
	global_func[active_func_ptr].var_list.push_back(temp);
	namptr = &global_func[active_func_ptr].var_list[global_func[active_func_ptr].var_list.size() - 1];
}

void search_param(string name, int active_func_ptr, bool &found, variable* &pn)
{
	found = false;
	namptr = -1;
	for(int i = 0; i < global_func[active_func_ptr].param_list.size(); i++)
	{
		if(global_func[active_func_ptr].param_list[i].name == name)
		{
			found = true;
			pn = &global_func[active_func_ptr].param_list[i];
			return;
		}
	}
}

void delete_var_list(int active_func_ptr, int level)
{
	for(int i = 0; i < global_func[active_func_ptr].var_list.size(); i++)
	{
		if(global_func[active_func_ptr].var_list[i].level == level)
		{
			global_func[active_func_ptr].var_list.erase(global_func[active_func_ptr].var_list.begin() + i);
		}
	}
}

void enter_param(string name, enum t type, int active_func_ptr, string struct_name, int pointer, vector<int> dimlist)
{
	variable temp;
	temp.name = name;
	temp.eletype = type;
	temp.struct_name = struct_name;
	temp.pointer = pointer;
	temp.dimlist = new vector<int>;
	*temp.dimlist = dimlist;
	global_func[active_func_ptr].param_list.push_back(temp);
}

enum t get_result_type(int fnptr)
{
	return global_func[fnptr].res_type;
}

void check_param_type(int call_func_ptr, int param_no, variable* var, bool &ok)
{
	if(global_func[active_func_ptr].param_list[param_no].eletype != var->eletype || global_func[active_func_ptr].param_list[param_no].type != var->type)
	{
		ok = false;
		return;
	}
	if(var->eletype != STRUC)
	{
		ok = true;
		return;
	}
	if(global_func[active_func_ptr].param_list[param_no].struct_name == var->struct_name)
	{
		ok = true;
	}
	else
	{
		ok = false;
	}
}

enum t get_variable_type(string name, int active_func_ptr, int level)
{
	int cur_level = -1;
	enum t type = ERRORTYPE;
	// sort(global_func[active_func_ptr].var_list.begin(), global_func[active_func_ptr].var_list.end(), compare);
	for(int i = global_func[active_func_ptr].var_list.size(); i >= 0; i--)
	{
		if(global_func[active_func_ptr].var_list[i].level > level)
		{
			continue;
		}
		if(global_func[active_func_ptr].var_list[i].name == name)
		{
			if(cur_level < global_func[active_func_ptr].var_list[i].level)
			{
				cur_level = global_func[active_func_ptr].var_list[i].level;
				type = global_func[active_func_ptr].var_list[i].eletype;
			}
		}
	}
	return type;
}
void search_struct(string name,bool &found, int &strptr)
{
	found = false;
	strptr = -1;
	for (int i=0;i<global_struct.size();i++)
	{
		if (global_struct[i].name==name)
		{
			found = true;
			strptr = i;
			return;
		}
	}
}
void enter_struct(string name ,int &strptr)
{
	struct_name_table temp;
	temp.name = name;
	temp.var_list.clear();
	global_struct.push_back(temp);
	strptr = global_struct.size()-1;
}
void search_struct_var(string name, int active_struct_ptr , bool &found, variable* &vn)
{
	found = false;
	vn = NULL;
	for(int i=0;i<global_struct[active_struct_ptr].var_list.size();i++)
	{
		if (global_struct[active_struct_ptr].var_list[i].name == name)
		{
			found = true;
			vn = &global_struct[active_struct_ptr].var_list[i];
			return;
		}
	}
}
void enter_struct_var(string name, int active_struct_ptr, variable * &vnptr, vector<int> dimlist, int pointer)
{
	variable temp;
	temp.name = name;
	temp.pointer = pointer;
	temp.dimlist = new vector<int>;
	*temp.dimlist = dimlist;
	global_struct[active_struct_ptr].var_list.push_back(temp);
	vnptr = &global_struct[active_struct_ptr].var_list[global_struct[active_struct_ptr].var_list.size()-1];
}

void backpatch(vector<int> list, int quad_number)
{
	for(int i=0;i<list.size();i++)
	{
		if(quad_table[list[i]].oprnd_1=="__")
			quad_table[list[i]].oprnd_1 = "L" + to_string(quad_number);
		if(quad_table[list[i]].oprnd_2=="__")
			quad_table[list[i]].oprnd_2 = "L" + to_string(quad_number);
		if(quad_table[list[i]].oprnd_3=="__")
			quad_table[list[i]].oprnd_3 = "L" + to_string(quad_number);
	}
}

void gen(quadruple quad)
{
	quad_table.push_back(quad);
	nextquad++;
}

void newtemp(variable *var)
{
	var->name = "t" + to_string(temp_var++);
	global_func[active_func_ptr].var_list.push_back(*var);
}

int get_size(enum t type)
{
	if(type==INT)
		return 4;
	else if(type==REAL)
		return 8;
	else if(type==CHA)
		return 1;
	return 1;
}
