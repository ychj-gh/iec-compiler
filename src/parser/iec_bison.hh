/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_ROOT_WORKSPACE_SOFTPLC_SPACE_IEC_COMPILER_SRC_PARSER_IEC_BISON_HH_INCLUDED
# define YY_YY_ROOT_WORKSPACE_SOFTPLC_SPACE_IEC_COMPILER_SRC_PARSER_IEC_BISON_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 177 "iec_bison.yy" /* yacc.c:1909  */

/* define a new data type to store the locations, so we can also store
 * the filename in which the token is expressed.
 */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE {
    int         first_line;
    int         first_column;
    const char *first_file;
    long int    first_order;
    int         last_line;
    int         last_column;
    const char *last_file;
    long int    last_order;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 0
#endif


#line 65 "/root/workspace/SoftPLC_space/iec-compiler/src/parser/iec_bison.hh" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END_OF_INPUT = 0,
    BOGUS_TOKEN_ID = 258,
    prev_declared_variable_name_token = 259,
    prev_declared_direct_variable_token = 260,
    prev_declared_fb_name_token = 261,
    prev_declared_simple_type_name_token = 262,
    prev_declared_subrange_type_name_token = 263,
    prev_declared_enumerated_type_name_token = 264,
    prev_declared_array_type_name_token = 265,
    prev_declared_structure_type_name_token = 266,
    prev_declared_string_type_name_token = 267,
    prev_declared_ref_type_name_token = 268,
    prev_declared_derived_function_name_token = 269,
    prev_declared_derived_function_block_name_token = 270,
    prev_declared_program_type_name_token = 271,
    disable_code_generation_pragma_token = 272,
    enable_code_generation_pragma_token = 273,
    pragma_token = 274,
    EN = 275,
    ENO = 276,
    REF = 277,
    DREF = 278,
    REF_TO = 279,
    NULL_token = 280,
    identifier_token = 281,
    integer_token = 282,
    binary_integer_token = 283,
    octal_integer_token = 284,
    hex_integer_token = 285,
    real_token = 286,
    safeboolean_true_literal_token = 287,
    safeboolean_false_literal_token = 288,
    boolean_true_literal_token = 289,
    boolean_false_literal_token = 290,
    FALSE = 291,
    TRUE = 292,
    single_byte_character_string_token = 293,
    double_byte_character_string_token = 294,
    fixed_point_token = 295,
    fixed_point_d_token = 296,
    integer_d_token = 297,
    fixed_point_h_token = 298,
    integer_h_token = 299,
    fixed_point_m_token = 300,
    integer_m_token = 301,
    fixed_point_s_token = 302,
    integer_s_token = 303,
    fixed_point_ms_token = 304,
    integer_ms_token = 305,
    end_interval_token = 306,
    erroneous_interval_token = 307,
    T_SHARP = 308,
    D_SHARP = 309,
    BYTE = 310,
    WORD = 311,
    DWORD = 312,
    LWORD = 313,
    LREAL = 314,
    REAL = 315,
    SINT = 316,
    INT = 317,
    DINT = 318,
    LINT = 319,
    USINT = 320,
    UINT = 321,
    UDINT = 322,
    ULINT = 323,
    WSTRING = 324,
    STRING = 325,
    BOOL = 326,
    TIME = 327,
    DATE = 328,
    DATE_AND_TIME = 329,
    DT = 330,
    TIME_OF_DAY = 331,
    TOD = 332,
    SAFEBYTE = 333,
    SAFEWORD = 334,
    SAFEDWORD = 335,
    SAFELWORD = 336,
    SAFELREAL = 337,
    SAFEREAL = 338,
    SAFESINT = 339,
    SAFEINT = 340,
    SAFEDINT = 341,
    SAFELINT = 342,
    SAFEUSINT = 343,
    SAFEUINT = 344,
    SAFEUDINT = 345,
    SAFEULINT = 346,
    SAFEWSTRING = 347,
    SAFESTRING = 348,
    SAFEBOOL = 349,
    SAFETIME = 350,
    SAFEDATE = 351,
    SAFEDATE_AND_TIME = 352,
    SAFEDT = 353,
    SAFETIME_OF_DAY = 354,
    SAFETOD = 355,
    ANY = 356,
    ANY_DERIVED = 357,
    ANY_ELEMENTARY = 358,
    ANY_MAGNITUDE = 359,
    ANY_NUM = 360,
    ANY_REAL = 361,
    ANY_INT = 362,
    ANY_BIT = 363,
    ANY_STRING = 364,
    ANY_DATE = 365,
    ASSIGN = 366,
    DOTDOT = 367,
    TYPE = 368,
    END_TYPE = 369,
    ARRAY = 370,
    OF = 371,
    STRUCT = 372,
    END_STRUCT = 373,
    direct_variable_token = 374,
    incompl_location_token = 375,
    VAR_INPUT = 376,
    VAR_OUTPUT = 377,
    VAR_IN_OUT = 378,
    VAR_EXTERNAL = 379,
    VAR_GLOBAL = 380,
    END_VAR = 381,
    RETAIN = 382,
    NON_RETAIN = 383,
    R_EDGE = 384,
    F_EDGE = 385,
    AT = 386,
    standard_function_name_token = 387,
    FUNCTION = 388,
    END_FUNCTION = 389,
    CONSTANT = 390,
    standard_function_block_name_token = 391,
    FUNCTION_BLOCK = 392,
    END_FUNCTION_BLOCK = 393,
    VAR_TEMP = 394,
    VAR = 395,
    PROGRAM = 396,
    END_PROGRAM = 397,
    ACTION = 398,
    END_ACTION = 399,
    TRANSITION = 400,
    END_TRANSITION = 401,
    FROM = 402,
    TO = 403,
    PRIORITY = 404,
    INITIAL_STEP = 405,
    STEP = 406,
    END_STEP = 407,
    L = 408,
    D = 409,
    SD = 410,
    DS = 411,
    SL = 412,
    N = 413,
    P = 414,
    P0 = 415,
    P1 = 416,
    prev_declared_global_var_name_token = 417,
    prev_declared_program_name_token = 418,
    prev_declared_resource_name_token = 419,
    prev_declared_configuration_name_token = 420,
    CONFIGURATION = 421,
    END_CONFIGURATION = 422,
    TASK = 423,
    RESOURCE = 424,
    ON = 425,
    END_RESOURCE = 426,
    VAR_CONFIG = 427,
    VAR_ACCESS = 428,
    WITH = 429,
    SINGLE = 430,
    INTERVAL = 431,
    READ_WRITE = 432,
    READ_ONLY = 433,
    EOL = 434,
    sendto_identifier_token = 435,
    LD = 436,
    LDN = 437,
    ST = 438,
    STN = 439,
    NOT = 440,
    S = 441,
    R = 442,
    S1 = 443,
    R1 = 444,
    CLK = 445,
    CU = 446,
    CD = 447,
    PV = 448,
    IN = 449,
    PT = 450,
    AND = 451,
    AND2 = 452,
    OR = 453,
    XOR = 454,
    ANDN = 455,
    ANDN2 = 456,
    ORN = 457,
    XORN = 458,
    ADD = 459,
    SUB = 460,
    MUL = 461,
    DIV = 462,
    MOD = 463,
    GT = 464,
    GE = 465,
    EQ = 466,
    LT = 467,
    LE = 468,
    NE = 469,
    CAL = 470,
    CALC = 471,
    CALCN = 472,
    RET = 473,
    RETC = 474,
    RETCN = 475,
    JMP = 476,
    JMPC = 477,
    JMPCN = 478,
    SENDTO = 479,
    OPER_NE = 480,
    OPER_GE = 481,
    OPER_LE = 482,
    OPER_EXP = 483,
    RETURN = 484,
    IF = 485,
    THEN = 486,
    ELSIF = 487,
    ELSE = 488,
    END_IF = 489,
    CASE = 490,
    END_CASE = 491,
    FOR = 492,
    BY = 493,
    DO = 494,
    END_FOR = 495,
    WHILE = 496,
    END_WHILE = 497,
    REPEAT = 498,
    UNTIL = 499,
    END_REPEAT = 500,
    EXIT = 501
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 200 "iec_bison.yy" /* yacc.c:1909  */

    symbol_c 	*leaf;
    list_c	*list;
    char 	*ID;	/* token value */

#line 331 "/root/workspace/SoftPLC_space/iec-compiler/src/parser/iec_bison.hh" /* yacc.c:1909  */
};
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

#endif /* !YY_YY_ROOT_WORKSPACE_SOFTPLC_SPACE_IEC_COMPILER_SRC_PARSER_IEC_BISON_HH_INCLUDED  */
