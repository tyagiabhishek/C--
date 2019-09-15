#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

enum t {INT, REAL, VOI, CHA, STRUC,ERRORTYPE,BOOL};
struct variable
{
	string name;
	bool type; //0 for simple, 1 for array
	enum t eletype;
	vector<int> *dimlist;
	// bool var_type; //0 for parameter, 1 for variable //we think not needed
	int level, pointer;
	int inside;
	string struct_name;
};

struct res
{
	enum t type;
	string struct_name;
	vector <variable*> namelist;
	int dimnum;
};

struct func_name_table
{
	string name;
	enum t res_type;
	string struct_name;
	vector<variable> param_list;
	vector<variable> var_list;
	int num_param;
};

struct struct_name_table
{
	string name;
	vector<variable> var_list;
};

struct quadruple
{
	string s1, s2, s3, s4, oprnd_1, oprnd_2, oprnd_3;
};

struct while_struct
{
	vector<int> falselist;
	int begin;
};

struct lhs
{
	variable *place;
	variable *offset;
	int dimnum;
};

struct smt_l
{
	vector<int> *list;
	bool ret;
};