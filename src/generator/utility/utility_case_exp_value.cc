#include "utility_case_exp_value.hh"





void case_exp_value_c::push(void) {
  if(push_not_first_time == true) {
    if(inner_scope != NULL) {
      inner_scope->push();
    } else {
      inner_scope = new case_exp_value_c();
    }
  } else {
    push_not_first_time = true;
  }
}
int case_exp_value_c::pop(void) {
  if(inner_scope != NULL) {
    if(inner_scope->pop() == 1) {
      delete inner_scope;
    } 
    return 0;
  } else {
    case_exp_value.clear();
    return 1;
  }
}

std::string case_exp_value_c::get_case_exp_value(void) {
  if(inner_scope != NULL) {
    return inner_scope->get_case_exp_value();
  }
  return case_exp_value;
} 
void case_exp_value_c::set_case_exp_value(std::string value) {
  if(inner_scope != NULL) {
    inner_scope->set_case_exp_value(value);
  } else {
    case_exp_value = value;
  }
}
