/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SELECT = 258,
     WORDS = 259,
     FROM = 260,
     INNER = 261,
     JOIN = 262,
     OUTER = 263,
     RIGHT = 264,
     LEFT = 265,
     WHERE = 266,
     AS = 267,
     ON = 268,
     AND = 269,
     OR = 270,
     GROUP = 271,
     BY = 272,
     HAVING = 273,
     ORDER = 274,
     DESC = 275,
     ASC = 276,
     SUM = 277,
     COUNT = 278,
     AVG = 279,
     T_MAX = 280,
     T_MIN = 281,
     STDDEV = 282,
     VARIANCE = 283
   };
#endif
/* Tokens.  */
#define SELECT 258
#define WORDS 259
#define FROM 260
#define INNER 261
#define JOIN 262
#define OUTER 263
#define RIGHT 264
#define LEFT 265
#define WHERE 266
#define AS 267
#define ON 268
#define AND 269
#define OR 270
#define GROUP 271
#define BY 272
#define HAVING 273
#define ORDER 274
#define DESC 275
#define ASC 276
#define SUM 277
#define COUNT 278
#define AVG 279
#define T_MAX 280
#define T_MIN 281
#define STDDEV 282
#define VARIANCE 283




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 16 "qry_parser.y"
typedef union YYSTYPE {
	BimaQuery *tquery;
	BimaQueryTable *ttable;
	BimaQueryField *tfield;
	GList *tlist;
	char *tkeyword;
	int	tint;
} YYSTYPE;
/* Line 1447 of yacc.c.  */
#line 103 "qry_parser.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE qrylval;



