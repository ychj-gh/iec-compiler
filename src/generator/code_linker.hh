#ifndef __CODE_LINKER_HH__
#define __CODE_LINKER_HH__




#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <list>
#include <algorithm>
#include "generate_iec.hh"

#include "stage4.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.

#include "standard_function_names.h"

#include "pre_generate_info.hh"
#include "generate_assignment_r_exp.hh"
#include "generate_assignment_l_exp.hh"
#include "generate_pou_var_declaration.hh"
#include "utility_token_get.hh"
#include "utility_case_exp_value.hh"
#include "generate_pou_invocation.hh"
#include "generate_configuration.hh"




/** obj file format
+------------------------------------------------------------------------------------------+
|task_count|-------------------------------------------------------------------------------|

|---------------------------------task_name------------------------------------------------|
|task_priority|task_type|signal_source|-----|---------------task_period--------------------|
|-----------string_pool_count---------------|----stack_count----|-------pou_count----------|
|-------const_count-----|---global_count----|----retain_count---|-------inst_count---------|

|-------------------------------------user_pou_name----------------------------------------|
|------------------------------------------------------------------------------------------|
|input_count|inout_count|output_count|local_count|----------------code_entry---------------|
*/

class user_pou_c
{
public:
	std::string user_pou_name;

	short pds_type;
	short pds_instance;

	short input_count;
	short inout_count;
	short output_count;
	short local_count;

	unsigned int code_entry;

public:
	user_pou_c() {
		user_pou_name = "";

		pds_type = 0;
		pds_instance = 0;

		input_count = 0;
		inout_count = 0;
		output_count = 0;
		local_count = 0;

		code_entry = 0;
	}
	~user_pou_c() {

	}

public:
	void print(std::ostream &out = std::cout) {
		out << std::endl;
		out << "# OBJ POU Description Segment" << std::endl;
		out << "pds_name           " << user_pou_name << std::endl;

		out << "pds_type:          " << ((pds_type == 1) ? "POU_TYPE_FUN" : (pds_type == 2 ? "POU_TYPE_FB" : (pds_type == 3 ? "POU_TYPE_PROG" : "POU_TYPE_UNDEF"))) << std::endl;
		out << "pds_instance:      " << pds_instance << std::endl;

		out << "pds_input_count    " << input_count << std::endl;
		out << "pds_inout_count    " << inout_count << std::endl;
		out << "pds_output_count   " << output_count << std::endl;
		out << "pds_local_count    " << local_count << std::endl;
		out << "pds_entry          " << code_entry << std::endl;
	}

};

class task_des_c
{
public:
	std::string task_name;

	short task_priority;
	short task_type;	// 0: 表示周期性任务； 1: 表示触发性任务
	unsigned short signal_source;
	unsigned long task_period;

	unsigned int string_pool_count;
	unsigned short int stack_count;
	short int pou_count;

	short int const_count;
	short int global_count;
	short int refval_count;
	short int retain_count;
	short int inst_count;

public:
	task_des_c() {
		task_name = "";

		task_priority = 0;
		task_type = 0;
		signal_source = 0;
		task_period = 0;

		string_pool_count = 256;
		stack_count = 0;
		pou_count = 0;

		const_count = 0;
		global_count = 0;
		refval_count = 0;
		retain_count = 0;
		inst_count = 0;
	}
	~task_des_c() {}

public:
	void print(std::ostream &out = std::cout) {
		out << std::endl;
		out << "# OBJ PLC Task Description Segment" << std::endl;
		out << "tds_name           " << task_name << std::endl;
		out << "tds_priority       " << task_priority << std::endl;
		out << "tds_type           " << (task_type == 0 ? "TASK_TYPE_INTERVAL" : "TASK_TYPE_SIGNAL") << std::endl;
		out << "tds_signal         " << signal_source << std::endl;
		out << "tds_interval       " << task_period << std::endl;
		out << "tds_sp_size        " << string_pool_count << std::endl;
		out << "tds_cs_size        " << stack_count << std::endl;
		out << "tds_pou_count      " << pou_count << std::endl;
		out << "tds_const_count    " << const_count << std::endl;
		out << "tds_global_count   " << global_count << std::endl;
		out << "tds_refval_count   " << refval_count << std::endl;
		// std::cout << "tds_retain_count " << elem.retain_count << std::endl;  //not achieved
		out << "tds_inst_count     " << inst_count << std::endl;
	}

};

class obj_task_c
{
public:
	task_des_c task_des;
	std::vector<user_pou_c> user_pou_list;

	std::vector<IValue> const_list;
	std::vector<IValue> global_list;
	std::vector<IValue> retain_list;
	std::vector<IValue> refval_list;

	std::list<std::string> code_list;


public:
	obj_task_c() {

	}
	~obj_task_c() {

	}
public:
	void print(std::ostream &out = std::cout) {
		task_des.print(out);

		for(auto elem : user_pou_list)
			elem.print(out);
		out << std::endl;
		out << "# OBJ PLC Task Constant Segment" << std::endl;
		for(auto elem : const_list) {
			out << "K " << (elem.type == TINT ? "TINT":((elem.type == TUINT) ? "TUINT" : "TDOUBLE")) << std::string(" ") ;
			if (elem.type == TINT)
				out << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				out << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				out << elem.v.value_d << std::endl;
			else
				out << elem.v.value_s.str << std::endl;
		}
		out << std::endl;

		out << "# OBJ PLC Task Global Variables Segment" << std::endl;
		for(auto elem : global_list) {
			out << "G " << (elem.type == TINT ? "TINT":((elem.type == TUINT) ? "TUINT" : "TDOUBLE")) << std::string(" ") ;
			if (elem.type == TINT)
				out << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				out << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				out << elem.v.value_d << std::endl;
			else
				out << elem.v.value_s.str << std::endl;
		}
		out << std::endl;

		out << "# OBJ PLC Task Reference Variables Segment" << std::endl;
		out << std::endl;

		/*std::cout << "# OBJ PLC Task Retain Variables Segment" << std::endl;
		for(auto elem : retain_list) {
			out << "R " << elem.type << std::string(" ");
			if (elem.type == TINT)
				out << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				out << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				out << elem.v.value_d << std::endl;
			else
				out << elem.v.value_s.str << std::endl;
		}
		out << std::endl;*/

		out << "# OBJ PLC Task Code Segment" << std::endl;
		for(auto elem : code_list) {
			out << "I ";
			out << elem << std::endl;
		}
	}

};


class obj_file_c
{
public:
	unsigned int task_count;
	unsigned int global_count;
	unsigned int timer_count;

	std::vector<IValue> global_list;
	std::vector<obj_task_c> task_list;


public:
	obj_file_c() {
		task_count = 0;
		global_count = 0;
		timer_count = 0;
	}
	~obj_file_c() {}

public:
	void print(std::ostream &out = std::cout) {
		out << std::endl;
		out << "# OBJ PLC Task List Segment" << std::endl;

		out << "plc_task_count " << task_count << std::endl;
		out << "plc_global_count " << global_count << std::endl;
		out << "plc_timer_count " << timer_count << std::endl;
		out << std::endl;

		for(auto elem : global_list) {
			out << "PG " << (elem.type == TINT ? "TINT":((elem.type == TUINT) ? "TUINT" : "TDOUBLE")) << std::string(" ");
			if (elem.type == TINT)
				out << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				out << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				out << elem.v.value_d << std::endl;
			else
				out << elem.v.value_s.str << std::endl;
		}
		out << std::endl;

		for(auto elem : task_list)
			elem.print(out);


	}

};



class code_linker_c
{
public:
	pre_generate_info_c *pre_code_info;

	obj_file_c obj_file;

public:
	code_linker_c(pre_generate_info_c *pre_code_info_param) : pre_code_info(pre_code_info_param) {

	}
	~code_linker_c() {

	}

public:
	void link_code(void);

	//注意：当字符串为空时，也会返回一个空字符串
	void split(std::string& s, const std::string& delim,std::vector< std::string >* ret);

	void link_task_pou(std::list<pre_generate_pou_info_c>::iterator& pou_iterator,  obj_task_c& temp_obj_task,
						std::string pou_ret);



public:
	void print(std::ostream &out = std::cout ) {
		obj_file.print(out);
	}

};












#endif
