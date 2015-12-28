#ifndef __UTILITY_CASE_EXP_VALUE_HH__
#define __UTILITY_CASE_EXP_VALUE_HH__


#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include "generate_iec.hh"

#include "stage4.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.

#include "pre_generate_info.hh"



class case_exp_value_c {
public:
  std::string case_exp_value;
  case_exp_value_c *inner_scope;
  bool push_not_first_time;
public:
  case_exp_value_c(void) {
    case_exp_value = "";
    inner_scope = NULL;
    push_not_first_time = false;
  }
  ~case_exp_value_c() {
  	
  }

  void push(void) ;
  int pop(void) ;

  std::string get_case_exp_value(void) ;

  void set_case_exp_value(std::string value);
};


#endif

