#ifndef __UTILITY_CONDITION_STATEMENT_CNT_HH__
#define __UTILITY_CONDITION_STATEMENT_CNT_HH__

#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <deque>
#include "generate_iec.hh"

#include "stage4.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.





class cond_statement_cnt_c {
public:
	bool push_not_first_time_flag;

	std::deque<unsigned int> jmp_times;

	unsigned int condj_insert_times;
	unsigned int condj_find_times;
	cond_statement_cnt_c *inner_scope;
	

public:
	cond_statement_cnt_c(void)  {
		condj_insert_times = 0;
		condj_find_times = 0;
		inner_scope = NULL;
		push_not_first_time_flag = false;
	}
	~cond_statement_cnt_c(void) {
		clear();
	}

public:
	void push(void) ;
	int pop(void) ;

	void clear(void) ;
	void inc_jmp_times(void) ;
	void print_jmp_times(void) ;
	unsigned int get_jmp_times_first_elem(void) ;
	unsigned int pop_jmp_times_first_elem(void) ;

	void inc_condj_insert_times(void) ;
	void inc_condj_find_times(void) ;
	unsigned int get_condj_insert_times(void) ;
	unsigned int get_condj_find_times(void) ;
	void set_condj_insert_times(unsigned int n) ;
	void set_condj_find_times(unsigned int n) ;
};



#endif

