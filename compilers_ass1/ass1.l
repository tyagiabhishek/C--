%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ass1.h"

	void print_str_token(char *token, char *tag, int token_no);
	void find_n_print_keyword(char *token);

%}
%%
						/* SQL predefined keywords */

(?i:add)												|
(?i:all)												|
(?i:alter)												|
(?i:and)												|
(?i:any)												|
(?i:as)													|
(?i:asc)												|
(?i:auto_increment)										|
(?i:avg)												|
(?i:by)													|
(?i:(CHAR(ACTER)?))										|
(?i:column)												|
(?i:count)												|
(?i:create)												|
(?i:decimal)											|
(?i:default)											|
(?i:delete)												|
(?i:desc)												|
(?i:distinct)											|
(?i:double)												|
(?i:drop)												|
(?i:exit)												|
(?i:exists)												|
(?i:float)												|
(?i:foreign)											|
(?i:from)												|
(?i:group)												|
(?i:having)												|
(?i:in)													|
(?i:insert)												|
(?i:(int(eger)?))										|
(?i:into)												|
(?i:join)												|
(?i:key)												|
(?i:like)												|
(?i:limit)												|
(?i:max)												|
(?i:min)												|
(?i:not)												|
(?i:null)												|
(?i:numeric)											|
(?i:on)													|
(?i:or)													|
(?i:order)												|
(?i:primary)											|
(?i:real)												|
(?i:references)											|
(?i:select)												|
(?i:set)												|
(?i:smallint)											|
(?i:sum)												|
(?i:table)												|
(?i:union)												|
(?i:unique)												|
(?i:update)												|
(?i:values)												|
(?i:varchar)											|
(?i:where)																{find_n_print_keyword(yytext);}


						/* Operators */

"="		| 
"<>" 	|
"<"		|
">"		|
"<="	|
">="	|	
[-+*/]																print_str_token(yytext,"Operator",OPERATOR); 				

						
						/* SQL symbols */
"("																		print_str_token(yytext,"Left Bracket",LEFT_BRACKET);
")"																	print_str_token(yytext,"Right Bracket",RIGHT_BRACKET);
","																		print_str_token(yytext,"Comma",COMMA);


					/* string literal */

[\"][^\"]*[\"]		|
'[^']*'																print_str_token(yytext,"String Literal",STRING);


						/* names */

[A-Za-z_][A-Za-z0-9_]*	|
[A-Za-z_][A-Za-z0-9_]*"."[A-Za-z_][A-Za-z0-9_]*								print_str_token(yytext,"Identifier",IDENTIFIER);
						

						/* numbers */

[0-9]+				|
[0-9]+"."[0-9]+ 																print_str_token(yytext,"Number",NUMBER);


[ \t\n\r]+			/* white space */									;


;					/* semi colon */									{print_str_token(yytext,"Semicolon",SEMICOLON); yylineno++;}


					/* invalid string literal */

[\"][^\"]*$								{printf("Error found in query no. %d near < %s >.\n",yylineno,yytext);
														exit(EXIT_SUCCESS);}
'[^']*$									{printf("Error found in query no. %d near < %s >.\n",yylineno,yytext);
														exit(EXIT_SUCCESS);}


[0-9]+[A-Za-z_][A-Za-z0-9_]*						{printf("Error found in query no. %d near < %s >.\n",yylineno,yytext);
														exit(EXIT_SUCCESS);}


.				/* any invalid non-sql character */			{printf("Error found in query no. %d near < %s >.\n",yylineno,yytext); 
																		exit(EXIT_SUCCESS);}	
%%

int yywrap(void)
{
	return 1;
}
const char *sql_keywords[] = {"add", "all", "alter", "and", "any", "as", "asc", "auto_increment", "avg", "by", "char", "character", "column", "count", "create", "decimal", "default", 
"delete", "desc", "distinct", "double", "drop", "exists", "exit", "float", "foreign", "from", "group", "having", "in", "insert", "int", 
"integer", "into", "join", "key", "like", "limit", "max", "min", "not", "null", "numeric", "on", "or", "order", "primary", "real", "references", 
"select", "set", "smallint", "sum", "table", "union", "unique", "update", "values", "varchar", "where", NULL};

void print_str_token(char *token, char *tag, int token_no)
{
	printf("%20s --- < %d, %s, %s >\n", token, token_no, token, tag);
}

void find_n_print_keyword(char *token)
{
	int i;
	char *copy = (char *)malloc((strlen(token)+1)*sizeof(char));
	for(i=0;token[i];i++)
	{
		copy[i] = tolower(token[i]);
	}
	copy[i] = token[i];
	for(i=0;sql_keywords[i];i++)
	{
		if(!strcmp(token,sql_keywords[i]))
			break;
	}
	print_str_token(copy,"SQL keyword",i+1);
}