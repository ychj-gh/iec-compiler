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
	temp_user_pou.input_count = pou_iterator->input_variable.size();
	temp_user_pou.inout_count = pou_iterator->input_output_variable.size();
	temp_user_pou.output_count = pou_iterator->output_variable.size();
	temp_user_pou.local_count = std::stoi(pou_iterator->get_pou_reg_num()) - temp_user_pou.input_count - temp_user_pou.inout_count - temp_user_pou.output_count;
	temp_user_pou.code_entry = temp_obj_task.code_list.size();
	
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

	std::string &ret_code_ref = temp_obj_task.code_list.back();
	while(start_index != end_index) {
		if ((*start_index).find("ucall") == 0) {
			std::vector<std::string>  code_slice;

			this->split(*start_index, " ", &code_slice);
			if(code_slice.size() != 4) {
				std::cout << "ucall convertion error" << std::endl;
				for(auto elem : code_slice)
					std::cout << elem << std::string(" ") ;
				std::cout << std::endl;
			} else {
				auto pou_begin = pre_code_info->pre_generate_info_collector.begin();
				auto pou_ended = pre_code_info->pre_generate_info_collector.end();
				while(pou_begin != pou_ended) {
					if((*pou_begin).get_pou_name() == code_slice[2]) {
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
				*start_index = code_slice[0] + std::string(" ") + code_slice[1] + std::string(" ") + code_slice[2];
			}
		}
		start_index++;
	}
	CP(111)
	if(ret_code_ref.find("ret") == 0) {
		CP(333)
		std::cout << pou_ret << std::endl;
		ret_code_ref += pou_ret;
	}
	CP(222)

	

}




void code_linker_c::link_code(void) {
	for(auto res_des : pre_code_info->configuration_info.res_list_set) {
		for(auto res_global_var : res_des.resource_global_var_set) {
			// IValue iv;
			// iv = res_global_var.type_value;
			// obj_file.global_list.push_back(iv);
		}

		for(auto res_global_dir : res_des.resource_global_dir_set) {
			/* wait for code */
		}

		for(auto res_program : res_des.program_list_set) {
			obj_task_c temp_obj_task;
			std::string temp_str;

			temp_obj_task.task_des.task_name = res_program.program_name;

			auto task_beg = res_des.task_list_set.begin();
			auto task_end = res_des.task_list_set.end();
			while(task_beg != task_end) {
				if((*task_beg).task_name == res_program.bind_task_name) {
					temp_obj_task.task_des.task_priority = (*task_beg).task_priority;
					temp_obj_task.task_des.task_period = (*task_beg).task_interval;
					// temp_obj_task.task_des.task_type = (*task_beg).task_is_signal;//wait to code
					// temp_obj_task.task_des.signal_source = (*task_beg).task_signal;//wait to code

					break;
				}
				task_beg++;
			}

			auto pou_beg = pre_code_info->pre_generate_info_collector.begin();
			auto pou_end = pre_code_info->pre_generate_info_collector.end();
			while(pou_beg != pou_end) {
				if((*pou_beg).get_pou_name() == res_program.program_instance_name) {
					this->link_task_pou(pou_beg, temp_obj_task, "");
					break;
				}
				pou_beg++;
			}

			temp_obj_task.task_des.pou_count = temp_obj_task.user_pou_list.size();
			temp_obj_task.task_des.const_count = temp_obj_task.const_list.size();
			temp_obj_task.task_des.global_count = temp_obj_task.global_list.size();
			temp_obj_task.task_des.retain_count = temp_obj_task.retain_list.size();
			temp_obj_task.task_des.inst_count = temp_obj_task.code_list.size();


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



