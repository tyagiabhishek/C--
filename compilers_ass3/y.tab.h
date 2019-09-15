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
#include "definition.h"
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    CHARACTER = 269,
    NUMBER_INT = 270,
    NUMBER_FLOAT = 271,
    TYPEDEF = 272,
    INTEGER = 273,
    FLOAT = 274,
    CHAR = 275,
    VOID = 276,
    STRUCT = 277,
    DOT = 278,
    SEMICOLON = 279,
    OR = 280,
    AND = 281,
    EQUALS = 282,
    LESS_THAN = 283,
    GREATER_THAN = 284,
    IF = 285,
    NOT = 286,
    WHILE = 287,
    QUOT = 288,
    RETURN = 289,
    COMMA = 290,
    ELSE = 291
  };
#endif
/* Tokens.  */
#define PLUS 258
#define MINUS 259
#define STAR 260
#define SLASH 261
#define LEFT_CURLY_BRACKET 262
#define RIGHT_CURLY_BRACKET 263
#define LEFT_CLOSED_BRACKET 264
#define RIGHT_CLOSED_BRACKET 265
#define LEFT_OPEN_BRACKET 266
#define RIGHT_OPEN_BRACKET 267
#define IDENTIFIER 268
#define CHARACTER 269
#define NUMBER_INT 270
#define NUMBER_FLOAT 271
#define TYPEDEF 272
#define INTEGER 273
#define FLOAT 274
#define CHAR 275
#define VOID 276
#define STRUCT 277
#define DOT 278
#define SEMICOLON 279
#define OR 280
#define AND 281
#define EQUALS 282
#define LESS_THAN 283
#define GREATER_THAN 284
#define IF 285
#define NOT 286
#define WHILE 287
#define QUOT 288
#define RETURN 289
#define COMMA 290
#define ELSE 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 48 "ass3-1.y" /* yacc.c:1909  */

	res* reslt;
	string* val;
	variable * var;
	vector<int> *list;
	int int_val;
	float float_val;
	smt_l* smt;
	while_struct *wstruct;
	lhs* lhs_var;

#line 138 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
