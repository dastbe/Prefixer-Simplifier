%{

	// Lexical parser for our expression language
	//
	// Created by: David Bell
	// April 26th, 2012

	#include "stdio.h"
	#include "stdlib.h"
	#include "expr_tree.h"

	#define YYSTYPE ExprTree*

	#include "expr_bison.tab.hpp"
	void yyerror(const char *);
%}

%option noyywrap

id			[a-zA-Z]
number		([0]|[1-9][0-9]*)
newline     [ \t\n\r]

%%

{number}	{ yylval = new Int(atoi(yytext)); return NUMBER; }	/* Constant values */
{id}		{ yylval = new Ident(yytext[0]); return ID; }			/* Identifiers */

"+"			{ return PLUS; }
"-"			{ return MINUS; }
"*"			{ return TIMES; }
"/"			{ return DIVIDE; }

"("			{ return OPENPAREN; }
")"			{ return CLOSEPAREN; }

{newline} 	;				 																		/* skip whitespace */

.			yyerror((char *) "invalid");

%%
