#include "generate_assignment_l_exp.hh"




/*******************************************/
/* ************ utility functions ******** */
/*******************************************/

std::string generate_assign_l_exp_c::numeric_to_string(int num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

std::string generate_assign_l_exp_c::numeric_to_string(double num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}



/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_assign_l_exp_c::visit(                 identifier_c *symbol) { TRACE("identifier_c");  return strdup(symbol->value); }
void *generate_assign_l_exp_c::visit(derived_datatype_identifier_c *symbol) { TRACE("derived_datatype_identifier_c"); return NULL;}
void *generate_assign_l_exp_c::visit(         poutype_identifier_c *symbol) { TRACE("poutype_identifier_c"); return NULL;}




/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_assign_l_exp_c::visit(symbolic_variable_c *symbol) {
	TRACE("symbolic_variable_c"); 
	int temp_num;
	std::string temp_num_str;
	std::string temp_str;

	temp_str = (char*)symbol->var_name->accept(*this);
	if((temp_num = pou_info->find_var_return_num(temp_str)) == -1)
	  ERROR_MSG("cannot find the specific variable !");

	temp_num_str = numeric_to_string(temp_num);
	
	return strdup(temp_num_str.c_str());
}


void *generate_assign_l_exp_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_assign_l_exp_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c"); return NULL;}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_assign_l_exp_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c");
  symbol->subscripted_variable->accept(*this);
  symbol->subscript_list->accept(*this);
  return NULL;
}


/* subscript_list ',' subscript */
void *generate_assign_l_exp_c::visit(subscript_list_c *symbol) {TRACE("subscript_list_c"); return NULL; }

/*  record_variable '.' field_selector */
void *generate_assign_l_exp_c::visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c"); 
  symbol->record_variable->accept(*this);
  symbol->field_selector->accept(*this);
  return NULL;
}



