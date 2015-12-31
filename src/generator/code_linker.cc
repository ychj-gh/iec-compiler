#include "code_linker.hh"







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

			auto temp_beg = res_des.task_list_set.begin();
			auto temp_end = res_des.task_list_set.end();
			while(temp_beg != temp_end) {
				if((*temp_beg).task_name == res_program.bind_task_name) {
					temp_obj_task.task_des.task_priority = (*temp_beg).task_priority;
					temp_obj_task.task_des.task_period = (*temp_beg).task_interval;
					// temp_obj_task.task_des.task_type = (*temp_beg).task_is_signal;//wait to code
					// temp_obj_task.task_des.signal_source = (*temp_beg).task_signal;//wait to code

					break;
				}
				temp_beg++;
			}

			auto beg = pre_code_info->pre_generate_info_collector.begin();
			auto end = pre_code_info->pre_generate_info_collector.end();
			while(temp_beg != temp_end) {
				if((*beg).get_pou_name() == res_program.program_instance_name) {
					user_pou_c temp_user_pou;
					temp_user_pou.user_pou_name = beg->get_pou_name();
					temp_user_pou.input_count = beg->input_variable.size();
					temp_user_pou.inout_count = beg->input_output_variable.size();
					temp_user_pou.output_count = beg->output_variable.size();
					temp_user_pou.local_count = std::stoi(beg->get_pou_reg_num()) - temp_user_pou.input_count - temp_user_pou.inout_count - temp_user_pou.output_count;
					temp_user_pou.code_entry = 0;
    				
    				for(auto const_elem : beg->constant_value) {
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

    				
					temp_obj_task.user_pou_list.push_back(temp_user_pou);
					break;
				}
				temp_beg++;
			}





			obj_file.task_list.push_back(temp_obj_task);

		}

	}
}



