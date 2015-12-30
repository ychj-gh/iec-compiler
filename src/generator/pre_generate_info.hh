#ifndef PRE_GENERATE_INFO_HH__
#define PRE_GENERATE_INFO_HH__

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include <deque>
#include <list>

#include "utility_condition_statement_cnt.hh"

typedef unsigned int varible_number_t;
typedef unsigned int inst_number_t;


typedef unsigned char internal_value_t;
/* Internal Value Type Tag */
#define TUNDEF  0
#define TINT    1
#define TUINT   2
#define TDOUBLE 3
#define TSTRING 4


typedef signed long  IInt;
typedef unsigned long IUInt;
typedef double   IDouble;
typedef struct {
    unsigned int length; /* '\0' included */
    char *str;
} IString;

/* Internal Value for Register | Constant | Global */
class IValue {
public:
	std::string name;
    char type;
    union {
        IInt value_i;
        IUInt value_u;
        IDouble value_d;
        IString value_s;
        //uint16_t value_p; [> reference or pointer value <]
    } v;
public:
	IValue(){
		name = "";
		type = TUNDEF;
		v.value_i = 0;
	}
	//just for debug
	void print(void) {
		std::cout << "IValue name: " << name 
			<< " type: " 
			<< (type == TINT ? "TINT " : (type == TUINT ? "TUINT" : (type == TDOUBLE ? "TDOUBLE" : "TSTRING"))) 
			<< " value: ";
		if (type == TINT)
			std::cout << v.value_i << std::endl;
		else if (type == TUINT)
			std::cout << v.value_u << std::endl;
		else if (type == TDOUBLE)
			std::cout << v.value_d << std::endl;
		else
			std::cout << v.value_s.str << std::endl;
	}

};


//pou status :
#define POU_STA_INIT 0
#define POU_STA_HEADER 1
#define POU_STA_VAR_DEC 2
#define POU_STA_VAR_IN_DEC 3
#define POU_STA_VAR_OUT_DEC 4
#define POU_STA_VAR_INOUT_DEC 5
#define POU_STA_VAR_LOCAL_DEC 6
#define POU_STA_BODY 7

//pou type
#define POU_TYPE_UNDEF 0
#define POU_TYPE_FUN 1
#define POU_TYPE_FB 2
#define POU_TYPE_PROG 3


class pre_generate_pou_info_c {
private:
	std::string pou_name;
	unsigned int pou_status;
	unsigned int pou_type;

	unsigned int pou_reg_num;

	inst_number_t pou_inst_number;

public:
	pre_generate_pou_info_c(std::string pou_name) {
		this->pou_name = pou_name; 
		pre_code = "";
		pou_status = POU_STA_INIT;
		pou_reg_num = 0;
	}
	virtual ~pre_generate_pou_info_c(){}
    
    void set_pou_name(std::string pou_name) { this->pou_name = pou_name; }
    std::string get_pou_name(void) const { return this->pou_name; }

    void set_pou_status(unsigned int status) { this->pou_status = status; }
    unsigned int get_pou_status(void) const { return this->pou_status; }

    void set_pou_type(unsigned int type) { pou_type = type; }
    unsigned int get_pou_type(void) const { return this->pou_type; }

    std::string get_pou_reg_num() const { 
    	std::stringstream strm;
    	std::string result;
    	strm << (this->pou_reg_num + input_variable.size() + input_output_variable.size() + output_variable.size() + local_variable.size() );
    	strm >> result;
    	return result;
    }
    void inc_pou_reg_num() { this->pou_reg_num ++; }
    void dec_pou_reg_num() { this->pou_reg_num --; }

    std::string get_pou_const_num() const {
    	std::stringstream strm;
    	std::string result;
    	strm << (this->constant_value.size() - 1) ;
    	strm >> result;
    	return result;
    }

	

public:
	std::string pre_code;  //no use
	
	cond_statement_cnt_c if_condj_cnt;
	cond_statement_cnt_c if_jmp_cnt;
	
	cond_statement_cnt_c case_condj_cnt;
	cond_statement_cnt_c case_jmp_cnt;

	cond_statement_cnt_c for_condj_cnt;
	cond_statement_cnt_c for_jmp_cnt;

	cond_statement_cnt_c while_condj_cnt;
	// cond_statement_cnt_c while_jmp_cnt;

	cond_statement_cnt_c repeat_condj_cnt;
	// cond_statement_cnt_c repeat_jmp_cnt;

	std::vector<IValue> input_variable;
	std::vector<IValue> input_output_variable;
	std::vector<IValue> output_variable;
	std::vector<IValue> local_variable;
	std::vector<IValue> constant_value;

	std::list<std::string> inst_code;



public:
	internal_value_t variable_type_check(std::string type);
	int find_var_return_num(std::string var_name);

	//just for debug
	void print(void);
	void print_detail_info(void);
};




class task_info_c
{
public:
	std::string task_name;
	unsigned int task_interval;/* unit: ms */
	unsigned int task_priority;
	std::string task_signal;
	bool task_is_signal;

public:
	task_info_c() {
		task_interval = 0;
		task_priority = 0;
		task_is_signal = false;
	}
	~task_info_c() {}
public:	

	void print(void) {
		std::cout << "task name: " << task_name << ", task interval: " << task_interval 
			<< ", task priority: " << task_priority << ", task signal: " << task_signal
			<< ", task is signal? : " << (task_is_signal ? "true":"false") << " ; " << std::endl;
	} 
};

class program_arguement_c
{
public:
	std::string key;
	std::string value;
public:
	program_arguement_c() {}
	~program_arguement_c() {}
public:
	void print() {
		std::cout << "key: " << key << ", value: " << value << std::endl;
	}
	
};

class program_info_c
{
public:
	std::string program_name;
	std::string bind_task_name;
	std::string program_instance_name;
	std::vector<program_arguement_c> assign_arguement;
	std::vector<program_arguement_c> sendto_arguement;
public:
	program_info_c()  {}
	~program_info_c() {}

public:
	void print(void) {
		std::cout << std::endl;
		std::cout << "program name: " << program_name << ", bind task name: " << bind_task_name << std::endl;
		std::cout << "program instance name: " << program_instance_name << std::endl;
		std::cout << "assign arguement number: " << assign_arguement.size() << std::endl;
		for(auto elem: assign_arguement)
			elem.print();
		std::cout << "sendto arguement number: " << sendto_arguement.size() << std::endl;
		for(auto elem: sendto_arguement)
			elem.print();
	}
	
};


class resource_info_c
{
public:
	std::string resource_name;
	std::string resource_typename;
	std::vector<IValue> resource_global_var_set;
	std::vector<task_info_c> task_list_set;
	std::vector<program_info_c> program_list_set;
public:
	resource_info_c() {}
	resource_info_c(std::string name) : resource_name(name) {}
	~resource_info_c() {}

public:
	void print(void) {
		std::cout << "resource name: " << resource_name << " resource_typename : " << resource_typename << std::endl;
		std::cout << "resource global var  number: " << resource_global_var_set.size() << std::endl;
		for(auto elem : resource_global_var_set)
			elem.print();
		std::cout << std::endl;
		std::cout << "task number: " << task_list_set.size() << std::endl;
		for(auto elem : task_list_set)
			elem.print();
		std::cout << std::endl;
		std::cout << "program number: " << program_list_set.size() << std::endl;
		for(auto elem : program_list_set)
			elem.print();
	}
	
};


class configuration_info_c
{
public:
	std::string configuration_name;
	std::vector<IValue> config_global_var_set;
	std::vector<resource_info_c> res_list_set;
public:
	configuration_info_c() {}
	configuration_info_c(std::string name) : configuration_name(name) {}
	~configuration_info_c() {}
	
};


class pre_generate_info_c {
public:
	std::list<pre_generate_pou_info_c> pre_generate_info_collector;
	configuration_info_c configuration_info;

public:
	pre_generate_info_c();

	virtual ~pre_generate_info_c(){}

	bool insert(pre_generate_pou_info_c info);
public:
	unsigned int count;

	void print(void);

};


#endif