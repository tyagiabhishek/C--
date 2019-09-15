%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include "y.tab.h"
	#define YYSTYPE char *
	string tostring(char*);
	extern int line_no;
%}
%%
"int"						return INTEGER;
"float"						return FLOAT;
"struct"					return STRUCT;
"void"						return VOID;
"char"						return CHAR;
"typedef"					return TYPEDEF;
"if"						return IF;
"else"						return ELSE;
"while"						return WHILE;
"return"					return RETURN;
"="							return EQUALS;
"+"							return PLUS;
"-"							return MINUS;
"*"							return STAR;
"/"							return SLASH;
"("							return LEFT_OPEN_BRACKET;
")"							return RIGHT_OPEN_BRACKET;
"{"							return LEFT_CURLY_BRACKET;
"}"							return RIGHT_CURLY_BRACKET;
"["							return LEFT_CLOSED_BRACKET;
"]"							return RIGHT_CLOSED_BRACKET;					
","							return COMMA;
";"							return SEMICOLON;
"<"							return LESS_THAN;
">"							return GREATER_THAN;
"!"							return NOT;
"'"							return QUOT;
"|"							return OR;
"&"							return AND;
"~"							return NOT;
'[^']'						{yylval.val = new string;*(yylval.val) = tostring(yytext);return CHARACTER;}
[0-9]+("."[0-9]+)			{yylval.float_val = atof(yytext);return NUMBER_FLOAT;}
[0-9]+						{yylval.int_val = atoi(yytext);return NUMBER_INT;}
"."							return DOT;
[A-Za-z_][A-Za-z0-9_]*		{yylval.val = new string;*(yylval.val) = tostring(yytext);return IDENTIFIER;}

"\n"						{line_no++;}
[\t\r ]+		/*white space */		

.				/* Any invalid entry */	{ printf("Error found near <%s>.\n",yytext);
												exit(EXIT_SUCCESS); }

%%

string tostring(char *str)
{
	string abc;
	int i = 0;
	while(str[i] != 0)
	{
		abc.push_back(str[i]);
		i++;
	}
	return abc;
}

int yywrap(void)
{
	return 1;
}