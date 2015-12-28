#include "utility_condition_statement_cnt.hh"




void cond_statement_cnt_c::push(void) {
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
int cond_statement_cnt_c::pop(void) {
	if(inner_scope != NULL) {
		if(inner_scope->pop() == 1) {
			delete inner_scope;
			inner_scope = NULL;
		} 
		return 0;
	} else {
		jmp_times.clear();
		condj_insert_times = 0;
		condj_find_times = 0;
		return 1;
	}
}
void cond_statement_cnt_c::clear(void) {
	if(inner_scope != NULL) {
		inner_scope->clear();
		delete inner_scope;
	}
	jmp_times.clear();
	condj_insert_times = 0;
	condj_find_times = 0;
}
void cond_statement_cnt_c::inc_jmp_times(void) {
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
void cond_statement_cnt_c::print_jmp_times(void) {
	std::cout << "====LAYER====" << std::endl;
	for(auto elem : jmp_times)
		std::cout << elem << ", " ;
	std::cout << std::endl;
	if(inner_scope != NULL) {
		inner_scope->print_jmp_times();
	}
}

unsigned int cond_statement_cnt_c::get_jmp_times_first_elem(void) {
	if(inner_scope != NULL) {
		inner_scope->get_jmp_times_first_elem();
	} else {
		return jmp_times.front();
	}
}
unsigned int cond_statement_cnt_c::pop_jmp_times_first_elem(void) {
	if(inner_scope != NULL) {
		inner_scope->pop_jmp_times_first_elem();
	} else {
		jmp_times.pop_front();
	}
}

void cond_statement_cnt_c::inc_condj_insert_times(void) {
	condj_insert_times++;
	if(inner_scope != NULL) {
		inner_scope->inc_condj_insert_times();
	} 
}
void cond_statement_cnt_c::inc_condj_find_times(void) {
	condj_find_times++;
	if(inner_scope != NULL) {
		inner_scope->inc_condj_find_times();
	} 
}
unsigned int cond_statement_cnt_c::get_condj_insert_times(void) {
	if(inner_scope != NULL) {
		return inner_scope->get_condj_insert_times();
	} else {
		return condj_insert_times;
	}
}
unsigned int cond_statement_cnt_c::get_condj_find_times(void) {
	if(inner_scope != NULL) {
		return inner_scope->get_condj_find_times();
	} else {
		return condj_find_times;
	}
}
void cond_statement_cnt_c::set_condj_insert_times(unsigned int n) {
	if(inner_scope != NULL) {
		inner_scope->set_condj_insert_times(n) ;
	} else {
		condj_insert_times = n;
	}
}
void cond_statement_cnt_c::set_condj_find_times(unsigned int n) {
	if(inner_scope != NULL) {
		inner_scope->set_condj_find_times(n);
	} else {
		condj_find_times = n;
	}
}

