%{
	#include <stdio.h>
	#include <stdlib.h>

	void yyerror(char *s);
%}


%left OR
%left AND
%left NOT

%token ADD ALL ALTER BETWEEN BY
%token CHAR COLUMN CREATE 
%token DECIMAL DELETE DISTINCT DOUBLE DROP
%token FOREIGN FROM
%token IN INSERT INT INTO
%token KEY NUL 
%token PRIMARY
%token REFERENCES SELECT SET
%token TABLE
%token UNIQUE UPDATE VALUES VARCHAR WHERE 

%left PLUS MINUS
%left STAR SLASH
%left OPERATOR EQUAL

%token IDENTIFIER
%token NUMBER
%token STRING
%token COMMA LEFT_BRACKET RIGHT_BRACKET SEMICOLON
%token ERROR

%start sql_start

%%

sql_start:		sql_stmt
			|	sql_stmt sql_start
			;

sql_stmt:	create
		|	select
		|	insert
		|	update
		|	delete
		|	drop
		|	alter
		; 

create:		CREATE TABLE IDENTIFIER LEFT_BRACKET table_columns RIGHT_BRACKET SEMICOLON {printf("Create cmd.\n");} ;

table_columns:	table_column
			|	table_column COMMA table_columns
			;

table_column:	IDENTIFIER coln_type coln_constr ;

coln_type:		CHAR LEFT_BRACKET NUMBER RIGHT_BRACKET
			|	INT
			|	VARCHAR	LEFT_BRACKET NUMBER RIGHT_BRACKET
 			|	DECIMAL LEFT_BRACKET NUMBER RIGHT_BRACKET
 			|	DOUBLE
 			;

coln_constr:
			|	NOT NUL
			|	NOT NUL UNIQUE
			|	NOT NUL PRIMARY KEY
			|	REFERENCES IDENTIFIER LEFT_BRACKET variables RIGHT_BRACKET
			;

variables:		IDENTIFIER
			| 	IDENTIFIER COMMA variables
			;

select:		SELECT optional_distinct select_list FROM variables optional_where SEMICOLON {printf("Select cmd.\n");} ;

optional_distinct:	
					|	ALL
					|	DISTINCT
					;

select_list:	expressions
			|	STAR
			;

expressions:	expression
			|	expression COMMA expressions
			;

expression:		expression PLUS expression
			|	expression MINUS expression
			|	expression STAR expression
			|	expression SLASH expression
			|	LEFT_BRACKET expression RIGHT_BRACKET
			|	IDENTIFIER
			|	NUMBER
			|	STRING
			;

optional_where:		
				|	WHERE where_condition
				;

where_condition:	where_condition AND where_condition
				|	where_condition OR where_condition
				|	LEFT_BRACKET where_condition RIGHT_BRACKET
				|	conditions
				;

conditions:		comp_conditions
			|	between_conditions
			|	in_conditions
			;

comp_conditions:	expression OPERATOR expression
				|	expression OPERATOR	nested_query
				|	expression EQUAL expression
				|	expression EQUAL nested_query
				;

between_conditions:		expression BETWEEN expression AND expression
					|	expression NOT BETWEEN expression AND expression
					;

in_conditions:		expression NOT IN nested_query 
				|	expression IN nested_query 
				;

nested_query: LEFT_BRACKET SELECT optional_distinct select_list FROM variables optional_where RIGHT_BRACKET ;	


insert:		INSERT INTO IDENTIFIER optional_attributes VALUES LEFT_BRACKET values_list RIGHT_BRACKET SEMICOLON {printf("Insert cmd.\n");} ;

optional_attributes:	
					|	LEFT_BRACKET variables RIGHT_BRACKET ;

values_list:	value
			|	value COMMA values_list
			;

value:		NUMBER
		|	STRING
		|	NUL
		;


update:	UPDATE IDENTIFIER SET key_value_pairs optional_where SEMICOLON {printf("Update cmd.\n");} ;

key_value_pairs:	key_value_pair
				|	key_value_pair COMMA key_value_pairs 
				;

key_value_pair:		IDENTIFIER EQUAL value ;


delete:		DELETE FROM IDENTIFIER optional_where SEMICOLON {printf("Delete cmd.\n");} ;

drop:		DROP TABLE IDENTIFIER SEMICOLON {printf("Drop cmd.\n");} ;

alter:		ALTER TABLE IDENTIFIER drop_add SEMICOLON {printf("Alter cmd.\n");} ;

drop_add:		DROP COLUMN IDENTIFIER
			|	ADD IDENTIFIER coln_type coln_constr
			;


%%
void yyerror(char *s)
{
	printf("ERROR: %s\n",s);
}

int main()
{
	return yyparse();
}