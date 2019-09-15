%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ass2.tab.h"
%}

%%

(?i:add)												return ADD;
(?i:all)												return ALL;
(?i:alter)												return ALTER;
(?i:and)												return AND;
(?i:between)											return BETWEEN;
(?i:by)													return BY;
(?i:(CHAR(ACTER)?))										return CHAR;
(?i:column)												return COLUMN;
(?i:create)												return CREATE;
(?i:decimal)											return DECIMAL;
(?i:delete)												return DELETE;
(?i:distinct)											return DISTINCT;
(?i:double)												return DOUBLE;
(?i:drop)												return DROP;
(?i:foreign)											return FOREIGN;
(?i:from)												return FROM;
(?i:in)													return IN;
(?i:insert)												return INSERT;
(?i:(int(eger)?))										return INT;
(?i:into)												return INTO;
(?i:key)												return KEY;
(?i:not)												return NOT;
(?i:null)												return NUL;
(?i:or)													return OR;
(?i:primary)											return PRIMARY;
(?i:references)											return REFERENCES;
(?i:select)												return SELECT;
(?i:set)												return SET;
(?i:table)												return TABLE;
(?i:unique)												return UNIQUE;
(?i:update)												return UPDATE;
(?i:values)												return VALUES;
(?i:varchar)											return VARCHAR;
(?i:where)												return WHERE;


"<>" 	|
"<"		|
">"		|
"<="	|
">="			return OPERATOR;

"="				return EQUAL;
"+"				return PLUS;
"-"				return MINUS;
"*"				return STAR;
"/"				return SLASH;
"("				return LEFT_BRACKET;
")"				return RIGHT_BRACKET;
","				return COMMA;
";"				return SEMICOLON;


[A-Za-z_][A-Za-z0-9_]*									|
[A-Za-z_][A-Za-z0-9_]*"."[A-Za-z_][A-Za-z0-9_]*					return IDENTIFIER;


[0-9]+					|
[0-9]+"."[0-9]+ 				return NUMBER;


[\"][^\"]*[\"]		|
'[^']*'							return STRING;											


[ \t\n\r]+			/* white space */ ;


[\"][^\"]*$								{printf("Error found near < %s >.\n",yytext);
														exit(EXIT_SUCCESS);}
'[^']*$									{printf("Error found near < %s >.\n",yytext);
														exit(EXIT_SUCCESS);}


[0-9]+[A-Za-z_][A-Za-z0-9_]*						{printf("Error found near < %s >.\n",yytext);
														exit(EXIT_SUCCESS);}


.				/* any invalid non-sql character */			{printf("Error found near < %s >.\n",yytext); 
																		exit(EXIT_SUCCESS);}	


%%

int yywrap(void)
{
	return 1;
}

