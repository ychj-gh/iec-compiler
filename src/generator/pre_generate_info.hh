#ifndef PRE_GENERATE_INFO_HH__
#define PRE_GENERATE_INFO_HH__

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include <deque>

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


class cond_statement_cnt_c {
public:
	bool push_not_first_time_flag;

	std::deque<unsigned int> jmp_times;

	unsigned int if_insert_times;
	unsigned int if_find_times;
	cond_statement_cnt_c *inner_scope;
	

public:
	cond_statement_cnt_c(void)  {
		if_insert_times = 0;
		if_find_times = 0;
		inner_scope = NULL;
		push_not_first_time_flag = false;
	}
	~cond_statement_cnt_c(void) {
		clear();
	}

public:
	void push(void) {
		if(push_not_first_time_flag == true) {
			if(inner_scope != NULL) {
				inner_scope->push();
			} else {
				inner_scope = new cond_statement_cnt_c();
			}
		} else {
			push_not_first_time_flag = true;
		}
	}
	int pop(void) {
		if(inner_scope != NULL) {
			if(inner_scope->pop() == 1) {
				delete inner_scope;
				inner_scope = NULL;
			} 
			return 0;
		} else {
			jmp_times.clear();
			if_insert_times = 0;
			if_find_times = 0;
			return 1;
		}
	}
	void clear(void) {
		if(inner_scope != NULL) {
			inner_scope->clear();
			delete inner_scope;
		}
		jmp_times.clear();
		if_insert_times = 0;
		if_find_times = 0;
	}
	void inc_jmp_times(void) {
		auto beg = jmp_times.begin();
		auto end = jmp_times.end();
		while(beg != end) {
			*beg = *beg + 1;
			beg++;
		}
		if(inner_scope != NULL) {
			inner_scope->inc_jmp_times();
		} else {
			jmp_times.push_front(1);
		}
	}
	void print_jmp_times(void) {
		std::cout << "====LAYER====" << std::endl;
		for(auto elem : jmp_times)
			std::cout << elem << ", " ;
		std::cout << std::endl;
		if(inner_scope != NULL) {
			inner_scope->print_jmp_times();
		}
	}
	
	unsigned int get_jmp_times_first_elem(void) {
		if(inner_scope != NULL) {
			inner_scope->get_jmp_times_first_elem();
		} else {
			return jmp_times.front();
		}
	}
	unsigned int pop_jmp_times_first_elem(void) {
		if(inner_scope != NULL) {
			inner_scope->pop_jmp_times_first_elem();
		} else {
			jmp_times.pop_front();
		}
	}

	void inc_if_insert_times(void) {
		if_insert_times++;
		if(inner_scope != NULL) {
			inner_scope->inc_if_insert_times();
		} 
	}
	void inc_if_find_times(void) {
		if_find_times++;
		if(inner_scope != NULL) {
			inner_scope->inc_if_find_times();
		} 
	}
	unsigned int get_if_insert_times(void) {
		if(inner_scope != NULL) {
			return inner_scope->get_if_insert_times();
		} else {
			return if_insert_times;
		}
	}
	unsigned int get_if_find_times(void) {
		if(inner_scope != NULL) {
			return inner_scope->get_if_find_times();
		} else {
			return if_find_times;
		}
	}
	void set_if_insert_times(unsigned int n) {
		if(inner_scope != NULL) {
			inner_scope->set_if_insert_times(n) ;
		} else {
			if_insert_times = n;
		}
	}
	void set_if_find_times(unsigned int n) {
		if(inner_scope != NULL) {
			inner_scope->set_if_find_times(n);
		} else {
			if_find_times = n;
		}
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
	std::string pre_code;


	cond_statement_cnt_c jmp_cnt;
	cond_statement_cnt_c if_cnt;

	std::vector<IValue> input_variable;
	std::vector<IValue> input_output_variable;
	std::vector<IValue> output_variable;
	std::vector<IValue> local_variable;
	std::vector<IValue> constant_value;
	std::vector<std::string> inst_code;



public:
	internal_value_t variable_type_check(std::string type);
	int find_var_return_num(std::string var_name);

	//just for debug
	void print(void);
	void print_detail_info(void);
};



class pre_generate_info_c {
private:
	std::map<std::string, pre_generate_pou_info_c *> pre_generate_info_collector;

public:
	pre_generate_info_c();

	virtual ~pre_generate_info_c(){}

	bool insert(std::string pou_name, pre_generate_pou_info_c *info);
public:
	unsigned int count;

};

#endif