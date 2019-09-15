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
    OR = 258,
    AND = 259,
    NOT = 260,
    ADD = 261,
    ALL = 262,
    ALTER = 263,
    BETWEEN = 264,
    BY = 265,
    CHAR = 266,
    COLUMN = 267,
    CREATE = 268,
    DECIMAL = 269,
    DELETE = 270,
    DISTINCT = 271,
    DOUBLE = 272,
    DROP = 273,
    FOREIGN = 274,
    FROM = 275,
    IN = 276,
    INSERT = 277,
    INT = 278,
    INTO = 279,
    KEY = 280,
    NUL = 281,
    PRIMARY = 282,
    REFERENCES = 283,
    SELECT = 284,
    SET = 285,
    TABLE = 286,
    UNIQUE = 287,
    UPDATE = 288,
    VALUES = 289,
    VARCHAR = 290,
    WHERE = 291,
    PLUS = 292,
    MINUS = 293,
    STAR = 294,
    SLASH = 295,
    OPERATOR = 296,
    EQUAL = 297,
    IDENTIFIER = 298,
    NUMBER = 299,
    STRING = 300,
    COMMA = 301,
    LEFT_BRACKET = 302,
    RIGHT_BRACKET = 303,
    SEMICOLON = 304,
    ERROR = 305
  };
#endif
/* Tokens.  */
#define OR 258
#define AND 259
#define NOT 260
#define ADD 261
#define ALL 262
#define ALTER 263
#define BETWEEN 264
#define BY 265
#define CHAR 266
#define COLUMN 267
#define CREATE 268
#define DECIMAL 269
#define DELETE 270
#define DISTINCT 271
#define DOUBLE 272
#define DROP 273
#define FOREIGN 274
#define FROM 275
#define IN 276
#define INSERT 277
#define INT 278
#define INTO 279
#define KEY 280
#define NUL 281
#define PRIMARY 282
#define REFERENCES 283
#define SELECT 284
#define SET 285
#define TABLE 286
#define UNIQUE 287
#define UPDATE 288
#define VALUES 289
#define VARCHAR 290
#define WHERE 291
#define PLUS 292
#define MINUS 293
#define STAR 294
#define SLASH 295
#define OPERATOR 296
#define EQUAL 297
#define IDENTIFIER 298
#define NUMBER 299
#define STRING 300
#define COMMA 301
#define LEFT_BRACKET 302
#define RIGHT_BRACKET 303
#define SEMICOLON 304
#define ERROR 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */