#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ass1.h"


typedef int bool;
#define true 1
#define false 0

#define MAX 100000
int length = 0;
int tokens[MAX];

const char *sql_keywords[] = {"add", "all", "alter", "and", "any", "as", "asc", "auto_increment", "avg", "by", "char", "character", "column", "count", "create", "decimal", "default", 
"delete", "desc", "distinct", "double", "drop", "exists", "exit", "float", "foreign", "from", "group", "having", "in", "insert", "int", 
"integer", "into", "join", "key", "like", "limit", "max", "min", "not", "null", "numeric", "on", "or", "order", "primary", "real", "references", 
"select", "set", "smallint", "sum", "table", "union", "unique", "update", "values", "varchar", "where", NULL};


const char delim[] = {' ', '\t', '\n', '\r', '\0'};
const char operators[] = {'=', '<', '>', '-', '+', '*', '/', '.','\0'};
const char left_bracket = '(';
const char right_bracket = ')';
const char comma = ',';
const char semi_colon = ';';


void print_char_token(char token, char *tag, int token_no)
{
	printf("%20c --- < %d, %c, %s >\n", token, token_no, token, tag);
}

void print_str_token(char *token, char *tag, int token_no)
{
	printf("%20s --- < %d, %s, %s >\n", token, token_no, token, tag);
}

void print_char_error(char token, int query_count)
{
	printf("Error found in < %c > in line no. %d.\n", token, query_count);
}

void print_str_error(char *token, int query_count)
{
	printf("Error found in < %s > in line no. %d.\n", token, query_count);
}

bool is_ident(char ch)
{
	if(isalpha(ch)||isdigit(ch)||ch=='_'||ch=='.')
		return true;
	return false;
}

bool is_delimeter(char ch)
{
	int i=0;
	for(i=0;delim[i];i++)
		if(delim[i] == ch)
			return true;
	return false;
}

bool is_operator(char ch)
{
	int i=0;
	for(i=0;operators[i];i++)
	{
		if(operators[i] == ch)
			return true;
	}
	return false;
}

int is_keyword(char *token)
{
	int i;
	for(i=0;sql_keywords[i];i++)
	{
		if(!strcmp(token,sql_keywords[i]))
			return i+1;
	}
	return 0;
}

bool is_identifier(char *token)
{
	int i,c=0;
	int f=0;
	if(!isalpha(token[0])&&token[0]!='_')
		return false;
	for(i=0;token[i];i++)
	{
		if(token[i]=='.')
		{
			c++;
			if(c==1)
			{
				if(!token[i+1]||(!isalpha(token[i+1]) && token[i+1]!='_'))
					f=1;
			}
		}
	}
	if(c>1||f)
		return false;
	return true;
}

bool is_num(char *token)
{
	int i,c=0;
	for(i=0;token[i];i++)
	{
		if(isdigit(token[i]) || token[i]=='.')
		{
			if(token[i]=='.')
				c++;
		}
		else
			return false;
	}
	if(c>1)
		return false;
	return true;
}

void error(char *token, int len, int *query_count)
{
	char ch;
	ch = getc(stdin);
	while(ch!=EOF&&ch!=';')
	{
		token[len++] = ch;
		ch = getc(stdin);
	}
	if(ch==';')
	{
		token[len++] = ch;
		token[len] = '\0';
		print_str_error(token, *query_count);
		(*query_count)++;
	}
	else
	{
		ungetc(ch,stdin);
		token[len] = '\0';
		print_str_error(token, *query_count);
	}
}

int main()
{
	char ch;
	int query_count = 1;
	int tok_cnt;
	ch = getc(stdin);
	while(ch != EOF)
	{
		if(ch == left_bracket)
		{
			tokens[len++] = LEFT_BRACKET;
			print_char_token(ch,"Left Bracket",LEFT_BRACKET);
		}		
		else if(ch == right_bracket)
		{
			tokens[len++] = RIGHT_BRACKET;
			print_char_token(ch,"Right Bracket",RIGHT_BRACKET);
		}
		else if(ch == comma)
		{
			tokens[len++] = COMMA;
			print_char_token(ch,"Comma",COMMA);
		}
		else if(ch == semi_colon)
		{
			tokens[len++] = SEMICOLON;
			print_char_token(ch,"Semicolon",SEMICOLON);
			query_count++;
		}
		else if(is_ident(ch))
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			char *token_copy = (char *)malloc(MAX*sizeof(char));
			int len=0;	
			while(is_ident(ch))
			{
				token[len] = tolower(ch);
				token_copy[len] = ch;
				len++;
				ch = getc(stdin);
			}
			ungetc(ch,stdin);
			token[len] = token_copy[len] = '\0';
			if((tok_cnt=is_keyword(token))!=0)
			{
				tokens[len++] = tok_cnt;
				print_str_token(token_copy,"SQL keyword",tok_cnt);
			}
			else if(is_identifier(token))
			{
				tokens[len++] = IDENTIFIER;
				print_str_token(token_copy,"Identifier",IDENTIFIER);
			}
			else if(is_num(token))
			{
				tokens[len++] = NUMBER;
				print_str_token(token_copy,"Number",NUMBER);
			}
			else 
			{
				tokens[len++] = ERROR;
				error(token_copy,len,&query_count);
			}

			free(token_copy);
			free(token);
			
		}
		else if(is_operator(ch))
		{
			char ch_new = getc(stdin);
			if(((ch == '>' || ch == '<') && ch_new == '=') || (ch=='<'&&ch_new == '>'))
			{
				char *token = (char *)malloc(10*sizeof(char));
				token[0] = ch;
				token[1] = ch_new;
				token[2] = '\0';
				print_str_token(token,"Operator",OPERATOR);
				free(token);
			}
			else
			{
				ungetc(ch_new,stdin);
				if(ch=='*')
					print_char_token(ch,"Star",STAR);
				else
					print_char_token(ch,"Operator",OPERATOR);
			}
			tokens
		}
		else if(ch=='"')
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			int len = 0;
			token[len++] = ch;
			ch = getc(stdin);
			while(ch!='"'&&ch!=EOF)
			{
				token[len++] = ch;
				ch = getc(stdin);
			}
			if(ch==EOF)
			{
				token[len] = '\0';
				print_str_error(token,query_count);
			}
			else
			{
				token[len++] = ch;
				token[len] = '\0';
				print_str_token(token,"String Literal",STRING);
			}
			free(token);
		}
		else if(ch=='\'')
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			int len = 0;
			token[len++] = ch;
			ch = getc(stdin);
			while(ch!='\''&&ch!=EOF)
			{
				token[len++] = ch;
				ch = getc(stdin);
			}
			if(ch==EOF)
			{
				token[len] = '\0';
				print_str_error(token,query_count);
			}
			else
			{
				token[len++] = ch;
				token[len] = '\0';
				print_str_token(token,"String Literal",STRING);
			}
			free(token);
		}
		else if(is_delimeter(ch))
		{

		}
		else
		{
			char *token = (char *)malloc(MAX*sizeof(char));
			int len = 0;
			ungetc(ch,stdin);
			error(token,len,&query_count);
			free(token); 
		}
		ch = getc(stdin);
	}
	return 0;
}  
