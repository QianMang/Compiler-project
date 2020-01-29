/* A Bison parser, made by GNU Bison 3.3.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_FB_TAB_H_INCLUDED
# define YY_YY_FB_TAB_H_INCLUDED
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
    _INT = 258,
    _ID = 259,
    OP_PLUS = 260,
    OP_MINUS = 261,
    OP_MULT = 262,
    OP_DIV = 263,
    DOT = 264,
    DOTDOT = 265,
    COMMA = 266,
    SEMI = 267,
    ASSIGN = 268,
    OP_EXCHANGE = 269,
    OP_LESS = 270,
    OP_GREATER = 271,
    OP_LESSEQUAL = 272,
    OP_GREATEREQUAL = 273,
    OP_EQUAL = 274,
    OP_NOTEQUAL = 275,
    KW_ARRAY = 276,
    KW_TUPLE = 277,
    KW_GLOBAL = 278,
    KW_LOCAL = 279,
    KW_DEFUN = 280,
    KW_END = 281,
    KW_WHILE = 282,
    KW_DO = 283,
    KW_IF = 284,
    KW_THEN = 285,
    KW_ELSIF = 286,
    KW_ELSE = 287,
    KW_FOREACH = 288,
    KW_IN = 289,
    KW_FOR = 290,
    LPAR = 291,
    RPAR = 292,
    LBRAK = 293,
    RBRAK = 294,
    PRINT = 295,
    RETURN = 296,
    _EOF = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "fb.y" /* yacc.c:1927  */
struct ast* node;

#line 104 "fb.tab.h" /* yacc.c:1927  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FB_TAB_H_INCLUDED  */
