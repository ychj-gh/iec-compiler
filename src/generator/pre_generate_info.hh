#ifndef PRE_GENERATE_INFO_HH__
#define PRE_GENERATE_INFO_HH__

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

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

class pre_generate_pou_info_c {
private:
	std::string pou_name;

	inst_number_t pou_inst_number;

public:
	pre_generate_pou_info_c(std::string pou_name) {
		this->pou_name = pou_name; 
		pre_code = "";
	}
	virtual ~pre_generate_pou_info_c(){}
    
    void set_pou_name(std::string pou_name) { this->pou_name = pou_name; }
    std::string get_pou_name(void) const { return this->pou_name; }
public:
	std::string pre_code;

	std::vector<IValue> input_variable;
	std::vector<IValue> input_output_variable;
	std::vector<IValue> output_variable;
	std::vector<IValue> local_variable;
	std::vector<std::string> inst_code;

public:
	internal_value_t variable_type_check(std::string type);

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