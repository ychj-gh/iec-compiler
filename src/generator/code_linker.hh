#ifndef __CODE_LINKER_HH__
#define __CODE_LINKER_HH__




#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <list>
#include "generate_iec.hh"

#include "stage4.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.

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
	void print(void) {
		std::cout << std::endl;
		std::cout << "# OBJ POU Description Segment" << std::endl;
		std::cout << "pds_name           " << user_pou_name << std::endl;

		std::cout << "pds_type:          " << pds_type << std::endl;
		std::cout << "pds_instance:      " << pds_instance << std::endl;

		std::cout << "pds_input_count    " << input_count << std::endl;
		std::cout << "pds_inout_count    " << inout_count << std::endl;
		std::cout << "pds_output_count   " << output_count << std::endl;
		std::cout << "pds_local_count    " << local_count << std::endl;
		std::cout << "pds_entry          " << code_entry << std::endl;
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
	void print(void) {
		std::cout << std::endl;
		std::cout << "# OBJ PLC Task Description Segment" << std::endl;
		std::cout << "tds_name           " << task_name << std::endl;
		std::cout << "tds_priority       " << task_priority << std::endl;
		std::cout << "tds_type           " << (task_type == 0 ? "TASK_TYPE_INTERVAL" : "TASK_TYPE_SIGNAL") << std::endl;
		std::cout << "tds_signal         " << signal_source << std::endl;
		std::cout << "tds_interval       " << task_period << std::endl;
		std::cout << "tds_sp_size        " << string_pool_count << std::endl;
		std::cout << "tds_cs_size        " << stack_count << std::endl;
		std::cout << "tds_pou_count      " << pou_count << std::endl;
		std::cout << "tds_const_count    " << const_count << std::endl;
		std::cout << "tds_global_count   " << global_count << std::endl;
		std::cout << "tds_refval_count   " << refval_count << std::endl;
		// std::cout << "tds_retain_count " << elem.retain_count << std::endl;  //not achieved
		std::cout << "tds_inst_count     " << inst_count << std::endl;
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
	void print(void) {
		task_des.print();

		for(auto elem : user_pou_list)
			elem.print();
		std::cout << std::endl;
		std::cout << "# OBJ PLC Task Constant Segment" << std::endl;
		for(auto elem : const_list) {
			std::cout << "K " << (elem.type == TINT ? "TINT":((elem.type == TUINT) ? "TUINT" : "TDOUBLE")) << std::string(" ") ;
			if (elem.type == TINT)
				std::cout << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				std::cout << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				std::cout << elem.v.value_d << std::endl;
			else
				std::cout << elem.v.value_s.str << std::endl;
		}
		std::cout << std::endl;

		std::cout << "# OBJ PLC Task Global Variables Segment" << std::endl;
		for(auto elem : global_list) {
			std::cout << "G " << elem.type << std::string(" ");
			if (elem.type == TINT)
				std::cout << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				std::cout << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				std::cout << elem.v.value_d << std::endl;
			else
				std::cout << elem.v.value_s.str << std::endl;
		}
		std::cout << std::endl;

		std::cout << "# OBJ PLC Task Reference Variables Segment" << std::endl;

		/*std::cout << "# OBJ PLC Task Retain Variables Segment" << std::endl;
		for(auto elem : retain_list) {
			std::cout << "R " << elem.type << std::string(" ");
			if (elem.type == TINT)
				std::cout << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				std::cout << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				std::cout << elem.v.value_d << std::endl;
			else
				std::cout << elem.v.value_s.str << std::endl;
		}
		std::cout << std::endl;*/

		std::cout << "# OBJ PLC Task Code Segment" << std::endl;
		for(auto elem : code_list) {
			std::cout << "I ";
			std::cout << elem << std::endl;
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
	void print(void) {
		std::cout << std::endl;
		std::cout << "# OBJ PLC Task List Segment" << std::endl;

		std::cout << "plc_task_count " << task_count << std::endl;
		std::cout << "plc_global_count " << global_count << std::endl;
		std::cout << "plc_timer_count " << timer_count << std::endl;
		std::cout << std::endl;

		for(auto elem : global_list) {
			std::cout << "PG " << (elem.type == TINT ? "TINT":((elem.type == TUINT) ? "TUINT" : "TDOUBLE")) << std::string(" ");
			if (elem.type == TINT)
				std::cout << elem.v.value_i << std::endl;
			else if (elem.type == TUINT)
				std::cout << elem.v.value_u << std::endl;
			else if (elem.type == TDOUBLE)
				std::cout << elem.v.value_d << std::endl;
			else
				std::cout << elem.v.value_s.str << std::endl;
		}
		std::cout << std::endl;

		for(auto elem : task_list)
			elem.print();


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
	void print(void) {
		obj_file.print();
	}

};












#endif
