#include "pre_generate_info.hh"




internal_value_t pre_generate_pou_info_c::variable_type_check(std::string type)
{
	if(type == "SINT" || type == "INT" || type == "DINT" || type == "LINT")
		return TINT;
	else if(type == "USINT" || type == "UINT" || type == "UDINT" || type == "ULINT"
		|| type == "BYTE" || type == "WORD" || type == "LWORD" || type == "DWORD" || type == "BOOL")
		return TUINT;
	else if(type == "REAL" || type == "LREAL")
		return TDOUBLE;
	else if(type == "STRING" || type == "WSTRING")
		return TSTRING;
	else {		// 处理复合数据类型或未定义类型
		pre_generate_info_c &pre_code_info = *(pre_generate_info_c::getInstance());
		for(auto elem : pre_code_info.struct_type_collector){
			if(elem.struct_name == type){
				return TREF;
			}
		}

		for(auto elem : pre_code_info.array_type_collector){
			if(elem.array_name == type){
				return TREF;
			}
		}

		return TUNDEF;
	}


}

int pre_generate_pou_info_c::find_var_return_num(std::string var_name)
{
	unsigned int count = 0;
	for(auto elem : input_variable) {
		if(elem.name == var_name) {
			return count;
		}
		count ++;
	}
	for(auto elem : input_output_variable) {
		if (elem.name == var_name) {
			return count;
		}
		count ++;
	}
	for(auto elem : output_variable) {
		if (elem.name == var_name) {
			return count;
		}
		count ++;
	}
	for(auto elem : local_variable) {
		if (elem.name == var_name) {
			return count;
		}
		count ++;
	}
	count = 0;
	for(auto elem : struct_var_collector){
		std::vector<std::string> str = utility_token_get_c::split(elem.struct_name, " ");
		if (str[1] == var_name){
			return count;
		}
		count ++;
	}
	return -1;
}

void pre_generate_pou_info_c::print(void)
{
	std::cout << std::endl;
	std::cout << "++++++POU INFO START++++++" << std::endl;
	std::cout << "pou name: " << pou_name << std::endl;
	std::cout << "input number: " << input_variable.size() << std::endl;
	std::cout << "in_out number: " << input_output_variable.size() << std::endl;
	std::cout << "output number: " << output_variable.size() << std::endl;
	std::cout << "local number: " << local_variable.size() << std::endl;
	std::cout << "inst number: " << inst_code.size() << std::endl;
	std::cout << "code buffer: " << pre_code << std::endl;
	std::cout << "++++++POU INFO END++++++++" << std::endl;
}

void pre_generate_pou_info_c::print_detail_info(void)
{
	unsigned int count = 0 ;
	std::cout << std::endl;
	std::cout << "++++++POU DETAIL INFO START++++++" << std::endl;
	std::cout << "pou name: " << pou_name << ", pou type: "
			  << ((pou_type == POU_TYPE_FUN) ? "FUN" : ((pou_type == POU_TYPE_FB) ? "FB" : (pou_type == POU_TYPE_PROG ? "PROG" : "UNDEF") )) << std::endl;
	std::cout << "--------------VAR----------------" << std::endl;
	std::cout << "input number: " << input_variable.size() << std::endl;
	for(auto elem : input_variable)
		elem.print();
	std::cout << std::endl;
	std::cout << "in_out number: " << input_output_variable.size() << std::endl;
	for(auto elem : input_output_variable)
		elem.print();
	std::cout << std::endl;
	std::cout << "output number: " << output_variable.size() << std::endl;
	for(auto elem : output_variable)
		elem.print();
	std::cout << std::endl;
	std::cout << "local number: " << local_variable.size() << std::endl;
	for(auto elem : local_variable)
		elem.print();
	std::cout << std::endl;
	std::cout << "constant number: " << constant_value.size() << std::endl;
	for(auto elem : constant_value)
		elem.print();
	std::cout << std::endl;
	std::cout << "------------Code-----------------" << std::endl;
	std::cout << "inst number: " << inst_code.size() << std::endl;
	for(auto elem : inst_code)
		std::cout << ++count << " : "<< elem << std::endl;
	std::cout << std::endl;
	std::cout << "++++++POU DETAIL INFO END++++++++" << std::endl;
	std::cout << std::endl;
}




pre_generate_info_c *pre_generate_info_c::singleton = NULL;

bool pre_generate_info_c::insert(pre_generate_pou_info_c info)
{
	pre_generate_info_collector.push_back(info);
}


void pre_generate_info_c::print(void)
{
	int i = 1;
	std::cout << std::endl;
	std::cout << "|+++++++POU LIST INFO START++++++|" << std::endl;
	std::cout << "pou number: " << pre_generate_info_collector.size() << std::endl;
	std::cout << "+--------------------------------+" << std::endl;
	for(auto elem : pre_generate_info_collector) {
		std::cout << "POU No." << i++ << std::endl;
		elem.print_detail_info();
	}
	std::cout << std::endl;
	std::cout << "|++++++++POU LIST INFO END+++++++|" << std::endl;

	std::cout << std::endl;
	std::cout << "|++++CONFIGURATION INFO START++++|" << std::endl;
	std::cout << "configuration name: " << configuration_info.configuration_name << std::endl;
	std::cout << std::endl;
	std::cout << "-----CONFIGURATION GLOBAL VAR-----" << std::endl;
	std::cout << "configuration global number: " << configuration_info.config_global_var_set.size() << std::endl;
	for(auto elem : configuration_info.config_global_var_set)
		elem.print();
	std::cout << std::endl;
	std::cout << "resource number: " << configuration_info.res_list_set.size() << std::endl;
	for(auto elem : configuration_info.res_list_set)
		elem.print();
	std::cout << std::endl;
	std::cout << "|+++++CONFIGURATION INFO END+++++|" << std::endl;

	std::cout << std::endl;
	std::cout << "|++++STRUCT_TYPE INFO START++++|" << std::endl;
	for(auto elem : struct_type_collector){
		elem.print();
		std::cout << "    --------------      "     << std::endl;
	}
	std::cout << std::endl;
	std::cout << "|++++STRUCT_TYPE INFO END++++++|" << std::endl;

	std::cout << std::endl;
	std::cout << "|++++ARRAY_TYPE INFO START++++|" << std::endl;
	for(auto elem : array_type_collector){
		elem.print();
		std::cout << "    --------------      "     << std::endl;
	}
	std::cout << std::endl;
	std::cout << "|++++ARRAY_TYPE INFO END++++++|" << std::endl;

}
