%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <iostream>
	#include <bits/stdc++.h>
	#include "definition.h"
	using namespace std;

	vector<func_name_table> global_func;
	vector<quadruple> quad_table;
	vector<struct_name_table> global_struct;
	variable *vn, *pn, *vnptr, *pnptr;
	int active_func_ptr = -1, call_func_ptr = -1, level = 0, namptr = -1, fnptr = -1,active_struct_ptr = -1,strptr = -1;
	bool found, ok;
	int nextquad = 0, temp_var = 0;
	int line_no = 1, error_flag = 0;
	void yyerror(string s);
	int yylex();
	int get_size(enum t type);
	void patchtype(enum t type,vector <variable*> &namelist,string name);
	void backpatch(vector<int> list, int quad_number);
	void gen(quadruple quad);
	void newtemp(variable *var);
	void delete_param_list(int active_func_ptr, int level);
	void error (string err);
	enum t not_compatible(enum t type);
	enum t compare_types(enum t type1,enum t type2);
	void search_func(string name, bool &found, int &namptr);
	void enter_func(string name, enum t type, int &namptr, string struct_name);
	void search_var(string name, int active_func_ptr, int level, bool &found, variable* &vn);
	void enter_var(string name, bool type, int level, int active_func_ptr, variable* &namptr, vector<int> dimlist, int pointer);
	void search_param(string name, int active_func_ptr, bool &found, variable* &pn);
	void delete_var_list(int active_func_ptr, int level);
	void enter_param(string name, bool type, enum t type2, int active_func_ptr, string struct_name, int pointer, vector<int> dimlist);
	enum t get_result_type(int fnptr);
	void check_param_type(int call_func_ptr, int param_no, variable* var, bool &ok);
	enum t get_variable_type(string name, int active_func_ptr, int level);
	void search_struct(string name,bool &found, int &strptr);
	void enter_struct(string name ,int &strptr);
	void search_struct_var(string name, int active_struct_ptr , bool &found, variable* &vn);
	void enter_struct_var(string name, bool type, int active_struct_ptr, variable * &vnptr, vector<int> dimlist, int pointer);
	void conv_float_quad(variable *a,variable *operand1);
	void conv_int_quad(variable *a,variable *operand1);
	void conv_bool_quad(variable *a,variable *operand1);
	bool coercible(enum t type_1, enum t type_2);
	bool compatible_arithop(enum t type_1, enum t type_2);
%}
%union
{
	res* reslt;
	string* val;
	variable * var;
	vector<int> *list;
	int int_val;
	float float_val;
	smt_l* smt;
	while_struct *wstruct;
	lhs* lhs_var;
}


/*  *********************** TO BE DONE ******************

1. STAR and ELIST together like int *a allows you to use a[10]




*/ 
%token PLUS MINUS STAR SLASH
%token LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET
%token LEFT_CLOSED_BRACKET RIGHT_CLOSED_BRACKET
%token LEFT_OPEN_BRACKET RIGHT_OPEN_BRACKET

%token <val> IDENTIFIER CHARACTER
%token <int_val> NUMBER_INT
%token <float_val> NUMBER_FLOAT 
%token TYPEDEF
%token INTEGER FLOAT CHAR VOID STRUCT DOT

%token SEMICOLON 

%token OR AND EQUALS LESS_THAN GREATER_THAN 
%token IF NOT WHILE

%token QUOT RETURN COMMA

%right ELSE

%type <lhs_var> lhs br_elist;
%type <wstruct> whileexp;
%type <reslt> result type list_id  struct_list_id;
%type <var> decl_ids id_arr exp  t_exp f_exp pm_exp aa_exp d_exp func_call;
%type <list> br_dimlist br_param ifexp n_inter;
%type <int_val> paramlist plist m_inter;
%type <smt> stmt matched_stmt optional_stmt stmt_list body func_body;

%start code

%%

code:				code_do
													{
														search_func("main", found, fnptr);
														if(!found)
														{
															error("main not declared");
														}
														if(error_flag == 0)
														{
															for(int i = 0; i < quad_table.size(); i++)
															{
																quadruple q;
																q = quad_table[i];
																cout<<"L"<<i<<": "<<q.s1<<" "<<q.oprnd_1<<" "<<q.s2<<" "<<q.oprnd_2<<" "<<q.s3<<" "<<q.oprnd_3<<" "<<q.s4<<endl;
															}
														}
													}

code_do:				struct_decl code_do	
					|	func_defn_decl code_do
					|	
					;

struct_decl:		str_head LEFT_CURLY_BRACKET dslist RIGHT_CURLY_BRACKET SEMICOLON
													{
														active_struct_ptr = -1;
													}
				;

str_head:			STRUCT IDENTIFIER
													{
														search_struct(*($2),found,strptr);
														if (found)
														{
															error("Structure already declared");
														}
														else 
														{
															enter_struct(*($2),strptr);
														}
														active_struct_ptr = strptr;
													}
				;

func_defn_decl:		func_head func_body
													{
														if(global_func[active_func_ptr].res_type != VOI && $2->ret == false)
														{
															error("return statement not found for function " + global_func[active_func_ptr].name);
														}
														if(error_flag==0)
														{
															delete_var_list(active_func_ptr, 2);
															delete_param_list(active_func_ptr, 1);
															
														}
														active_func_ptr = -1;
														level = 0;
													}
				;

func_body:			LEFT_CURLY_BRACKET optional_stmt RIGHT_CURLY_BRACKET
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														$$->ret = $2->ret;
														backpatch(*$2->list, nextquad);
														quadruple q;
														q.s1 = "func end";
														q.oprnd_1 = q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
														gen(q);
													}
				;

optional_stmt:		stmt_list
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = (*$1->list);
														$$->ret = $1->ret;
													}
				|
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														$$->ret = false;
													}
				;

func_head:			res_id LEFT_OPEN_BRACKET decl_plist RIGHT_OPEN_BRACKET
													{
														level = 2;
													}
				;

res_id:				result IDENTIFIER	
													{
														search_func(*$2, found, namptr);
														if(found)
														{
															error("Function already declared");
														}
														else
														{
															enter_func(*$2, $1->type, namptr, $1->struct_name);
															quadruple q;
															q.s1 = "func begin";
															q.oprnd_1 = *$2;
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
														}
														active_func_ptr = namptr;
														level = 1;
													}
				;

result:				INTEGER				
													{
														$$ = new res;
														$$->type = INT;
														$$->struct_name = "";
													}
				|	FLOAT				
													{
														$$ = new res;
														$$->type = REAL;
														$$->struct_name = "";
													}
				|	CHAR				
													{
														$$ = new res;
														$$->type = CHA;
														$$->struct_name = "";
													}
				|	VOID				
													{
														$$ = new res;
														$$->type = VOI;
														$$->struct_name = "";
													}
				|	STRUCT IDENTIFIER	
													{
														$$ = new res;
														$$->type = STRUC;
														$$->struct_name = *$2;
														search_struct(*($2),found,strptr);
														if(!found)
														{
															error("Structure not defined "+ *($2));
														}
													}
				;

decl_plist:			decl_param COMMA decl_plist
				|	decl_param
				| 	VOID
				|
				;

decl_param:			type decl_ids
													{
														search_param($2->name, active_func_ptr, found, pnptr);
														if(found)
														{
															error("Parameter already declared");
														}
														else
														{
															enter_param($2->name, $2->type, $1->type, active_func_ptr, $1->struct_name, $2->pointer, *($2->dimlist));
														}
													}
				;

decl_ids:			IDENTIFIER br_param
													{
														$$ = new variable;
														$$->type = ($2->size()>0);
														$$->name = *($1);
														$$->dimlist = new vector<int>;
														*($$->dimlist) = *($2);
													}
				;

br_param:			LEFT_CLOSED_BRACKET NUMBER_INT RIGHT_CLOSED_BRACKET br_param
													{
														$$ = new vector<int>;
														(*$$) = *$4;
														(*$$).insert((*$$).begin(), $2);
													}
				|
													{
														$$ = new vector<int>;
														(*$$).clear();
													}
				;

dslist:				struct_declaration
				|	dslist struct_declaration
				;


var_decl:			declaration
				;

struct_declaration: type struct_list_id SEMICOLON			
													{
														if($1->type!=STRUC)
															patchtype ($1->type,$2->namelist,"");
														else 
															patchtype($1->type,$2->namelist,$1->struct_name);   //todo //function table variablelist and its level
													}		
				;



declaration:		type list_id SEMICOLON			
													{
														if($1->type!=STRUC)
															patchtype ($1->type,$2->namelist,"");
														else 
															patchtype($1->type,$2->namelist,$1->struct_name);   //todo //function table variablelist and its level
													}		
				;								

type:				INTEGER				
													{
														$$ = new res;
														$$->type = INT;
														$$->struct_name = "";
													}
				|	FLOAT		
													{
														$$ = new res;
														$$->type = REAL;
														$$->struct_name = "";
													}	
				|	CHAR				
													{
														$$ = new res;
														$$->type = CHA;
														$$->struct_name = "";
													}
				|	STRUCT IDENTIFIER		
													{
														$$ = new res;
														$$->type = STRUC;
														$$->struct_name = *$2;
														search_struct(*($2),found,strptr);
														if(!found)
														{
															error("structure not declared "+ *($2));
														}
													}
				;

struct_list_id:  	id_arr														
													{
														search_struct_var(($1)->name, active_struct_ptr, found, vn);
														$$=new res;
														if(found)
														{
															error("Variable already declared in the structure");
														}
														else
														{
															enter_struct_var(($1)->name, $1->type, active_struct_ptr, vnptr, *(($1)->dimlist), $1->pointer);
															($$->namelist).push_back(vnptr);
														}
													}
				| 	struct_list_id COMMA id_arr														
													{
														search_struct_var(($3)->name, active_struct_ptr, found, vn);
														$$=new res;
														$$->namelist = $1->namelist;
														if(found)
														{
															error("Variable already declared in the structure");
														}																	
														else
														{
															enter_struct_var(($3)->name, $3->type, active_struct_ptr, vnptr, *(($3)->dimlist), $3->pointer);
															($$->namelist).push_back(vnptr);
														}
													}
				;

list_id:			id_arr
													{
														search_var(($1)->name, active_func_ptr, level, found, vn);
														$$=new res;
														
														if(found && vn->level == level)
														{
															error("Variable already declared at same level");
														}
														else if(level == 2)
														{
															search_param(($1)->name, active_func_ptr, found, pn);
															if(found)
															{
																error("Redeclaration of parameter as a variable");
															}
															else
															{
																enter_var(($1)->name, $1->type, level, active_func_ptr, vnptr, *(($1)->dimlist), ($1)->pointer);
																($$->namelist).push_back(vnptr);
															}
														}
														else
														{
															enter_var(($1)->name, $1->type, level, active_func_ptr, vnptr, *(($1)->dimlist), ($1)->pointer);
															($$->namelist).push_back(vnptr);
														}
													}
				| 	list_id COMMA id_arr														
													{
														search_var(($3)->name, active_func_ptr, level, found, vn);
														$$=new res;
														$$->namelist = $1->namelist;
														if(found && vn->level == level)
														{
															error("Variable already declared at same level");
														}
														else if(level == 2)
														{
															search_param(($3)->name, active_func_ptr, found, pn);
															if(found)
															{
																error("Redeclaration of parameter as a variable");
															}
															else
															{
																enter_var(($3)->name, $3->type, level, active_func_ptr, vnptr, *(($3)->dimlist), ($3)->pointer);
																($$->namelist).push_back(vnptr);
															}
														}
														else
														{
															enter_var(($3)->name, $1->type, level, active_func_ptr, vnptr, *(($3)->dimlist), ($3)->pointer);
															($$->namelist).push_back(vnptr);
														}
													}
				;

id_arr:				IDENTIFIER br_dimlist	
													{
														$$ = new variable;
														$$->name = *$1;
														$$->type = 1;
														$$->dimlist = new vector<int>;
														// $$->var_type = 1; 
														*($$->dimlist) = *($2);
													}	
				|	IDENTIFIER
													{
														$$ = new variable;
														$$->name = *$1;
														$$->type = 0;
														$$->dimlist = new vector<int>;
														(*($$->dimlist)).clear();
														// $$->var_type = 1;    //todo level 
													}
				;


br_dimlist:			LEFT_CLOSED_BRACKET NUMBER_INT RIGHT_CLOSED_BRACKET		
													{
														$$ = new vector<int>;
														(*$$).insert((*$$).begin(),$2);
													}
				|	LEFT_CLOSED_BRACKET NUMBER_INT RIGHT_CLOSED_BRACKET br_dimlist
													{
														$$ = new vector<int>;
														(*$$) = *$4;
														(*$$).insert((*$$).begin(),$2);
													}
				;

body:				LEFT_CURLY_BRACKET {level++;} optional_stmt RIGHT_CURLY_BRACKET
													{
														delete_var_list(active_func_ptr, level);
														level--;
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = (*$3->list);
														$$->ret = $3->ret;
													}
				;

stmt_list:			stmt_list m_inter stmt
													{
														backpatch(*$1->list, $2);
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = (*$3->list);
														$$->ret = $3->ret || $1->ret;
													}
				|	stmt
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = (*$1->list);
														$$->ret = $1->ret;
													}
				;

stmt:				matched_stmt
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = (*$1->list);
														$$->ret = $1->ret;
													}
				|	ifexp stmt
													{
														$$ = new smt_l;
														$$->ret = false;
														$$->list = new vector<int>;
														// (*$$).reserve((*$1).size() + (*$2).size());
														for(int i =0;i<(*$2->list).size();i++)
															(*$$->list).push_back((*$2->list)[i]);
														for(int i =0;i<(*$1).size();i++)
															(*$$->list).push_back((*$1)[i]);
														// (*$$).insert((*$$).end(), (*$2).begin(), (*$2).end());
														// (*$$).insert((*$$).end(), (*$1).begin(), (*$1).end());
													}
				|	ifexp matched_stmt n_inter ELSE m_inter stmt
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														$$->ret = $2->ret && $6->ret;
														backpatch(*$1, $5);
														for(int i =0;i<(*$2->list).size();i++)
															(*$$->list).push_back((*$2->list)[i]);
														for(int i =0;i<(*$3).size();i++)
															(*$$->list).push_back((*$3)[i]);
														for(int i =0;i<(*$6->list).size();i++)
															(*$$->list).push_back((*$6->list)[i]);
														// (*$$).reserve((*$2).size() + (*$3).size() + (*$6).size());
														// (*$$).insert((*$$).end(), (*$2).begin(), (*$2).end());
														// (*$$).insert((*$$).end(), (*$3).begin(), (*$3).end());
														// (*$$).insert((*$$).end(), (*$6).begin(), (*$6).end());
													}
				;

n_inter:	
													{
														$$ = new vector<int>;
														(*$$).push_back(nextquad);
														quadruple q;
														q.s1 = "goto";
														q.oprnd_1 = "__";
														q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
														gen(q);
													}
				;

m_inter:	
													{
														$$ = nextquad;
													}
				;

matched_stmt:		whileexp body
													{
														quadruple q;
														q.s1 = "goto";
														q.oprnd_1 = $1->begin;
														q.s2 = "";
														q.oprnd_2 = "0";
														q.s3 = "";
														q.oprnd_3 = "";
														q.s4 = "";
														gen(q);
														backpatch(*$2->list, $1->begin);
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = ($1->falselist);
														$$->ret = false;
													}
				|	asg SEMICOLON
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														$$->ret = false;
													}
				|	func_call SEMICOLON
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														$$->ret = false;
													}
				|	RETURN exp SEMICOLON
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														$$->ret = false;
														enum t type = get_result_type(active_func_ptr);

														if(type != $2->eletype || $2->type!=0)
														{
															error("Return type mismatch");
														}
														else
														{
															if((type != STRUC) || ($2->struct_name == global_func[active_func_ptr].struct_name))
															{
																quadruple q;
																q.s1 = "return";
																q.oprnd_1 = $2->name;
																q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
																gen(q);
																$$->ret = true;
															}
															else
															{
																error("Return type mismatch");
															}
														}
													}
				|	RETURN SEMICOLON
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														enum t type = get_result_type(active_func_ptr);
														if(type != VOI)
														{
															$$->ret = false;
															error("Return type mismatch");
														}
														else
														{
															quadruple q;
															q.s1 = "return";
															q.oprnd_1 = "";
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
															$$->ret = true;
														}
													}
				|	body
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list) = (*$1->list);
														$$->ret = $1->ret;
													}
				|	var_decl
													{
														$$ = new smt_l;
														$$->list = new vector<int>;
														(*$$->list).clear();
														$$->ret = false;
													}
				;

ifexp:				IF LEFT_OPEN_BRACKET exp RIGHT_OPEN_BRACKET   		 
													{
														$$ = new vector<int>;
														if($3->eletype==ERRORTYPE)
														{
															error("Wrong type in IF statement");
														}
														else
														{
															(*$$).clear();
															quadruple q;
															variable *operand1;
															operand1 = new variable;
															if($3->eletype != INT)
															{
																conv_int_quad($3,operand1);
															}
															else
															{
																*operand1 = *$3;
															}
															(*$$).push_back(nextquad);
															q.s1 = "if";
															q.oprnd_1 = operand1->name;
															q.s2 = "<=";
															q.oprnd_2 = "0";
															q.s3 = "goto";
															q.oprnd_3 = "__";
															q.s4 = "";
															gen(q);
														}
													}
				;

whileexp:			WHILE m_inter LEFT_OPEN_BRACKET exp	RIGHT_OPEN_BRACKET
													{
														if($4->eletype==ERRORTYPE)
															error("Wrong type in WHILE statement");
														else
														{
															$$ = new while_struct;
															quadruple q;
															variable *operand1;
															operand1 = new variable;
															if($4->eletype != INT)
															{
																conv_int_quad($4,operand1);
															}
															else
															{
																*operand1 = *$4;
															}
															($$->falselist).push_back(nextquad);
															q.s1 = "if";
															q.oprnd_1 = operand1->name;
															q.s2 = "<=";
															q.oprnd_2 = "0";
															q.s3 = "goto";
															q.oprnd_3 = "__";
															q.s4 = "";
															gen(q);
															$$->begin = $2;
														}
													}
				;

asg:				lhs EQUALS exp				
													{
														if(($1->place)->eletype!=ERRORTYPE && $3->eletype!=ERRORTYPE)
														{	
															if(!coercible(($1->place)->eletype , $3->eletype))
																error("TYPE MISMATCH");
															else if(($1->place)->type==1 || $3->type==1)
																error("Array assignment not allowed");
															else
															{
																if($1->place->eletype != $3->eletype)
																{
																	variable *operand1;
																	operand1  =new variable;
																	if($1->place->eletype == INT)
																		conv_int_quad($3,operand1);
																	else if($1->place->eletype == REAL)
																		conv_float_quad($3,operand1);
																	else if($1->place->eletype == CHA)
																		conv_bool_quad($3,operand1);																	
																}
																if((*($1->place->dimlist)).size() == 0)
																{
																	quadruple q;
																	q.s1 = "";
																	q.oprnd_1 = $1->place->name;
																	q.s2 = "=";
																	q.oprnd_2 = $3->name;
																	q.s3 = q.oprnd_3 = q.s4 = "";
																	gen(q);
																}
																else
																{
																	quadruple q;
																	q.s1 = "";
																	q.oprnd_1 = ($1->place)->name;
																	q.s2 = "[";
																	q.oprnd_2 = ($1->offset)->name;
																	q.s3 = "] = ";
																	q.oprnd_3 = $3->name;
																	q.s4 = "";
																	gen(q);
																}
															}
														}
														else 
														{
															//
														}
													}
				;

lhs:				IDENTIFIER 
													{
														$$ = new lhs;
														$$->offset = NULL;
														$$->place = new variable;
														search_var(*$1, active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*$1, active_func_ptr, found, pn);
															if(!found)
															{
																($$->place)->eletype = ERRORTYPE;
																error("Identifier " + *$1 + " not declared");
															}
															else
															{
																*($$->place) = *pn;
															}
														}
														else
														{
															*($$->place) = *vn;
														}
													}


				|	IDENTIFIER DOT IDENTIFIER
													{
														$$ = new lhs;
														$$->offset = NULL;
														$$->place = new variable;
														search_var(*($1),active_func_ptr,level,found,vn);
														if(!found)
														{
															search_param(*($1),active_func_ptr,found,pn);
															if (!found || pn->eletype!=STRUC)
															{
																($$->place)->eletype = ERRORTYPE;
																error("VARIABLE IS NOT STRUCT "+ *($1));
															}
															else
															{
																search_struct(pn->struct_name,found,strptr);
																search_struct_var(*($3),strptr,found,pn);
																if(!found)
																{
																	($$->place)->eletype = ERRORTYPE;
																	error(*$3 + " not in structure " + pn->struct_name);
																}
																else
																{
																	*($$->place) = *pn;
																	$$->place->name = *$1 + "." + *$3;
																}
															}
														}
														else if(vn->eletype!=STRUC)
														{
															($$->place)->eletype = ERRORTYPE;
															error(*($1)+" not a structure");

														}
														else
														{
															search_struct(vn->struct_name,found,strptr);
															search_struct_var(*($3),strptr,found,vn);
															if(!found)
															{
																($$->place)->eletype = ERRORTYPE;
																error(*$3 + " not in structure " + vn->struct_name);
															}
															else
															{
																*($$->place) = *vn;
																$$->place->name = *$1 + "." + *$3;
															}
														}
													}

				|	br_elist RIGHT_CLOSED_BRACKET
													{
														$$ = new lhs;
														$$->place = new variable;
														*($$->place) = *($1->place);
														$$->offset = new variable;
														($$->offset)->eletype = INT;
														($$->offset)->type = 0;
														($$->offset)->level = level;
														($$->offset)->struct_name = "";
														newtemp($$->offset);
														quadruple q;
														q.s1 = "";
														q.oprnd_1 = ($$->offset)->name;
														q.s2 = "=";
														q.oprnd_2 = ($1->offset)->name;
														q.s3 = "*";
														q.oprnd_3 = to_string(get_size(($$->place)->eletype));
														q.s4 = "";
														gen(q);
														if($$->place->eletype == ERRORTYPE)
														{}
														else if($1->offset->inside != $1->place->dimlist->size())
															error("Mismatch in dimension");
														else
															$$->place->type = 0;
														// search_var(*$1, active_func_ptr, level, found, vn);
														// if(!found)
														// {
														// 	search_param(*$1, active_func_ptr, found, pn);
														// 	if(!found)
														// 	{
														// 		$$->eletype = ERRORTYPE;
														// 		error("Identifier " + *$1 + " not declared");
														// 	}
														// 	else
														// 	{
														// 		*($$->place) = *pn;
														// 	}
														// }
														// else
														// {
														// 	*($$->place) = *vn;
														// }
														// *($$->offset) = *$2;
													}
				;

br_elist:			br_elist RIGHT_CLOSED_BRACKET LEFT_CLOSED_BRACKET exp
													{
														$$ = new lhs;
														$$->dimnum = $1->dimnum + 1;
														$$->place = new variable;
														($$->offset) = new variable;
														*($$->place) = *($1->place);
														int num_elem;
														if($$->place->eletype != ERRORTYPE)
														{
															if((*($1->place->dimlist)).size() >= $$->dimnum)
																num_elem = (*($1->place->dimlist))[$$->dimnum];
															else
															{
																error("Dimension given high.");
															}
															($$->offset)->type = 0;
															($$->offset)->eletype = INT;
															($$->offset)->struct_name = "";
															($$->offset)->level = level;
															newtemp($$->offset);
															variable *temp = new variable;
															temp->type = 0;
															temp->eletype = INT;
															temp->struct_name = "";
															temp->level = level;
															newtemp(temp);
															quadruple q;
															q.s1 = "";
															q.oprnd_1 = temp->name;
															q.s2 = "=";
															q.oprnd_2 = ($1->offset)->name;
															q.s3 = "*";
															q.oprnd_3 = to_string(num_elem);
															q.s4 = "";
															gen(q);
															q.oprnd_1 = ($$->offset)->name;
															q.oprnd_2 = temp->name;
															q.s3 = "+";
															q.oprnd_3 = $4->name;
															gen(q);
															$$->offset->inside = 1 + $1->offset->inside;
														}
													}
				|	IDENTIFIER LEFT_CLOSED_BRACKET exp
													{
														$$ = new lhs;
														$$->dimnum = 1;
														$$->place = new variable;
														$$->offset = new variable;
														search_var(*$1, active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*$1, active_func_ptr, found, pn);
															if(!found)
															{
																($$->place)->eletype = ERRORTYPE;
																error("Identifier " + *$1 + " not declared");
															}
															else
															{
																*($$->place) = *pn;
															}
														}
														else
														{
															*($$->place) = *vn;
														}
														if($$->place->eletype == ERRORTYPE)
														{
															
														}
														else if((*($$->place->dimlist)).size() > 0)
														{
															*($$->offset) = *$3;
														}
														else
														{
															error(*$1 + " can't be indexed");
														}
														$$->offset->inside = 1;
													}
				|	IDENTIFIER DOT IDENTIFIER LEFT_CLOSED_BRACKET exp
													{
														$$ = new lhs;
														$$->dimnum = 1;
														$$->place = new variable;
														$$->offset = new variable;
														search_var(*($1),active_func_ptr,level,found,vn);
														if(!found)
														{
															search_param(*($1),active_func_ptr,found,pn);
															if (!found || pn->eletype!=STRUC)
															{
																($$->place)->eletype = ERRORTYPE;
																error("VARIABLE IS NOT STRUCT "+ *($1));
															}
															else
															{
																search_struct(pn->struct_name,found,strptr);
																search_struct_var(*($3),strptr,found,pn);
																if(!found)
																{
																	($$->place)->eletype = ERRORTYPE;
																	error(*$3 + " not in structure " + pn->struct_name);
																}
																else
																{
																	*($$->place) = *pn;
																	$$->place->name = *$1 + "." + *$3;
																}
															}
														}
														else if(vn->eletype!=STRUC)
														{
															($$->place)->eletype = ERRORTYPE;
															error(*($1)+" not a structure");

														}
														else
														{
															search_struct(vn->struct_name,found,strptr);
															search_struct_var(*($3),strptr,found,vn);
															if(!found)
															{
																($$->place)->eletype = ERRORTYPE;
																error(*$3 + " not in structure " + vn->struct_name);
															}
															else
															{
																*($$->place) = *vn;
																$$->place->name = *$1 + "." + *$3;
															}
														}
														if($$->place->eletype == ERRORTYPE)
														{}
														if((*($$->place->dimlist)).size() > 0)
															*($$->offset) = *$5;
														else
														{
															error(*$3 + " can't be indexed");
														}
														$$->offset->inside = 1;
													}

/*
br_elist:			LEFT_CLOSED_BRACKET exp RIGHT_CLOSED_BRACKET				
													{
														$$ = new variable;
														if($2->eletype != INT)
														{
															$$->eletype = ERRORTYPE;
															error("Dimension not an integer.");
														}
														else
														{
															(*$$) = (*$2);
														}
													}				
				|	LEFT_CLOSED_BRACKET exp RIGHT_CLOSED_BRACKET br_elist
													{
														$$ = new variable;	
														if($2->eletype != INT || $4->type != INT)
														{
															$$->eletype = ERRORTYPE;
															error("Dimension not an integer.");
														}
														else
														{
															$$->eletype = INT;
															$$->struct_name = "";
															$$->type = 0;
															$$->level = level;
															newtemp($$);
														}
													}				
*/
				;
exp:				exp OR OR aa_exp												
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $4->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $4->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}
															else if(($1)->type==1 || $4->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);


																if($1->eletype!=BOOL)
																{
																	conv_bool_quad($1,operand1);
																}
																else
																{
																	*operand1 = *$1;	
																}

																if($4->eletype!=BOOL)
																{
																	conv_bool_quad($4,operand2);
																}
																else
																{
																	*operand2 = *$4;	
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "||";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}
				|	aa_exp															
													{
														$$ = new variable;
														*$$ = *$1;
													}
				;

aa_exp:				d_exp									
													{
														$$ = new variable;
														*$$ = *$1;
													}
				|	aa_exp AND AND d_exp 											
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $4->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $4->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $4->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);


																if($1->eletype!=BOOL)
																{
																	conv_bool_quad($1,operand1);
																}
																else
																{
																	*operand1 = *$1;	
																}

																if($4->eletype!=BOOL)
																{
																	conv_bool_quad($4,operand2);
																}
																else
																{
																	*operand2 = *$4;	
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "&&";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}							
				;			

d_exp:				pm_exp	
													{
														$$ = new variable;
														*$$ = *$1;
													}
				|	pm_exp GREATER_THAN pm_exp										
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $3->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $3->eletype) || !compatible_arithop($1->eletype, $3->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $3->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $3->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $3->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $3->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else 
																{
																	*operand1 = *$1;
																}

																if($3->eletype == INT && $1->eletype == REAL)
																{
																	conv_float_quad($3, operand2);
																}
																else if($3->eletype == CHA && $1->eletype == INT)
																{
																	conv_int_quad($3,operand2);
																}
																else if($3->eletype == CHA && $1->eletype == REAL)
																{
																	conv_float_quad($3,operand2);
																}
																else 
																{
																	*operand2 = *$3;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = ">";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}							
				|	pm_exp NOT EQUALS pm_exp										
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $4->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $4->eletype) || !compatible_arithop($1->eletype, $4->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $4->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $4->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $4->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $4->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else 
																{
																	*operand1 = *$1;
																}

																if($4->eletype == INT && $1->eletype == REAL)
																{
																	conv_float_quad($4, operand2);
																}
																else if($4->eletype == CHA && $1->eletype == INT)
																{
																	conv_int_quad($4,operand2);
																}
																else if($4->eletype == CHA && $1->eletype == REAL)
																{
																	conv_float_quad($4,operand2);
																}
																else 
																{
																	*operand2 = *$4;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "!=";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}		
				|	pm_exp EQUALS EQUALS pm_exp	
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $4->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $4->eletype) || !compatible_arithop($1->eletype, $4->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $4->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $4->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $4->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $4->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $4->eletype)
																{
																	*operand1 = *$1;
																}

																if($4->eletype == INT && $1->eletype == REAL)
																{
																	conv_float_quad($4, operand2);
																}
																else if($4->eletype == CHA && $1->eletype == INT)
																{
																	conv_int_quad($4,operand2);
																}
																else if($4->eletype == CHA && $1->eletype == REAL)
																{
																	conv_float_quad($4,operand2);
																}
																else if($4->eletype == $1->eletype)
																{
																	*operand2 = *$4;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "==";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}		
				|	pm_exp LESS_THAN pm_exp											
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $3->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $3->eletype) || !compatible_arithop($1->eletype, $3->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $3->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $3->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $3->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $3->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else
																{
																	*operand1 = *$1;
																}

																if($3->eletype == INT && $1->eletype == REAL)
																{
																	conv_float_quad($3, operand2);
																}
																else if($3->eletype == CHA && $1->eletype == INT)
																{
																	conv_int_quad($3,operand2);
																}
																else if($3->eletype == CHA && $1->eletype == REAL)
																{
																	conv_float_quad($3,operand2);
																}
																else
																{
																	*operand2 = *$3;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "<";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}
				|	pm_exp LESS_THAN EQUALS pm_exp									
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $4->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $4->eletype) || !compatible_arithop($1->eletype, $4->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $4->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $4->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $4->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $4->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $4->eletype)
																{
																	*operand1 = *$1;
																}

																if($4->eletype == INT && $1->eletype == REAL)
																{
																	conv_float_quad($4, operand2);
																}
																else if($4->eletype == CHA && $1->eletype == INT)
																{
																	conv_int_quad($4,operand2);
																}
																else if($4->eletype == CHA && $1->eletype == REAL)
																{
																	conv_float_quad($4,operand2);
																}
																else if($4->eletype == $1->eletype)
																{
																	*operand2 = *$4;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "<=";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}			
				|	pm_exp GREATER_THAN EQUALS pm_exp
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $4->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $4->eletype) || !compatible_arithop($1->eletype, $4->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $4->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = BOOL;
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $4->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $4->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $4->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $4->eletype)
																{
																	*operand1 = *$1;
																}

																if($4->eletype == INT && $1->eletype == REAL)
																{
																	conv_float_quad($4, operand2);
																}
																else if($4->eletype == CHA && $1->eletype == INT)
																{
																	conv_int_quad($4,operand2);
																}
																else if($4->eletype == CHA && $1->eletype == REAL)
																{
																	conv_float_quad($4,operand2);
																}
																else if($4->eletype == $1->eletype)
																{
																	*operand2 = *$4;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = ">=";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}	
				|	NOT LEFT_OPEN_BRACKET exp RIGHT_OPEN_BRACKET					
													{
														$$ = new variable;
														*$$ = *$3;
														$$->type = ($3->eletype == ERRORTYPE) ? ERRORTYPE : BOOL;
														newtemp($$);
														if($$->type != ERRORTYPE)
														{
															quadruple q;
															q.s1 = "";
															q.oprnd_1 = $$->name;
															q.s2 = "= !";
															q.oprnd_2 = $3->name;
															q.s3 = "";
															q.oprnd_3 = "";
															q.s4 = "";
															gen(q);
														}
													}					
				;

pm_exp:				pm_exp PLUS t_exp
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $3->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $3->eletype) || !compatible_arithop($1->eletype, $3->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $3->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = compare_types($1->eletype, $3->eletype);
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $$->eletype)
																{
																	*operand1 = *$1;
																}

																if($3->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($3, operand2);
																}
																else if($3->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($3,operand2);
																}
																else if($3->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($3,operand2);
																}
																else if($3->eletype == $$->eletype)
																{
																	*operand2 = *$3;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "+";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}
				|	pm_exp MINUS t_exp		
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $3->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $3->eletype) || !compatible_arithop($1->eletype, $3->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $3->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = compare_types($1->eletype, $3->eletype);
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $$->eletype)
																{
																	*operand1 = *$1;
																}

																if($3->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($3, operand2);
																}
																else if($3->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($3,operand2);
																}
																else if($3->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($3,operand2);
																}
																else if($3->eletype == $$->eletype)
																{
																	*operand2 = *$3;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "-";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}													
				|	t_exp					
													{
														$$ = new variable;
														*$$ = *$1;
													}
				;

t_exp:				f_exp STAR t_exp												
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $3->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $3->eletype) || !compatible_arithop($1->eletype, $3->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $3->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = compare_types($1->eletype, $3->eletype);
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $$->eletype)
																{
																	*operand1 = *$1;
																}

																if($3->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($3, operand2);
																}
																else if($3->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($3,operand2);
																}
																else if($3->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($3,operand2);
																}
																else if($3->eletype == $$->eletype)
																{
																	*operand2 = *$3;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "*";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}
				|	f_exp SLASH t_exp		
													{
														$$ = new variable;
														variable *operand1, *operand2;
														operand1 = new variable;
														operand2 = new variable;
														if($1->eletype != ERRORTYPE && $3->eletype != ERRORTYPE)
														{
															if(!coercible($1->eletype, $3->eletype) || !compatible_arithop($1->eletype, $3->eletype))
															{
																error("Type mismatch");
																$$->eletype = ERRORTYPE;
															}

															else if(($1)->type==1 || $3->type==1)
																error("Array not allowed");
															else
															{
																$$->eletype = compare_types($1->eletype, $3->eletype);
																$$->type = 0;
																$$->struct_name = "";
																$$->level = level;
																newtemp($$);

																if($1->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($1, operand1);
																}
																else if($1->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($1,operand1);
																}
																else if($1->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($1,operand1);
																}
																else if($1->eletype == $$->eletype)
																{
																	*operand1 = *$1;
																}

																if($3->eletype == INT && $$->eletype == REAL)
																{
																	conv_float_quad($3, operand2);
																}
																else if($3->eletype == CHA && $$->eletype == INT)
																{
																	conv_int_quad($3,operand2);
																}
																else if($3->eletype == CHA && $$->eletype == REAL)
																{
																	conv_float_quad($3,operand2);
																}
																else if($3->eletype == $$->eletype)
																{
																	*operand2 = *$3;
																}

																quadruple q;
																q.s1 = "";
																q.oprnd_1 = $$->name;
																q.s2 = "=";
																q.oprnd_2 = operand1->name;
																q.s3 = "/";
																q.oprnd_3 = operand2->name;
																q.s4 = "";
																gen(q);
															}
														}
														else
														{
															$$->eletype = ERRORTYPE;
														}
													}		
				|	f_exp															
													{
														$$ = new variable;
														*$$ = *$1;
													}						
				;

f_exp:				NUMBER_INT				
													{
														$$ = new variable;
														$$->eletype = INT;
														$$->name = to_string($1);
														$$->type = 0;
														$$->dimlist = NULL;
														$$->level = 1;
														$$->struct_name = "";
													}
				|	CHARACTER						
													{
														$$ = new variable;
														$$->eletype = CHA;
														$$->name = (*$1);
														$$->type = 0;
														$$->dimlist = NULL;
														$$->level = 1;
														$$->struct_name = "";	
													}
				|	NUMBER_FLOAT			
													{	
														$$ = new variable;
														$$->eletype = REAL;
														$$->name = to_string($1);
														$$->type = 0;
														$$->dimlist = NULL;
														$$->level = 1;
														$$->struct_name = "";
													}
				|	IDENTIFIER
													{
														$$ = new variable;
														$$->pointer = 1;
														search_var(*$1, active_func_ptr, level, found, vn);
														if(!found)
														{
															search_param(*$1, active_func_ptr, found, pn);
															if(!found)
															{
																$$->eletype = ERRORTYPE;
																error("Identifier " + *$1 + " not declared");
															}
															else
															{
																(*$$) = *pn;
															}
														}
														else
														{
															*$$ = *vn;
														}
													}
				|	IDENTIFIER DOT IDENTIFIER
													{
														$$ = new variable;
														search_var(*($1),active_func_ptr,level,found,vn);
														if(!found)
														{
															search_param(*($1),active_func_ptr,found,pn);
															if (!found || pn->eletype!=STRUC)
															{
																($$)->eletype = ERRORTYPE;
																error("VARIABLE IS NOT STRUCT "+ *($1));
															}
															else
															{
																search_struct(pn->struct_name,found,strptr);
																search_struct_var(*($3),strptr,found,pn);
																if(!found)
																{
																	($$)->eletype = ERRORTYPE;
																	error(*$3 + " not in structure " + pn->struct_name);
																}
																else
																{
																	*($$) = *pn;
																	$$->name = *$1 + "." + *$3;
																}
															}
														}
														else if(vn->eletype!=STRUC)
														{
															($$)->eletype = ERRORTYPE;
															error(*($1)+" not a structure");

														}
														else
														{
															search_struct(vn->struct_name,found,strptr);
															search_struct_var(*($3),strptr,found,vn);
															if(!found)
															{
																($$)->eletype = ERRORTYPE;
																error(*$3 + " not in structure " + vn->struct_name);
															}
															else
															{
																*($$) = *vn;
																$$->name = *$1 + "." + *$3;
															}
														}
													}
				|	br_elist RIGHT_CLOSED_BRACKET
													{

														$$ = new variable;
														$$->eletype = $1->place->eletype;
														$$->type = $1->place->type;
														// search_var($1->place->name, active_func_ptr, level, found, vn);
														// if(!found)
														// {
														// 	search_param($1->place->name, active_func_ptr, found, pn);
														// 	if(!found)
														// 	{
														// 		$$->eletype = ERRORTYPE;
														// 		error("Identifier " + $1->place->name + " not declared");
														// 	}
														// 	else
														// 	{
														// 		$$->eletype = pn->eletype;
														// 		$$->type = pn->type;
														// 	}
														// }
														// else
														// {
														// 	$$->type = vn->type;
														// 	$$->eletype = vn->eletype;
														// }

														if($$->eletype != ERRORTYPE)
														{
															$$->type = 0;
															$$->level = level;
															$$->struct_name = "";
															variable *temp = new variable;
															temp->type = 0;
															temp->eletype = INT;
															temp->struct_name = "";
															temp->level = level;
															newtemp(temp);
															quadruple q;
															q.s1 = "";
															q.oprnd_1 = temp->name;
															q.s2 = "=";
															q.oprnd_2 = $1->offset->name;
															q.s3 = "*";
															q.oprnd_3 = to_string(get_size($$->eletype));
															q.s4 = "";
															gen(q);
															newtemp($$);
															q.s1 = "";
															q.oprnd_1 = $$->name;
															q.s2 = "=";
															q.oprnd_2 = $1->place->name;
															q.s3 = "[";
															q.oprnd_3 = temp->name;
															q.s4 = "]";
															gen(q);
														}
														if($1->offset->inside != $1->place->dimlist->size())
															error("Mismatch in dimension");
														else
															$$->type = 0;
													}
				|	func_call
													{//pointers to be handled
														$$ = new variable;
														*$$ = *$1;
													}
				|	LEFT_OPEN_BRACKET exp RIGHT_OPEN_BRACKET				
													{//pointers
														$$ = new variable;
														*$$ = *$2;
													}	
				;

func_call_head:	IDENTIFIER
													{
														search_func(*$1, found, fnptr);
														if(!found)
														{
															call_func_ptr = -1;
														}
														else
														{
															call_func_ptr = fnptr;
														}
													}

func_call:			func_call_head LEFT_OPEN_BRACKET paramlist RIGHT_OPEN_BRACKET
													{
														$$ = new variable;
														$$->type = 0;
														if(call_func_ptr == -1)
														{
															$$->eletype = ERRORTYPE;
															error("Function not declared");
															call_func_ptr = -1;
														}
														else
														{
															$$->eletype = global_func[call_func_ptr].res_type;
															$$->type = 0;
															if($$->eletype == STRUC)
															{
																$$->struct_name = global_func[call_func_ptr].struct_name;
															}
															else
															{
																$$->struct_name = "";
															}
															if(global_func[call_func_ptr].num_param != ($3))
															{
																error("Mismatch in number of parameters");
															}
															else
															{
																newtemp($$);
																quadruple q;
																if($$->eletype != VOI)
																{
																	q.s1 = "refparam";
																	q.oprnd_1 = $$->name;
																	q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
																	gen(q);
																	q.s1 = "call";
																	q.oprnd_1 = global_func[call_func_ptr].name;
																	q.s2 = "";
																	q.oprnd_2 = to_string($3 + 1);
																	q.s3 = q.oprnd_3 = q.s4 = "";
																	gen(q);
																}
																else
																{
																	q.s1 = "call";
																	q.oprnd_1 = global_func[call_func_ptr].name;
																	q.s2 = "";
																	q.oprnd_2 = to_string($3);
																	q.s3 = q.oprnd_3 = q.s4 = "";
																	gen(q);
																}
															}
														}
													}
				;

paramlist:			plist
													{
														$$ = $1;
													}
				|				
													{
														$$ = 0;
													}
				;

plist:				exp COMMA plist
													{
														$$ = $3 + 1;
														check_param_type(call_func_ptr, $$, $1, ok);
														if(!ok)
														{
															error("Parameter type mismatch");
														}
														else
														{
															quadruple q;
															if(global_func[call_func_ptr].param_list[global_func[call_func_ptr].param_list.size() - $$].type == 0)
																q.s1 = "param";
															else
																q.s1 = "refparam";
															q.oprnd_1 = $1->name;
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
														}
													}
				|	exp
													{
														$$ = 1;
														check_param_type(call_func_ptr, 1, $1, ok);
														if(!ok)
														{
															error("Parameter type mismatch");
														}
														else
														{
															quadruple q;
															if(global_func[call_func_ptr].param_list[global_func[call_func_ptr].param_list.size() - $$].type == 0)
																q.s1 = "param";
															else
																q.s1 = "refparam";
															q.oprnd_1 = $1->name;
															q.s2 = q.oprnd_2 = q.s3 = q.oprnd_3 = q.s4 = "";
															gen(q);
														}
													}
				;



%%

void yyerror(string s)
{
	cout<<"ERROR: " + s<<endl;
}
int main()
{
	return yyparse();
}

void conv_float_quad(variable *a,variable *operand1)
{
	operand1->eletype = REAL;
	operand1->type = 0;
	operand1->level = level;
	operand1->struct_name = "";
	newtemp(operand1);
	quadruple q;
	q.s1 = "";
	q.oprnd_1 = operand1->name;
	q.s2 = "= cnvrt_float(";
	q.oprnd_2 = a->name;
	q.s3 = ")";
	q.oprnd_3 = q.s4 = "";
	gen(q);
}

void conv_int_quad(variable *a,variable *operand1)
{
	operand1->eletype = INT;
	operand1->type = 0;
	operand1->level = level;
	operand1->struct_name = "";
	newtemp(operand1);
	quadruple q;
	q.s1 = "";
	q.oprnd_1 = operand1->name;
	q.s2 = "= cnvrt_int(";
	q.oprnd_2 = a->name;
	q.s3 = ")";
	q.oprnd_3 = q.s4 = "";
	gen(q);
}

void conv_bool_quad(variable *a,variable *operand1)
{
	operand1->eletype = BOOL;
	operand1->type = 0;
	operand1->level = level;
	operand1->struct_name = "";
	newtemp(operand1);
	quadruple q;
	q.s1 = "";
	q.oprnd_1 = operand1->name;
	q.s2 = "= cnvrt_bool(";
	q.oprnd_2 = a->name;
	q.s3 = ")";
	q.oprnd_3 = q.s4 = "";
	gen(q);
}

bool coercible(enum t type_1, enum t type_2)
{
	if((type_1==INT || type_1 == CHA || type_1 == REAL || type_1 == BOOL) &&
		(type_2==INT || type_2 == CHA || type_2 == REAL || type_2 == BOOL))
		return true;
	return false;
}

bool compatible_arithop(enum t type_1, enum t type_2)
{
	if((type_1==INT || type_1 == CHA || type_1 == REAL) &&
		(type_2==INT || type_2 == CHA || type_2 == REAL))
		return true;
	return false;
}

void patchtype(enum t type,vector <variable*> &namelist,string name)
{
	for(int i=0;i<namelist.size();i++)
	{
		namelist[i]->eletype = type;
		if(type==STRUC)
		{
			namelist[i]->struct_name = name;
		}
	}
}
void error (string err)
{
	cout<<"Line no: " << line_no << "--> " << err<< endl;
	error_flag = 1;
}

enum t not_compatible(enum t type)
{
	if(type == ERRORTYPE || type == REAL)
		return ERRORTYPE;
	else
		return type;
}

enum t compare_types(enum t type1,enum t type2)
{
	if(type1 == REAL || type2 == REAL)
		return REAL;
	else if(type1 == INT || type2 == INT)
		return INT;
	else if(type1 == CHA || type2 == CHA)
		return CHA;
}

void search_func(string name, bool &found, int &namptr)
{
	found = false;
	namptr = -1;
	for(int i = 0; i < global_func.size(); i++)
	{
		if(global_func[i].name == name)
		{
			found = true;
			namptr = i;
			return;
		}
	}
}

void enter_func(string name, enum t type, int &namptr, string struct_name)
{
	func_name_table temp;
	temp.name = name;
	temp.res_type = type;
	temp.num_param = 0;
	temp.param_list.clear();
	temp.var_list.clear();
	temp.struct_name = struct_name;
	global_func.push_back(temp);
	namptr = global_func.size() - 1;
}

bool compare(variable &a, variable &b)
{
	if(a.level < b.level)
		return true;
	return false;
}

void search_var(string name, int active_func_ptr, int level, bool &found, variable* &vn)
{
	found = false;
	vn = NULL;
	int cur_level = -1;
	// sort(global_func[active_func_ptr].var_list.begin(), global_func[active_func_ptr].var_list.end(), compare);
	for(int i = global_func[active_func_ptr].var_list.size() - 1; i >= 0; i--)
	{
		if(level < global_func[active_func_ptr].var_list[i].level)
		{
			continue;
		}
		if(global_func[active_func_ptr].var_list[i].name == name)
		{
			if(cur_level < global_func[active_func_ptr].var_list[i].level)
			{
				cur_level = global_func[active_func_ptr].var_list[i].level;
				vn = &global_func[active_func_ptr].var_list[i];
				found = true;
			}
		}
	}
}

void enter_var(string name, bool type, int level, int active_func_ptr, variable* &namptr, vector<int> dimlist, int pointer)
{
	variable temp;
	temp.name = name;
	temp.level = level;
	temp.type = type;
	temp.pointer = pointer;
	temp.dimlist = new vector<int>;
	*temp.dimlist = dimlist;
	global_func[active_func_ptr].var_list.push_back(temp);
	namptr = &global_func[active_func_ptr].var_list[global_func[active_func_ptr].var_list.size() - 1];
}

void search_param(string name, int active_func_ptr, bool &found, variable* &pn)
{
	found = false;
	namptr = -1;
	for(int i = 0; i < global_func[active_func_ptr].param_list.size(); i++)
	{
		if(global_func[active_func_ptr].param_list[i].name == name)
		{
			found = true;
			pn = &global_func[active_func_ptr].param_list[i];
			return;
		}
	}
}

void delete_var_list(int active_func_ptr, int level)
{
	if(error_flag == 0)
	{
		cout << endl;
		cout << "Function name: " << global_func[active_func_ptr].name << " " << "Level = " << level << endl;
		cout << "Name" << "\t" << "Type" << "\t" << "Variable/Array" << "\t" << "Struct_name" << endl;
	}
	for(int i = 0; i < global_func[active_func_ptr].var_list.size(); i++)
	{
		if(global_func[active_func_ptr].var_list[i].level == level)
		{
			if(error_flag == 0)
			{
				cout << global_func[active_func_ptr].var_list[i].name << "\t";
				cout << global_func[active_func_ptr].var_list[i].eletype << "\t";
				cout << global_func[active_func_ptr].var_list[i].type << "\t";
				if(global_func[active_func_ptr].var_list[i].eletype == STRUC)
					cout << global_func[active_func_ptr].var_list[i].struct_name;
				cout << endl;
			
				
			}
			global_func[active_func_ptr].var_list.erase(global_func[active_func_ptr].var_list.begin() + i);
		}
	}
}

void delete_param_list(int active_func_ptr, int level)
{
	cout << endl;
	cout << "Function name: " << global_func[active_func_ptr].name << " " << "Level = " << level << endl;
	cout << "Name" << "\t" << "Type" << "\t" << "Variable/Array" << "\t" << "Struct_name" << endl;
	for(int i = 0; i < global_func[active_func_ptr].param_list.size(); i++)
	{
		if(global_func[active_func_ptr].param_list[i].level == level)
		{
			cout << global_func[active_func_ptr].param_list[i].name << "\t";
			cout << global_func[active_func_ptr].param_list[i].eletype << "\t";
			cout << global_func[active_func_ptr].param_list[i].type << "\t";
			if(global_func[active_func_ptr].param_list[i].eletype == STRUC)
				cout << global_func[active_func_ptr].param_list[i].struct_name;
			cout << endl;
			global_func[active_func_ptr].param_list.erase(global_func[active_func_ptr].param_list.begin() + i);
		}
	}
}

void enter_param(string name, bool type, enum t type2, int active_func_ptr, string struct_name, int pointer, vector<int> dimlist)
{
	variable temp;
	temp.name = name;
	temp.type = type;
	temp.eletype = type2;
	temp.struct_name = struct_name;
	temp.pointer = pointer;
	temp.dimlist = new vector<int>;
	*temp.dimlist = dimlist;
	global_func[active_func_ptr].param_list.push_back(temp);
	global_func[active_func_ptr].num_param =  global_func[active_func_ptr].num_param + 1;
}

enum t get_result_type(int fnptr)
{
	return global_func[fnptr].res_type;
}

void check_param_type(int call_func_ptr, int param_no, variable* var, bool &ok)
{
	// param_no = param_no - 1;
	int size = global_func[call_func_ptr].param_list.size();
	if((global_func[call_func_ptr].param_list[size - param_no].eletype != var->eletype) || (global_func[call_func_ptr].param_list[size - param_no].type != var->type))
	{
		ok = false;
		return;
	}
	if(var->eletype != STRUC)
	{
		ok = true;
		return;
	}
	if(global_func[call_func_ptr].param_list[size - param_no].struct_name == var->struct_name)
	{
		ok = true;
	}
	else
	{
		ok = false;
	}
}

enum t get_variable_type(string name, int active_func_ptr, int level)
{
	int cur_level = -1;
	enum t type = ERRORTYPE;
	// sort(global_func[active_func_ptr].var_list.begin(), global_func[active_func_ptr].var_list.end(), compare);
	for(int i = global_func[active_func_ptr].var_list.size(); i >= 0; i--)
	{
		if(global_func[active_func_ptr].var_list[i].level > level)
		{
			continue;
		}
		if(global_func[active_func_ptr].var_list[i].name == name)
		{
			if(cur_level < global_func[active_func_ptr].var_list[i].level)
			{
				cur_level = global_func[active_func_ptr].var_list[i].level;
				type = global_func[active_func_ptr].var_list[i].eletype;
			}
		}
	}
	return type;
}
void search_struct(string name,bool &found, int &strptr)
{
	found = false;
	strptr = -1;
	for (int i=0;i<global_struct.size();i++)
	{
		if (global_struct[i].name==name)
		{
			found = true;
			strptr = i;
			return;
		}
	}
}
void enter_struct(string name ,int &strptr)
{
	struct_name_table temp;
	temp.name = name;
	temp.var_list.clear();
	global_struct.push_back(temp);
	strptr = global_struct.size()-1;
}
void search_struct_var(string name, int active_struct_ptr , bool &found, variable* &vn)
{
	found = false;
	vn = NULL;
	for(int i=0;i<global_struct[active_struct_ptr].var_list.size();i++)
	{
		if (global_struct[active_struct_ptr].var_list[i].name == name)
		{
			found = true;
			vn = &global_struct[active_struct_ptr].var_list[i];
			return;
		}
	}
}
void enter_struct_var(string name, bool type, int active_struct_ptr, variable * &vnptr, vector<int> dimlist, int pointer)
{
	variable temp;
	temp.name = name;
	temp.pointer = pointer;
	temp.type = type;
	temp.dimlist = new vector<int>;
	*temp.dimlist = dimlist;
	global_struct[active_struct_ptr].var_list.push_back(temp);
	vnptr = &global_struct[active_struct_ptr].var_list[global_struct[active_struct_ptr].var_list.size()-1];
}

void backpatch(vector<int> list, int quad_number)
{
	for(int i=0;i<list.size();i++)
	{
		if(quad_table[list[i]].oprnd_1=="__")
			quad_table[list[i]].oprnd_1 = "L" + to_string(quad_number);
		if(quad_table[list[i]].oprnd_2=="__")
			quad_table[list[i]].oprnd_2 = "L" + to_string(quad_number);
		if(quad_table[list[i]].oprnd_3=="__")
			quad_table[list[i]].oprnd_3 = "L" + to_string(quad_number);
	}
}

void gen(quadruple quad)
{
	quad_table.push_back(quad);
	nextquad++;
}

void newtemp(variable *var)
{
	var->name = "t" + to_string(temp_var++);
	global_func[active_func_ptr].var_list.push_back(*var);
}

int get_size(enum t type)
{
	if(type==INT)
		return 4;
	else if(type==REAL)
		return 8;
	else if(type==CHA)
		return 1;
	return 1;
}