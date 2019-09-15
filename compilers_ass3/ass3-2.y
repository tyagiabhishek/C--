%{
	#include <stdio.h>
	#include <stdlib.h>
	void yyerror(char *s);
%}


%token PLUS MINUS STAR SLASH
%token LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token LEFT_CLOSED_BRACKET RIGHT_CLOSED_BRACKET
%token LEFT_OPEN_BRACKET RIGHT_OPEN_BRACKET

%token IDENTIFIER
%token NUMBER_INT
%token NUMBER_FLOAT 
%token TYPEDEF
%token INTEGER FLOAT CHAR VOID STRUCT

%token SEMICOLON 

%token OR AND EQUALS LESS_THAN GREATER_THAN 
%token IF NOT WHILE

%token CHARACTER QUOT RETURN COMMA

%right ELSE

%start code

%%

code:				struct_decl code	
				|	func_defn_decl code
				|	
				;

struct_decl:		STRUCT IDENTIFIER LEFT_CURLY_BRACKET dlist RIGHT_CURLY_BRACKET SEMICOLON
				;

func_defn_decl:		func_head func_body
				|	func_head SEMICOLON
				;

func_body:			LEFT_CURLY_BRACKET optional_stmt optional_return RIGHT_CURLY_BRACKET
				;

optional_return:	RETURN SEMICOLON;
				|	RETURN exp SEMICOLON;
				|
				;

optional_stmt:		stmt_list
				|
				;

func_head:			res_id LEFT_OPEN_BRACKET decl_plist RIGHT_OPEN_BRACKET
				;

res_id:				result mult_star IDENTIFIER
				;

result:				INTEGER										
				|	FLOAT			
				|	CHAR				
				|	VOID				
				|	STRUCT IDENTIFIER	
				;

decl_plist:			decl_param COMMA decl_plist
				|	decl_param
				| 	VOID
				|
				;

decl_param:			type decl_ids
				;

decl_ids:			mult_star IDENTIFIER br_param
				;

mult_star:			STAR mult_star
				|	
				;

br_param:			LEFT_CLOSED_BRACKET NUMBER_INT RIGHT_CLOSED_BRACKET br_param
				|
				;

dlist:				declaration 
				|	dlist declaration 
				;

var_decl:			declaration 
				;

declaration:		type list_id SEMICOLON			
												

type:				INTEGER				
				|	FLOAT			
				|	CHAR				
				|	STRUCT IDENTIFIER		
				;

list_id:			id_arr							
				| 	list_id COMMA id_arr						
				;

id_arr:				mult_star IDENTIFIER EQUALS exp		
				|	mult_star IDENTIFIER br_dimlist		
				|	mult_star IDENTIFIER br_dimlist EQUALS LEFT_CURLY_BRACKET elist RIGHT_CURLY_BRACKET
				|	mult_star IDENTIFIER
				;

elist:				exp
				|	exp COMMA elist
				;

br_dimlist:			LEFT_CLOSED_BRACKET NUMBER_INT RIGHT_CLOSED_BRACKET																
				|	LEFT_CLOSED_BRACKET NUMBER_INT RIGHT_CLOSED_BRACKET br_dimlist
				;

body:				LEFT_CURLY_BRACKET optional_stmt RIGHT_CURLY_BRACKET
				;

stmt_list:			stmt_list stmt
				|	stmt
				;

stmt:				matched_stmt
				|	ifexp stmt
				|	ifexp matched_stmt ELSE stmt
				;

matched_stmt:		whileexp body
				|	asg SEMICOLON
				|	func_call SEMICOLON
				|	body
				|	var_decl
				;

ifexp:				IF exp    		
				;

whileexp:			WHILE exp							
				;

asg:				lhs EQUALS exp				
				;

lhs:				IDENTIFIER
				|	STAR IDENTIFIER 
				|	STAR IDENTIFIER br_elist
				|	IDENTIFIER br_elist
				;

br_elist:			LEFT_CLOSED_BRACKET exp RIGHT_CLOSED_BRACKET																		
				|	LEFT_CLOSED_BRACKET exp RIGHT_CLOSED_BRACKET br_elist																
				;

exp:				exp OR OR aa_exp	
				|	aa_exp												
				;

aa_exp:				d_exp										
				|	aa_exp AND AND d_exp 																		
				;			

d_exp:				pm_exp																	
				|	pm_exp GREATER_THAN pm_exp																	
				|	pm_exp NOT EQUALS pm_exp												
				|	pm_exp EQUALS EQUALS pm_exp												
				|	pm_exp LESS_THAN pm_exp											
				|	pm_exp LESS_THAN EQUALS pm_exp												
				|	pm_exp GREATER_THAN EQUALS pm_exp											
				|	NOT LEFT_OPEN_BRACKET exp RIGHT_OPEN_BRACKET										
				;

pm_exp:				pm_exp PLUS t_exp																		
				|	pm_exp MINUS t_exp																
				|	t_exp
				;

t_exp:				f_exp STAR t_exp																
				|	f_exp SLASH t_exp														
				|	f_exp																					
				;

f_exp:				NUMBER_INT
				|	NUMBER_FLOAT			
				|	STAR IDENTIFIER
				|	AND IDENTIFIER
				|	IDENTIFIER
				|	STAR IDENTIFIER br_elist
				|	AND IDENTIFIER br_elist 
				|	IDENTIFIER br_elist
				|	func_call
				|	LEFT_OPEN_BRACKET exp RIGHT_OPEN_BRACKET					
				;

func_call:			IDENTIFIER LEFT_OPEN_BRACKET paramlist RIGHT_OPEN_BRACKET
				;

paramlist:			plist
				|
				;

plist:				exp COMMA plist
				|	exp
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

