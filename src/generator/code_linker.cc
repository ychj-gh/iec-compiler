#include "code_linker.hh"


//注意：当字符串为空时，也会返回一个空字符串
void code_linker_c::split(std::string& s, const std::string& delim,std::vector< std::string >* ret)
{
	size_t last = 0;
	size_t index=s.find_first_of(delim,last);
	while (index!=std::string::npos)
	{
		ret->push_back(s.substr(last,index-last));
		last=index+1;
		index=s.find_first_of(delim,last);
	}
	if (index-last>0)
	{
		ret->push_back(s.substr(last,index-last));
	}
}


void code_linker_c::link_task_pou(std::list<pre_generate_pou_info_c>::iterator& pou_iterator,
									obj_task_c& temp_obj_task, std::string pou_ret) {
	user_pou_c temp_user_pou;
	temp_user_pou.user_pou_name = pou_iterator->get_pou_name();
	temp_user_pou.pds_type = pou_iterator->get_pou_type();
	temp_user_pou.input_count = pou_iterator->input_variable.size();
	temp_user_pou.inout_count = pou_iterator->input_output_variable.size();
	temp_user_pou.output_count = pou_iterator->output_variable.size();
	temp_user_pou.local_count = std::stoi(pou_iterator->get_pou_reg_num()) - temp_user_pou.input_count - temp_user_pou.inout_count - temp_user_pou.output_count;
	temp_user_pou.code_entry = temp_obj_task.code_list.size();

	// 消除重复的常量,节省空间，但code is dirty， 需要优化
	for(auto const_elem : pou_iterator->constant_value) {
		bool flag = true;
		for(auto obj_const_elem : temp_obj_task.const_list) {
			if(const_elem == obj_const_elem) {
				flag = false;
				break;
			}
		}
		if(flag == true) {
			temp_obj_task.const_list.push_back(const_elem);
		}
	}

	// 上一步中消除了重复变量，所以对应索引也发生了变化，需要更新代码中的常量索引
	auto code_beg = pou_iterator->inst_code.begin();
	auto code_end = pou_iterator->inst_code.end();
	while(code_beg != code_end) {
		if((*code_beg).find("kload") == 0) {
			std::vector<std::string> code_slice;
			IValue iv;
			unsigned int i = 0;
			this->split(*code_beg, " ", &code_slice);
			if(code_slice.size() != 3) {
				ERROR;
			}
			iv = pou_iterator->constant_value[std::stoi(code_slice[2])];
			for(auto obj_const_elem : temp_obj_task.const_list) {
				if(iv == obj_const_elem) {
					code_slice[2] = std::to_string(i);
				}
				i++;
			}
			*code_beg = code_slice[0] + std::string(" ") + code_slice[1] + std::string(" ") + code_slice[2];
		}
		code_beg++;

	}
	temp_obj_task.user_pou_list.push_back(temp_user_pou);

	auto end_index = temp_obj_task.code_list.end();
	unsigned int inst_code_count = temp_obj_task.code_list.size();
	temp_obj_task.code_list.insert(end_index, pou_iterator->inst_code.begin(), pou_iterator->inst_code.end());

	auto start_index = temp_obj_task.code_list.begin() ;
	for(; inst_code_count > 0; inst_code_count --)
		start_index ++;

	end_index = start_index;
	inst_code_count = pou_iterator->inst_code.size();
	for(; inst_code_count > 0; inst_code_count --)
		end_index ++;

	/**
	 * 解析ucall指令
	 * 预生成信息类对象中格式为：ucall index1 name index2
	 * 其中，index1为调用pou传入的寄存器其实索引，name为被调用pou名，index2为返回调用pou的寄存器索引
	 * 在运行系统ucall指令格式为：ucall index1 pou_index
	 * 因此，需要根据pou名找到对应pou索引
	 */
	std::string &ret_code_ref = temp_obj_task.code_list.back();
	while(start_index != end_index) { // 查找代码中是否包含ucall指令
		if ((*start_index).find("ucall") == 0) {
			std::vector<std::string>  code_slice;

			this->split(*start_index, " ", &code_slice);
			if(code_slice.size() != 4) { 	// 若ucall指令格式不对，则输出错误信息
				std::cout << "ucall convertion error" << std::endl;
				for(auto elem : code_slice)
					std::cout << elem << std::string(" ") ;
				std::cout << std::endl;
			} else { // ucall指令格式正确，则检查该pou是否已添加temp_obj_task中。
				bool flag = false; // 指示该pou是否已添加temp_obj_task中
				unsigned int i =0;
				for(auto elem : temp_obj_task.user_pou_list) {
					if(elem.user_pou_name == code_slice[2]) {
						code_slice[2] = std::to_string(i);
						flag = true;
						break;
					}
					i++;
				}
				if (flag != true){  // 若在temp_obj_task中未找到，则需要在预生成信息类中查找
					auto pou_begin = pre_code_info->pre_generate_info_collector.begin();
					auto pou_ended = pre_code_info->pre_generate_info_collector.end();
					while(pou_begin != pou_ended) {
						if((*pou_begin).get_pou_name() == code_slice[2]) { // 若找到，则递归添加该pou到temp_obj_task中
							flag = true;
							this->link_task_pou(pou_begin, temp_obj_task, code_slice[3]);
							unsigned int i =0;
							for(auto elem : temp_obj_task.user_pou_list) {
								if(elem.user_pou_name == code_slice[2]) {
									code_slice[2] = std::to_string(i);
									break;
								}
								i++;
							}
							break;
						}
						pou_begin++;
					}
				}
				/**
				 * 若该pou为系统级POU，则需要改用scall指令，该指令格式为： scall index1 pou_index
				 * 在此处只需将指令写为ucall index1 pou_name即可，因为在后面翻译器（translator程序）运行时会将
				 * pou_name变换为对应的系统级POU索引
				 */
				if(flag != true){	// 若仍然未找到对应pou，则在系统库pou中查找
					int i = 0;
					while(standard_function_names[i] != NULL){
						if(code_slice[2] == standard_function_names[i]){
							flag = true;
							*start_index = std::string("scall ") + code_slice[1] + std::string(" ") + code_slice[2];
							break;
						}
						i ++;
					}
					if(flag != true){
						std::cout << "ERROR: There is a wrong pou invocation : " << code_slice[2] << std::endl;
						exit(-1);
					}
				} else {
					*start_index = code_slice[0] + std::string(" ") + code_slice[1] + std::string(" ") + code_slice[2];
				}
			}
		}
		start_index++;
	}
	/**
     * FUNCTION型POU和FB型POU的结尾为ret指令，此指令格式为：ret A Bx，但A与Bx在目前运行系统中并未用到（前期有使用，后发现不合理）
	 * 故在将A和Bx均设置为0
	 */
	if(ret_code_ref.find("ret") == 0) {
		// std::cout << pou_ret << std::endl;
		ret_code_ref += "0 0";
	}



}



/**
 * 链接主调用函数，由编译预生成信息类对象pre_code_info，生成目标文件代码信息
 */
void code_linker_c::link_code(void) {
	/* 对应IEC61131-3编程模型中资源内容逐个生成 */
	for(auto res_des : pre_code_info->configuration_info.res_list_set) {
		// 获得任务间全局变量信息（对应目标文件中PG段）
		for(auto res_global_var : res_des.resource_global_var_set) {
			IValue iv;
			iv = res_global_var.type_value;
			obj_file.global_list.push_back(iv);
		}
		obj_file.global_count = obj_file.global_list.size();

		// 获得任务间直接变量信息
		for(auto res_global_dir : res_des.resource_global_dir_set) {
			/* wait for code */
		}

		/* 对应IEC61131-3编程模型中任务内容逐个生成 */
		for(auto res_program : res_des.program_list_set) {
			obj_task_c temp_obj_task;
			std::string temp_str;

			temp_obj_task.task_des.task_name = res_program.program_name;

			auto task_beg = res_des.task_list_set.begin();
			auto task_end = res_des.task_list_set.end();
			while(task_beg != task_end) {
				if((*task_beg).task_name == res_program.bind_task_name) {
					temp_obj_task.task_des.task_priority = (*task_beg).task_priority;  // 任务优先级
					temp_obj_task.task_des.task_period = (*task_beg).task_interval * 1000000ul; // 任务周期由ms转换为ns
					temp_obj_task.task_des.task_type = (*task_beg).task_is_signal;

					/**
					 * 如果此任务为事件触发性任务，则在任务间全局变量或直接变量中查找触发源；如果触发源为全局变量，
					 * 则signal_source为全局变量索引（0~2^15-1）;若为直接变量，则signal_source为（2^15~2^16-1）
					 * 即通过signal_source（short型）的最高位区分;任务间全局变量个数一般不超过2^15-1。
					 */
					if(temp_obj_task.task_des.task_type == 1){
						std::string signal_name = (*task_beg).task_signal; // 获得信号源名

						bool flag = false ; 	// 指示是否已找到对应信号源变量，若全局变量索引中找到，则不需要再查找直接变量索引

						// 全局变量索引
						for(int i = 0; i < obj_file.global_list.size(); i++){
							if(obj_file.global_list[i].name == signal_name){
								temp_obj_task.task_des.signal_source = i;
								if(i >= 0x8000){
									std::cout << "ERROR: index of task signal_source variable should be less then 0x8000" << std::endl;
									exit(-1);
								}
								flag = true;
								break;
							}
						}
						// 直接变量索引
						if(flag != true){	// 全局变量索引中未找到信号源变量
							for(int i = 0; i < res_des.resource_global_dir_set.size(); i ++){
								if(res_des.resource_global_dir_set[i].type_value.name == signal_name){
									temp_obj_task.task_des.signal_source = i | 0x8000; // 使最高位为1，以指示其为直接变量
									flag = true;
									break;
								}
							}
						}
					} else { // 如果任务为周期性任务，则忽略此项，置为0
						temp_obj_task.task_des.signal_source = 0;
					}
					break;
				}
				task_beg++;
			}

			/* 生成组成task的程序代码 */
			auto pou_beg = pre_code_info->pre_generate_info_collector.begin();
			auto pou_end = pre_code_info->pre_generate_info_collector.end();
			while(pou_beg != pou_end) {
				if((*pou_beg).get_pou_name() == res_program.program_instance_name) {
					this->link_task_pou(pou_beg, temp_obj_task, "");
					break;
				}
				pou_beg++;
			}

			/**
			 * 在主POU即PROGRAM中，生成输入输出代码；
			 * 即在主POU开头加入输入代码，在主POU结尾，即halt 0 0 0指令之前加入输出代码；
			 * 同时在添加后需修改除主POU外，其他所有POU的代码入口即entry值。
			 */
			// 输入变量 key:= value
			std::vector<std::string> input_code; // 读入输入的代码
			for(auto elem : res_program.assign_arguement){
				// 查找每一个输入变量key对应POU中的寄存器索引, 包括在input型变量中查找和在inout型变量中查找；
				int index = 0;     // 输入变量对应POU中的寄存器索引
				bool flag = false ; // 判断是否在input型变量中找到，若找到，则置为true，inout型变量中则不再查找。
				for(int i = 0; i < (*pou_beg).input_variable.size(); i ++){
					if((*pou_beg).input_variable[i].name == elem.key){
						flag = true;
						index = i;
						break;
					}
				}
				if(flag != true){ // 在input型变量中未找到对应变量
					for(int i = 0; i < (*pou_beg).input_output_variable.size(); i ++){
						if((*pou_beg).input_output_variable[i].name == elem.key){
							flag = true;
							index = i + (*pou_beg).input_variable.size(); // input_output_variable变量在input_variable之后，所以索引要加上input_variable的个数
							break;
						}
					}
				}
				// 若找到了对应key的寄存器索引，则接下来查找对应输入value的类型（直接变量or任务间全局变量）及其索引
				if(flag == true){
					int index2 = 0; // 对应任务间全局变量索引
					int found = 0; // 指示是否找到及类型，0：未找到，1：任务间全局变量,2：直接变量
					for(int i = 0; i < obj_file.global_list.size(); i++){ 	// 在任务间全局变量中查找
						if(obj_file.global_list[i].name == elem.value){
							found = 1;
							index2 = i;
							break;
						}
					}
					if(found != 1){ // 在全局变量中未找到，需要在直接变量中查找
						for(int i = 0; i < res_des.resource_global_dir_set.size(); i ++){
							if(res_des.resource_global_dir_set[i].type_value.name == elem.value){
								found = 2;
								index2 = i;
								break;
							}
						}
					}
					if(found == 1){   // 对应输入value的类型为任务间全局变量
						// 全局变量加载指令：gload A Bx  ==> R[A]<--G[Bx]
						std::string temp_code = "pgload ";
						temp_code += std::to_string(index) + std::string(" ") + std::to_string(index2);
						input_code.push_back(temp_code);
					} else if(found == 2){ // 对应输入value的类型为直接变量
						// 直接变量加载指令： ldload A B C ==> R[A]<--LDI[B,C], B为起始位，C为长度
						std::string str = res_des.resource_global_dir_set[index2].location;
						if(str.size() < 4 || str[0] != '%' || str[1] != 'I'){
							std::cout << "ERROR: Main pou has a wrong input value location: " << str << std::endl;
							exit(-1);
						}
						/**
						 * 接下来解析%IX（1位）或%IB（8位）或%IW（16位）或%ID（32位）或%IL（64位）
						 * 在用户层面数字IO每8个（1Byte）为一个通道，如：
						 * %IB0为取通道0的8位IO值；
						 * %IX0.1为取通道0的第一位，%IX12为取整个I/O的第12位，等价于%IX1.4;
						 * %IW1为取通道1的第0位开始的16位，即通道1和通道2的值
						 * %ID2为取通道2的第0位开始的32位，即通道2,3,4,5的值
						 * %IL0为取通道0的第0位开始的64位，即通道0,1,2,3,4,5,6,7的值
						 * I/O简图如下：(假设总共8通道)
						 * ######### ######### ######### ######## ######### ######### ######### ######### #########
						 * ^         ^         ^         ^        ^         ^         ^         ^         ^
						 * |		 |         |         |        |         |         |         |         |
						 * ch0       ch1       ch2       ch3      ch4       ch5       ch6       ch7       ch8
						 */
						std::vector<std::string> ret;
						std::string s = str.substr(3);
						std::string temp_code = "ldload ";
						switch (str[2]) {
							case 'X':
								split(s, ".", &ret);
								if(ret.size() == 1){	// %IX中不包含'.'
									temp_code += std::to_string(index) + std::string(" ") + ret[0] + std::string(" ") + std::to_string(1);
									input_code.push_back(temp_code);
								} else if(ret.size() == 2){ // %IX中包含'.'
									temp_code += std::to_string(index) + std::string(" ") ;
									int B = 8 * std::stoi(ret[0]) + std::stoi(ret[1]);
									temp_code += std::to_string(B) + std::string(" ") + std::to_string(1);
									input_code.push_back(temp_code);
								} else {
									std::cout << "ERROR: Main pou has a wrong input value location: " << str << std::endl;
									exit(-1);
								}
								break;
							case 'B':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(8);
								input_code.push_back(temp_code);
								break;
							case 'W':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(16);
								input_code.push_back(temp_code);
								break;
							case 'D':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(32);
								input_code.push_back(temp_code);
								break;
							case 'L':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(32);
								input_code.push_back(temp_code);
								break;
						}
					} else { // 若未找到对应索引，则输出错误信息并退出
						std::cout << "ERROR: Main pou has a wrong input value variable" << std::endl;
						exit(-1);
					}
				} else {	// 若未找到对应寄存器索引，则输出错误信息并退出
					std::cout << "ERROR: Main pou has a wrong input key variable" << std::endl;
					exit(-1);
				}
			}

			// 输出变量： key => value
			std::vector<std::string> output_code; // 刷新输出的代码
			for(auto elem : res_program.sendto_arguement){
				// 查找每一个输入变量key对应POU中的寄存器索引, 包括在output型变量中查找和在inout型变量中查找；
				int index = 0;     // 输入变量对应POU中的寄存器索引
				bool flag = false ; // 判断是否在inout型变量中找到，若找到，则置为true，output型变量中则不再查找。
				for(int i = 0; i < (*pou_beg).input_output_variable.size(); i ++){
					if((*pou_beg).input_output_variable[i].name == elem.key){
						flag = true;
						index = i + (*pou_beg).input_variable.size(); // input_output_variable变量在input_variable之后，所以索引要加上input_variable的个数
						break;
					}
				}
				if(flag != true){ // 在inout型变量中未找到对应变量
					for(int i = 0; i < (*pou_beg).output_variable.size(); i ++){
						if((*pou_beg).output_variable[i].name == elem.key){
							flag = true;
							index = i + (*pou_beg).input_variable.size() + (*pou_beg).input_output_variable.size(); // input_output_variable变量在input_variable之后，所以索引要加上input_variable的个数
							break;
						}
					}
				}
				// 若找到了对应key的寄存器索引，则接下来查找对应输入value的类型（直接变量or任务间全局变量）及其索引
				if(flag == true){
					int index2 = 0; // 对应任务间全局变量索引
					int found = 0; // 指示是否找到及类型，0：未找到，1：任务间全局变量,2：直接变量
					for(int i = 0; i < obj_file.global_list.size(); i++){ 	// 在任务间全局变量中查找
						if(obj_file.global_list[i].name == elem.value){
							found = 1;
							index2 = i;
							break;
						}
					}
					if(found != 1){ // 在全局变量中未找到，需要在直接变量中查找
						for(int i = 0; i < res_des.resource_global_dir_set.size(); i ++){
							if(res_des.resource_global_dir_set[i].type_value.name == elem.value){
								found = 2;
								index2 = i;
								break;
							}
						}
					}
					if(found == 1){   // 对应输入value的类型为任务间全局变量
						// 全局变量存储指令：gstore A Bx  ==> R[A]-->G[Bx]
						std::string temp_code = "pgstore ";
						temp_code += std::to_string(index) + std::string(" ") + std::to_string(index2);
						output_code.push_back(temp_code);
					} else if(found == 2){ // 对应输入value的类型为直接变量
						// 直接变量输出指令： ldstore A B C ==> R[A]-->LDI[B,C], B为起始位，C为长度
						std::string str = res_des.resource_global_dir_set[index2].location;
						if(str.size() < 4 || str[0] != '%' || str[1] != 'Q'){
							std::cout << "ERROR: Main pou has a wrong output value location: " << str << std::endl;
							exit(-1);
						}
						/**
						 * 接下来解析%QX（1位）或%QB（8位）或%QW（16位）或%QD（32位）或%QL（64位）
						 * 在用户层面数字IO每8个（1Byte）为一个通道，如：
						 * %QB0为取通道0的8位IO值；
						 * %QX0.1为取通道0的第一位，%QX12为取整个I/O的第12位，等价于%QX1.4;
						 * %QW1为取通道1的第0位开始的16位，即通道1和通道2的值
						 * %QD2为取通道2的第0位开始的32位，即通道2,3,4,5的值
						 * %QL0为取通道0的第0位开始的64位，即通道0,1,2,3,4,5,6,7的值
						 * I/O简图如下：(假设总共8通道)
						 * ######### ######### ######### ######## ######### ######### ######### ######### #########
						 * ^         ^         ^         ^        ^         ^         ^         ^         ^
						 * |		 |         |         |        |         |         |         |         |
						 * ch0       ch1       ch2       ch3      ch4       ch5       ch6       ch7       ch8
						 */
						std::vector<std::string> ret;
						std::string s = str.substr(3);
						std::string temp_code = "ldstore ";
						switch (str[2]) {
							case 'X':
								split(s, ".", &ret);
								if(ret.size() == 1){	// %IX中不包含'.'
									temp_code += std::to_string(index) + std::string(" ") + ret[0] + std::string(" ") + std::to_string(1);
									output_code.push_back(temp_code);
								} else if(ret.size() == 2){ // %IX中包含'.'
									temp_code += std::to_string(index) + std::string(" ") ;
									int B = 8 * std::stoi(ret[0]) + std::stoi(ret[1]);
									temp_code += std::to_string(B) + std::string(" ") + std::to_string(1);
									output_code.push_back(temp_code);
								} else {
									std::cout << "ERROR: Main pou has a wrong input value location: " << str << std::endl;
									exit(-1);
								}
								break;
							case 'B':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(8);
								output_code.push_back(temp_code);
								break;
							case 'W':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(16);
								output_code.push_back(temp_code);
								break;
							case 'D':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(32);
								output_code.push_back(temp_code);
								break;
							case 'L':
								temp_code += std::to_string(index) + std::string(" ") + str.substr(3) + std::string(" ") + std::to_string(32);
								output_code.push_back(temp_code);
								break;
						}
					} else { // 若未找到对应索引，则输出错误信息并退出
						std::cout << "ERROR: Main pou has a wrong input value variable" << std::endl;
						exit(-1);
					}
				} else {	// 若未找到对应寄存器索引，则输出错误信息并退出
					std::cout << "ERROR: Main pou has a wrong input key variable" << std::endl;
					exit(-1);
				}
			}
			/*************************************************************************************/
			/*************************************************************************************/
			/*************************************************************************************/
			/*************************************************************************************/
			/*************************************************************************************/
			/* 下一步：
				1.插入输入输出代码；
				2.各pou的entry更新；
				3.设计pgload指令和pgstore指令；
				4.主POU有名变量与任务内global区变量交换；
				5.处理ucall与scall；
				6.处理functionblock；
			*/
			/**
 			 * 将任务的读入输入和刷新输出代码插入到主POU的前后
			 * 即，将input_code指令集添加到主POU之前（实际也是所有程序之前），
			 * 将output_code指令集添加到主POU的尾部，也就是halt指令之前
			 */
			// 1.将input_code代码加入到任务代码前面
			temp_obj_task.code_list.insert(temp_obj_task.code_list.begin(), input_code.begin(), input_code.end());
			// 2.将output_code代码加入到halt指令之前
			auto code_tail = std::find(temp_obj_task.code_list.begin(), temp_obj_task.code_list.end(), "halt 0 0 0");
			temp_obj_task.code_list.insert(code_tail, output_code.begin(), output_code.end());

			/**
			 * 将主POU（即PROGRAM）中的有名变量（包括input型，output型，inout型，var...end_var型）与任务内global区变量交换
			 * 因为PROGRAM中的有名变量类似与FB中变量，属于静态变量，需要放在全局数据区，
			 * 在FB中的处理方法是，对每一个FB对应一个ref_type型实体变量，放在refval区（引用类型数据区，其实也是一种任务内global区变量）
			 * 但对应PROGRAM型POU，在每个PLC任务中只有一个，所以可以简化设计，直接在任务内global区对应，
			 * 在程序开始前将变量从全局区加载到寄存器，程序结束前需要将寄存器中内容存储到全局区；
			 * 即，任务内global区保存的唯一内容为PROGRAM的一般类型有名变量（非ref_type型变量，此变量需放置在refval区）
			 */
			/* 将有名变量（包括input型，inout型，output型，var...end_var型）加入global区,对应以下四行 */
			temp_obj_task.global_list.insert(temp_obj_task.global_list.end(), (*pou_beg).input_variable.begin(), (*pou_beg).input_variable.end());
			temp_obj_task.global_list.insert(temp_obj_task.global_list.end(), (*pou_beg).input_output_variable.begin(), (*pou_beg).input_output_variable.end());
			temp_obj_task.global_list.insert(temp_obj_task.global_list.end(), (*pou_beg).output_variable.begin(), (*pou_beg).output_variable.end());
			temp_obj_task.global_list.insert(temp_obj_task.global_list.end(), (*pou_beg).local_variable.begin(), (*pou_beg).local_variable.end());

			std::vector<std::string> gload_code; // 在程序开始前将全局变量加载到寄存器代码
			for(int i = 0; i < temp_obj_task.global_list.size(); i ++){
				std::string temp_code = "gload ";
				temp_code += std::to_string(i) + std::string(" ") + std::to_string(i);
				gload_code.push_back(temp_code);
			}
			std::vector<std::string> gstore_code; // 在程序结束前将寄存器存储到全局代码
			for(int i = 0; i < temp_obj_task.global_list.size(); i ++){
				std::string temp_code = "gstore ";
				temp_code += std::to_string(i) + std::string(" ") + std::to_string(i);
				gstore_code.push_back(temp_code);
			}

			/**
 			 * 将全局交换代码插入到主POU的前后
			 * 即，将gload_code指令集添加到主POU之前（实际也是所有程序之前），
			 * 将gstore_code指令集添加到主POU的尾部，也就是halt指令之前
			 */
			// 1.将gload_code代码加入到任务代码前面
			temp_obj_task.code_list.insert(temp_obj_task.code_list.begin(), gload_code.begin(), gload_code.end());
			// 2.将gstore_code代码加入到halt指令之前
			code_tail = std::find(temp_obj_task.code_list.begin(), temp_obj_task.code_list.end(), "halt 0 0 0");
			temp_obj_task.code_list.insert(code_tail, gstore_code.begin(), gstore_code.end());


			/**
			 * 更新所有pou的entry
			 * 因为新插入的代码添加在主POU（即PROGRAM）的前后，且主POU代码总是放在code_list的开头；
			 * 所以，entry值等于原entry值加上添加的指令个数；
			 */
			int offset = input_code.size() + output_code.size() + gload_code.size() + gstore_code.size(); // entry偏移值，即新添加的代码总的指令个数
			// 因为主POU的entry值不需要修改，所以下面的循环中i从1开始
			for(int i = 1; i < temp_obj_task.user_pou_list.size(); i ++){
				temp_obj_task.user_pou_list[i].code_entry += offset;
			}

			temp_obj_task.task_des.pou_count = temp_obj_task.user_pou_list.size();
			temp_obj_task.task_des.stack_count = temp_obj_task.user_pou_list.size() + 2; // 调用栈的个数为POU个数加2，富余2个；
			temp_obj_task.task_des.const_count = temp_obj_task.const_list.size();
			temp_obj_task.task_des.global_count = temp_obj_task.global_list.size();
			temp_obj_task.task_des.retain_count = temp_obj_task.retain_list.size();
			temp_obj_task.task_des.inst_count = temp_obj_task.code_list.size();

			/**
			 * 将代码中与跳转相关的指令统一；
			 * 在代码编译阶段，由于if语句，while语句，switch语句等都涉及判断跳转指令（conj和jmp），
			 * 当其相互嵌套时，判定conj和jmp的对应关系非常复杂，为简化问题，在编译阶段，生成了不同的
			 * 伪指令，if语句对应conj_if和jmp_if,while语句对应conj_while和jmp_while，...
			 * 此时需要统一还原。
			 */
			auto code_beg = temp_obj_task.code_list.begin();
			auto code_end = temp_obj_task.code_list.end();
			while(code_beg != code_end) {
				if((*code_beg).find("condj") == 0) {
					std::vector<std::string> code_slice;
					this->split(*code_beg, " ", &code_slice);

					code_slice[0] = "condj";
					*code_beg = code_slice[0] + std::string(" ") + code_slice[1] + std::string(" ") + code_slice[2];
				}
				if((*code_beg).find("jmp") == 0) {
					std::vector<std::string> code_slice;
					this->split(*code_beg, " ", &code_slice);

					code_slice[0] = "jmp";
					*code_beg = code_slice[0] + std::string(" ") + code_slice[1] + std::string(" ") + code_slice[2];
				}
				code_beg ++;
			}


			obj_file.task_list.push_back(temp_obj_task);
			obj_file.task_count = obj_file.task_list.size();

		}

	}
}
