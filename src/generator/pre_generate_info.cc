#include "pre_generate_info.hh"




internal_value_t pre_generate_pou_info_c::variable_type_check(std::string type)
{
	if(type == "SINT" || type == "INT" || type == "DINT" || type == "LINT")
		return TINT;
	else if(type == "USINT" || type == "UINT" || type == "UDINT" || type == "ULINT" 
		|| type == "BYTE" || type == "WORD" || type == "LWORD" || type == "DWORD")
		return TUINT;
	else if(type == "REAL" || type == "LREAL")
		return TDOUBLE;
	else if(type == "STRING" || type == "WSTRING")
		return TSTRING;
	else
		return TUNDEF;
	
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
	std::cout << std::endl;
	std::cout << "++++++POU DETAIL INFO START++++++" << std::endl;
	std::cout << "pou name: " << pou_name << std::endl;
	std::cout << "input number: " << input_variable.size() << std::endl;
	for(auto elem : input_variable)
		elem.print();
	std::cout << "in_out number: " << input_output_variable.size() << std::endl;
	for(auto elem : input_output_variable)
		elem.print();
	std::cout << "output number: " << output_variable.size() << std::endl;
	for(auto elem : output_variable)
		elem.print();
	std::cout << "local number: " << local_variable.size() << std::endl;
	for(auto elem : local_variable)
		elem.print();
	std::cout << "inst number: " << inst_code.size() << std::endl;
	std::cout << "code buffer: " << pre_code << std::endl;
	std::cout << "++++++POU DETAIL INFO END++++++++" << std::endl;
}


pre_generate_info_c::pre_generate_info_c()
{

}

bool pre_generate_info_c::insert(std::string pou_name, pre_generate_pou_info_c *info)
{
	pre_generate_info_collector.insert(std::pair<std::string, pre_generate_pou_info_c *>(pou_name, info));
}