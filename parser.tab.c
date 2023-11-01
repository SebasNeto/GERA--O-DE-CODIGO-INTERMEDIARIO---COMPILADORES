/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <stdio.h>
#include <stdlib.h>

#include "lex.yy.h"

ASTNode* ast_root = NULL;
#include "codegen.h"
#include "tabelaSimbolos.h"



extern int yylex();
extern char* yytext;
extern int yylineno;

int getLineNumber(void);
void yyerror(const char *s);


#line 93 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_KW_INT = 3,                     /* KW_INT  */
  YYSYMBOL_KW_REAL = 4,                    /* KW_REAL  */
  YYSYMBOL_VOID = 5,                       /* VOID  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_LOOP = 9,                       /* LOOP  */
  YYSYMBOL_INPUT = 10,                     /* INPUT  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_EQ = 12,                        /* EQ  */
  YYSYMBOL_LEQ = 13,                       /* LEQ  */
  YYSYMBOL_LT = 14,                        /* LT  */
  YYSYMBOL_GT = 15,                        /* GT  */
  YYSYMBOL_GEQ = 16,                       /* GEQ  */
  YYSYMBOL_NEQ = 17,                       /* NEQ  */
  YYSYMBOL_LIT_INT = 18,                   /* LIT_INT  */
  YYSYMBOL_LIT_REAL = 19,                  /* LIT_REAL  */
  YYSYMBOL_LIT_CHAR = 20,                  /* LIT_CHAR  */
  YYSYMBOL_ID = 21,                        /* ID  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* '='  */
  YYSYMBOL_24_ = 24,                       /* '('  */
  YYSYMBOL_25_ = 25,                       /* ')'  */
  YYSYMBOL_26_ = 26,                       /* ','  */
  YYSYMBOL_27_ = 27,                       /* '{'  */
  YYSYMBOL_28_ = 28,                       /* '}'  */
  YYSYMBOL_29_ = 29,                       /* '+'  */
  YYSYMBOL_30_ = 30,                       /* '-'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_33_ = 33,                       /* '%'  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_programa = 37,                  /* programa  */
  YYSYMBOL_lista_decl = 38,                /* lista_decl  */
  YYSYMBOL_decl = 39,                      /* decl  */
  YYSYMBOL_decl_var = 40,                  /* decl_var  */
  YYSYMBOL_espec_tipo = 41,                /* espec_tipo  */
  YYSYMBOL_decl_func = 42,                 /* decl_func  */
  YYSYMBOL_params = 43,                    /* params  */
  YYSYMBOL_lista_param = 44,               /* lista_param  */
  YYSYMBOL_param = 45,                     /* param  */
  YYSYMBOL_decl_locais = 46,               /* decl_locais  */
  YYSYMBOL_lista_com = 47,                 /* lista_com  */
  YYSYMBOL_comando = 48,                   /* comando  */
  YYSYMBOL_com_expr = 49,                  /* com_expr  */
  YYSYMBOL_com_atrib = 50,                 /* com_atrib  */
  YYSYMBOL_com_comp = 51,                  /* com_comp  */
  YYSYMBOL_com_selecao = 52,               /* com_selecao  */
  YYSYMBOL_com_repeticao = 53,             /* com_repeticao  */
  YYSYMBOL_com_retorno = 54,               /* com_retorno  */
  YYSYMBOL_exp = 55,                       /* exp  */
  YYSYMBOL_op_relac = 56,                  /* op_relac  */
  YYSYMBOL_exp_soma = 57,                  /* exp_soma  */
  YYSYMBOL_exp_mult = 58,                  /* exp_mult  */
  YYSYMBOL_exp_simples = 59,               /* exp_simples  */
  YYSYMBOL_literais = 60,                  /* literais  */
  YYSYMBOL_cham_func = 61,                 /* cham_func  */
  YYSYMBOL_var = 62,                       /* var  */
  YYSYMBOL_args = 63,                      /* args  */
  YYSYMBOL_lista_arg = 64                  /* lista_arg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    33,     2,     2,
      24,    25,    31,    29,    26,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    23,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    83,    83,    89,    92,    98,    99,   103,   107,   116,
     117,   118,   123,   131,   132,   133,   138,   139,   143,   147,
     148,   152,   155,   161,   162,   163,   164,   165,   166,   170,
     173,   180,   191,   197,   200,   206,   212,   215,   221,   224,
     228,   229,   230,   231,   232,   233,   237,   238,   239,   248,
     249,   250,   260,   261,   262,   263,   267,   268,   269,   273,
     277,   285,   292,   293,   297,   298
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "KW_INT", "KW_REAL",
  "VOID", "IF", "ELSE", "WHILE", "LOOP", "INPUT", "RETURN", "EQ", "LEQ",
  "LT", "GT", "GEQ", "NEQ", "LIT_INT", "LIT_REAL", "LIT_CHAR", "ID", "';'",
  "'='", "'('", "')'", "','", "'{'", "'}'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'['", "']'", "$accept", "programa", "lista_decl", "decl",
  "decl_var", "espec_tipo", "decl_func", "params", "lista_param", "param",
  "decl_locais", "lista_com", "comando", "com_expr", "com_atrib",
  "com_comp", "com_selecao", "com_repeticao", "com_retorno", "exp",
  "op_relac", "exp_soma", "exp_mult", "exp_simples", "literais",
  "cham_func", "var", "args", "lista_arg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-15)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      30,   -84,   -84,   -84,    14,    18,   -84,   -84,    -2,   -84,
     -84,     1,    23,    69,   -84,   -84,   -84,   -23,   -84,    76,
     -84,   -84,   -84,    40,   -84,   -84,   -84,   -84,   -84,   -84,
      28,    56,   -26,   -84,   -84,   -84,    29,    31,    76,    76,
     -84,    35,   -84,    76,    45,    49,    18,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,    76,    76,    76,    76,    76,
      76,   -84,    57,    99,    55,    59,   -84,   -84,    67,    72,
      46,   -84,   -84,    78,    77,   -26,   -26,   -20,   -84,   -84,
      84,    85,    83,    88,    86,    87,   -84,    40,    40,   -84,
      76,   -84,    -6,   -84,   -84,   -84,    80,   -84,    89,    30,
     -84,   103,   -84,   -84,   -84,   -84,    40,   -84
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,    11,     0,    22,     4,     5,     0,     6,
       1,     0,     0,     0,    56,    57,    58,    60,    30,     0,
      20,     3,     2,    22,    23,    24,    25,    26,    27,    28,
       0,    39,    48,    51,    55,    54,    53,     0,     0,     0,
      36,     0,    53,    63,     0,     0,    22,    21,    29,    44,
      40,    41,    42,    43,    45,     0,     0,     0,     0,     0,
       0,     7,     0,    15,     0,     0,    37,    65,     0,    62,
       0,    52,    19,     0,     0,    46,    47,    38,    49,    50,
       0,     0,    11,     0,     0,    13,    17,     0,     0,    59,
       0,    61,     0,    32,    31,     8,    60,    18,     0,     0,
      33,    25,    35,    64,    12,    16,     0,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   107,    71,   -43,   -84,   -84,   -84,    16,
     -84,   -16,   -75,   -84,   -84,   -83,   -84,   -84,   -84,   -11,
     -84,    61,   -12,     7,    58,   -84,    -5,   -84,   -84
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,     7,     8,     9,    84,    85,    86,
      46,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      57,    31,    32,    33,    34,    35,    42,    68,    69
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    43,    41,    73,   101,    58,    59,    47,    45,    55,
      56,    44,   100,   102,    10,   104,    61,    62,    36,    37,
      83,     1,     2,     3,    11,    38,    12,    64,    65,    13,
      74,   107,    67,     1,     2,     3,    14,    15,    16,    17,
      18,    36,    19,    75,    76,    20,    11,    39,    12,    80,
      48,    13,    60,    61,    62,    63,    83,    66,    14,    15,
      16,    17,    18,    70,    19,    78,    79,    20,    49,    50,
      51,    52,    53,    54,    71,    14,    15,    16,    97,   103,
      87,    91,    36,    36,    88,    55,    56,    14,    15,    16,
      17,    40,    89,    19,    14,    15,    16,    17,    90,    92,
      19,    36,     1,     2,    82,    93,    94,    95,   -14,    96,
     106,    98,    21,    99,    44,   105,    20,    72,    77,     0,
      81
};

static const yytype_int8 yycheck[] =
{
       5,    24,    13,    46,    87,    31,    32,    23,    19,    29,
      30,    34,    87,    88,     0,    98,    22,    23,    23,    21,
      63,     3,     4,     5,     6,    24,     8,    38,    39,    11,
      46,   106,    43,     3,     4,     5,    18,    19,    20,    21,
      22,    46,    24,    55,    56,    27,     6,    24,     8,    60,
      22,    11,    23,    22,    23,    24,    99,    22,    18,    19,
      20,    21,    22,    18,    24,    58,    59,    27,    12,    13,
      14,    15,    16,    17,    25,    18,    19,    20,    83,    90,
      25,    35,    87,    88,    25,    29,    30,    18,    19,    20,
      21,    22,    25,    24,    18,    19,    20,    21,    26,    21,
      24,   106,     3,     4,     5,    28,    22,    22,    25,    21,
       7,    25,     5,    26,    34,    99,    27,    46,    57,    -1,
      62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,    37,    38,    39,    40,    41,    42,
       0,     6,     8,    11,    18,    19,    20,    21,    22,    24,
      27,    39,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    57,    58,    59,    60,    61,    62,    21,    24,    24,
      22,    55,    62,    24,    34,    55,    46,    47,    22,    12,
      13,    14,    15,    16,    17,    29,    30,    56,    31,    32,
      23,    22,    23,    24,    55,    55,    22,    55,    63,    64,
      18,    25,    40,    41,    47,    58,    58,    57,    59,    59,
      55,    60,     5,    41,    43,    44,    45,    25,    25,    25,
      26,    35,    21,    28,    22,    22,    21,    62,    25,    26,
      48,    51,    48,    55,    51,    45,     7,    48
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      41,    41,    42,    43,    43,    43,    44,    44,    45,    46,
      46,    47,    47,    48,    48,    48,    48,    48,    48,    49,
      49,    50,    51,    52,    52,    53,    54,    54,    55,    55,
      56,    56,    56,    56,    56,    56,    57,    57,    57,    58,
      58,    58,    59,    59,    59,    59,    60,    60,    60,    61,
      62,    62,    63,    63,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     1,     1,     1,     3,     5,     1,
       1,     1,     6,     1,     1,     0,     3,     1,     2,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     1,     2,
       1,     4,     4,     5,     7,     5,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     3,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     4,
       1,     4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* programa: lista_decl lista_com  */
#line 83 "parser.y"
                        {
        ast_root = ast_create_node(AST_PROGRAM, (yyvsp[-1].astNode), (yyvsp[0].astNode), NULL);
    }
#line 1218 "parser.tab.c"
    break;

  case 3: /* lista_decl: lista_decl decl  */
#line 89 "parser.y"
                    {
        (yyval.astNode) = ast_create_node(AST_LIST_DECL, (yyvsp[-1].astNode), (yyvsp[0].astNode), NULL);
    }
#line 1226 "parser.tab.c"
    break;

  case 4: /* lista_decl: decl  */
#line 92 "parser.y"
           {
        (yyval.astNode) = ast_create_node(AST_DECL, (yyvsp[0].astNode), NULL, NULL);
    }
#line 1234 "parser.tab.c"
    break;

  case 5: /* decl: decl_var  */
#line 98 "parser.y"
             { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1240 "parser.tab.c"
    break;

  case 6: /* decl: decl_func  */
#line 99 "parser.y"
                { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1246 "parser.tab.c"
    break;

  case 7: /* decl_var: espec_tipo ID ';'  */
#line 103 "parser.y"
                      {
        Symbol* entry = inserirSimbolo((yyvsp[-2].astNode)->tipo, (yyvsp[-1].symbolEntry)->strValue);
        (yyval.astNode) = ast_create_node(AST_DECL_VAR, NULL, NULL, entry);
    }
#line 1255 "parser.tab.c"
    break;

  case 8: /* decl_var: espec_tipo ID '=' literais ';'  */
#line 107 "parser.y"
                                     {
        Symbol* entry = inserirSimbolo((yyvsp[-4].astNode)->tipo, (yyvsp[-3].symbolEntry)->strValue);
        (yyval.astNode) = ast_create_node(AST_DECL_VAR, NULL, NULL, entry);
    }
#line 1264 "parser.tab.c"
    break;

  case 9: /* espec_tipo: KW_INT  */
#line 116 "parser.y"
           { (yyval.astNode) = ast_create_node(AST_TYPE_INT, NULL, NULL, NULL); }
#line 1270 "parser.tab.c"
    break;

  case 10: /* espec_tipo: KW_REAL  */
#line 117 "parser.y"
              { (yyval.astNode) = ast_create_node(AST_TYPE_REAL, NULL, NULL, NULL); }
#line 1276 "parser.tab.c"
    break;

  case 11: /* espec_tipo: VOID  */
#line 118 "parser.y"
           { (yyval.astNode) = ast_create_node(AST_TYPE_VOID, NULL, NULL, NULL); }
#line 1282 "parser.tab.c"
    break;

  case 12: /* decl_func: espec_tipo ID '(' params ')' com_comp  */
#line 123 "parser.y"
                                          {
        Symbol* entry = inserirSimbolo((yyvsp[-5].astNode)->tipo, (yyvsp[-4].symbolEntry)->strValue);
        (yyval.astNode) = ast_create_node(AST_FUNC_DECL, NULL, NULL, entry);
    }
#line 1291 "parser.tab.c"
    break;

  case 13: /* params: lista_param  */
#line 131 "parser.y"
                { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1297 "parser.tab.c"
    break;

  case 14: /* params: VOID  */
#line 132 "parser.y"
           { (yyval.astNode) = ast_create_node(AST_TYPE_VOID, NULL, NULL, NULL); }
#line 1303 "parser.tab.c"
    break;

  case 15: /* params: %empty  */
#line 133 "parser.y"
                  { (yyval.astNode) = NULL; }
#line 1309 "parser.tab.c"
    break;

  case 20: /* decl_locais: %empty  */
#line 148 "parser.y"
                  { (yyval.astNode) = NULL; }
#line 1315 "parser.tab.c"
    break;

  case 21: /* lista_com: comando lista_com  */
#line 152 "parser.y"
                      {
        (yyval.astNode) = ast_create_node(AST_LIST_COM, (yyvsp[-1].astNode), (yyvsp[0].astNode), NULL);
    }
#line 1323 "parser.tab.c"
    break;

  case 22: /* lista_com: %empty  */
#line 155 "parser.y"
                  {
        (yyval.astNode) = NULL;
    }
#line 1331 "parser.tab.c"
    break;

  case 23: /* comando: com_expr  */
#line 161 "parser.y"
             { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1337 "parser.tab.c"
    break;

  case 24: /* comando: com_atrib  */
#line 162 "parser.y"
                { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1343 "parser.tab.c"
    break;

  case 25: /* comando: com_comp  */
#line 163 "parser.y"
               { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1349 "parser.tab.c"
    break;

  case 26: /* comando: com_selecao  */
#line 164 "parser.y"
                  { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1355 "parser.tab.c"
    break;

  case 27: /* comando: com_repeticao  */
#line 165 "parser.y"
                    { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1361 "parser.tab.c"
    break;

  case 28: /* comando: com_retorno  */
#line 166 "parser.y"
                  { (yyval.astNode) = (yyvsp[0].astNode); }
#line 1367 "parser.tab.c"
    break;

  case 29: /* com_expr: exp ';'  */
#line 170 "parser.y"
            {
        (yyval.astNode) = ast_create_node(AST_EXPR, (yyvsp[-1].astNode), NULL, NULL); // Ajuste conforme necessário
    }
#line 1375 "parser.tab.c"
    break;

  case 30: /* com_expr: ';'  */
#line 173 "parser.y"
          {
        (yyval.astNode) = ast_create_node(AST_EMPTY, NULL, NULL, NULL); // Representa um comando vazio
    }
#line 1383 "parser.tab.c"
    break;

  case 31: /* com_atrib: var '=' exp ';'  */
#line 180 "parser.y"
                    {
        Symbol* varEntry = retornaSimbolo((yyvsp[-3].astNode)->identifier);
        if (!varEntry) {
            yyerror("Variável não declarada");
        }else{
            (yyval.astNode) = ast_create_node(AST_ASSIGN, (yyvsp[-3].astNode), (yyvsp[-1].astNode), NULL);
        }
    }
#line 1396 "parser.tab.c"
    break;

  case 32: /* com_comp: '{' decl_locais lista_com '}'  */
#line 191 "parser.y"
                                  {
        (yyval.astNode) = ast_create_node(AST_COMPOUND, (yyvsp[-2].astNode), (yyvsp[-1].astNode), NULL); // Ajuste conforme necessário
    }
#line 1404 "parser.tab.c"
    break;

  case 33: /* com_selecao: IF '(' exp ')' comando  */
#line 197 "parser.y"
                           {
        (yyval.astNode) = ast_create_node(AST_IF, (yyvsp[-2].astNode), (yyvsp[0].astNode), NULL); // Sem parte "else"
    }
#line 1412 "parser.tab.c"
    break;

  case 34: /* com_selecao: IF '(' exp ')' com_comp ELSE comando  */
#line 200 "parser.y"
                                           {
        (yyval.astNode) = ast_create_node(AST_IF_ELSE, (yyvsp[-4].astNode), (yyvsp[-2].astNode), (yyvsp[0].astNode)); // Com parte "else"
    }
#line 1420 "parser.tab.c"
    break;

  case 35: /* com_repeticao: WHILE '(' exp ')' comando  */
#line 206 "parser.y"
                              {
        (yyval.astNode) = ast_create_node(AST_WHILE, (yyvsp[-2].astNode), (yyvsp[0].astNode), NULL); 
    }
#line 1428 "parser.tab.c"
    break;

  case 36: /* com_retorno: RETURN ';'  */
#line 212 "parser.y"
               {
        (yyval.astNode) = ast_create_node(AST_RETURN, NULL, NULL, NULL); 
    }
#line 1436 "parser.tab.c"
    break;

  case 37: /* com_retorno: RETURN exp ';'  */
#line 215 "parser.y"
                     {
        (yyval.astNode) = ast_create_node(AST_RETURN, (yyvsp[-1].astNode), NULL, NULL); 
    }
#line 1444 "parser.tab.c"
    break;

  case 38: /* exp: exp_soma op_relac exp_soma  */
#line 221 "parser.y"
                               {
        (yyval.astNode) = ast_create_node((yyvsp[-1].symbolEntry)->type, (yyvsp[-2].symbolEntry), (yyvsp[0].symbolEntry), NULL);
    }
#line 1452 "parser.tab.c"
    break;

  case 39: /* exp: exp_soma  */
#line 224 "parser.y"
               { (yyval.astNode) = (yyvsp[0].symbolEntry); }
#line 1458 "parser.tab.c"
    break;

  case 40: /* op_relac: LEQ  */
#line 228 "parser.y"
        { (yyval.symbolEntry) = ast_create_node(AST_LEQ, NULL, NULL, NULL); }
#line 1464 "parser.tab.c"
    break;

  case 41: /* op_relac: LT  */
#line 229 "parser.y"
         { (yyval.symbolEntry) = ast_create_node(AST_LT, NULL, NULL, NULL); }
#line 1470 "parser.tab.c"
    break;

  case 42: /* op_relac: GT  */
#line 230 "parser.y"
         { (yyval.symbolEntry) = ast_create_node(AST_GT, NULL, NULL, NULL); }
#line 1476 "parser.tab.c"
    break;

  case 43: /* op_relac: GEQ  */
#line 231 "parser.y"
          { (yyval.symbolEntry) = ast_create_node(AST_GEQ, NULL, NULL, NULL); }
#line 1482 "parser.tab.c"
    break;

  case 44: /* op_relac: EQ  */
#line 232 "parser.y"
         { (yyval.symbolEntry) = ast_create_node(AST_EQ, NULL, NULL, NULL); }
#line 1488 "parser.tab.c"
    break;

  case 45: /* op_relac: NEQ  */
#line 233 "parser.y"
          { (yyval.symbolEntry) = ast_create_node(AST_NEQ, NULL, NULL, NULL); }
#line 1494 "parser.tab.c"
    break;

  case 46: /* exp_soma: exp_soma '+' exp_mult  */
#line 237 "parser.y"
                          { (yyval.symbolEntry) = ast_create_node(AST_ADD, (yyvsp[-2].symbolEntry), (yyvsp[0].symbolEntry), NULL); }
#line 1500 "parser.tab.c"
    break;

  case 47: /* exp_soma: exp_soma '-' exp_mult  */
#line 238 "parser.y"
                            { (yyval.symbolEntry) = ast_create_node(AST_SUB, (yyvsp[-2].symbolEntry), (yyvsp[0].symbolEntry), NULL); }
#line 1506 "parser.tab.c"
    break;

  case 48: /* exp_soma: exp_mult  */
#line 239 "parser.y"
               { (yyval.symbolEntry) = (yyvsp[0].symbolEntry); }
#line 1512 "parser.tab.c"
    break;

  case 49: /* exp_mult: exp_mult '*' exp_simples  */
#line 248 "parser.y"
                             { (yyval.symbolEntry) = ast_create_node(AST_MUL, (yyvsp[-2].symbolEntry), (yyvsp[0].symbolEntry), NULL); }
#line 1518 "parser.tab.c"
    break;

  case 50: /* exp_mult: exp_mult '/' exp_simples  */
#line 249 "parser.y"
                               { (yyval.symbolEntry) = ast_create_node(AST_DIV, (yyvsp[-2].symbolEntry), (yyvsp[0].symbolEntry), NULL); }
#line 1524 "parser.tab.c"
    break;

  case 51: /* exp_mult: exp_simples  */
#line 250 "parser.y"
                  { (yyval.symbolEntry) = (yyvsp[0].symbolEntry); }
#line 1530 "parser.tab.c"
    break;

  case 52: /* exp_simples: '(' exp ')'  */
#line 260 "parser.y"
                { (yyval.symbolEntry) = (yyvsp[-1].astNode); }
#line 1536 "parser.tab.c"
    break;

  case 53: /* exp_simples: var  */
#line 261 "parser.y"
          { (yyval.symbolEntry) = (yyvsp[0].astNode); }
#line 1542 "parser.tab.c"
    break;

  case 54: /* exp_simples: cham_func  */
#line 262 "parser.y"
                { (yyval.symbolEntry) = (yyvsp[0].symbolEntry); }
#line 1548 "parser.tab.c"
    break;

  case 55: /* exp_simples: literais  */
#line 263 "parser.y"
               { (yyval.symbolEntry) = (yyvsp[0].symbolEntry); }
#line 1554 "parser.tab.c"
    break;

  case 56: /* literais: LIT_INT  */
#line 267 "parser.y"
            { (yyval.symbolEntry) = ast_create_node(AST_LIT_INT, NULL, NULL, inserirSimbolo(SYMBOL_SCALAR, yytext)); }
#line 1560 "parser.tab.c"
    break;

  case 57: /* literais: LIT_REAL  */
#line 268 "parser.y"
               { (yyval.symbolEntry) = ast_create_node(AST_LIT_REAL, NULL, NULL, inserirSimbolo(SYMBOL_SCALAR, yytext)); }
#line 1566 "parser.tab.c"
    break;

  case 58: /* literais: LIT_CHAR  */
#line 269 "parser.y"
               { (yyval.symbolEntry) = ast_create_node(AST_LIT_CHAR, NULL, NULL, inserirSimbolo(SYMBOL_SCALAR, yytext)); }
#line 1572 "parser.tab.c"
    break;

  case 60: /* var: ID  */
#line 277 "parser.y"
       {
        Symbol* sym = retornaSimbolo((yyvsp[0].symbolEntry)->identifier);
        if (!sym) {
            yyerror("Variável não declarada");
        } else {
            (yyval.astNode) = ast_create_node(AST_ID, NULL, NULL, sym);
        }
    }
#line 1585 "parser.tab.c"
    break;

  case 61: /* var: ID '[' LIT_INT ']'  */
#line 285 "parser.y"
                         {
        // Tratamento de arrays, se necessário
    }
#line 1593 "parser.tab.c"
    break;


#line 1597 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 301 "parser.y"


int getLineNumber(void) {
    return yylineno;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático na linha %d, próximo ao token '%s': %s\n", yylineno, yytext, s);
}
