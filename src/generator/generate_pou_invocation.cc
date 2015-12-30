#include "generate_pou_invocation.hh"




void *generate_pou_invocation_c::print_list(list_c *list,
			       std::string pre_elem_str ,
			       std::string inter_elem_str ,
			       std::string post_elem_str ) {

  for(int i = 0; i < list->n; i++) {
    list->elements[i]->accept(*this);
  }
  return NULL;
}

/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_pou_invocation_c::visit(                 identifier_c *symbol) { 
	TRACE("identifier_c"); 
	return strdup(symbol->value); 
}
void *generate_pou_invocation_c::visit(derived_datatype_identifier_c *symbol) { 
	TRACE("derived_datatype_identifier_c"); 
	return NULL;
}
void *generate_pou_invocation_c::visit(         poutype_identifier_c *symbol) { 
  TRACE("poutype_identifier_c"); 
  return strdup(symbol->value); 
}



/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_pou_invocation_c::visit(real_c *symbol)               { 
	TRACE("real_c"); 
	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TDOUBLE;
	iv.v.value_d = std::stod((char*)utility_token_get_c::return_striped_token(symbol));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(integer_c *symbol) { 
	TRACE("integer_c"); 

	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TUINT;
	iv.v.value_u = std::stoi((char*)utility_token_get_c::return_striped_token(symbol));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}
void *generate_pou_invocation_c::visit(binary_integer_c *symbol)     { 
  	TRACE("binary_integer_c"); 

	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TUINT;
	iv.v.value_u = std::stoi((char*)utility_token_get_c::return_striped_binary_token(symbol, 2));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(octal_integer_c *symbol) { 
	TRACE("octal_integer_c"); 
	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TUINT;
	iv.v.value_u = std::stoi((char*)utility_token_get_c::return_striped_octal_token(symbol, 2));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}


void *generate_pou_invocation_c::visit(hex_integer_c *symbol) { 
	TRACE("hex_integer_c"); 
	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TUINT;
	iv.v.value_u = std::stoi((char*)utility_token_get_c::return_striped_hex_token(symbol, 3));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(neg_real_c *symbol) { 
	TRACE("neg_real_c"); 
	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TDOUBLE;
	iv.v.value_d = -1 * std::stod((char*)utility_token_get_c::return_striped_token(dynamic_cast<token_c*>(symbol->exp)));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(neg_integer_c *symbol) { 
	TRACE("neg_integer_c"); 

	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_num + std::string(" ");

	IValue iv;
	iv.type = TINT;
	iv.v.value_i = -1 * std::stoi((char*)utility_token_get_c::return_striped_token(dynamic_cast<token_c*>(symbol->exp)));
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(integer_literal_c *symbol)    { 
	TRACE("integer_literal_c"); 
	if (NULL != symbol->type) {
		symbol->type->accept(*this);
	}
	return symbol->value->accept(*this);
}

void *generate_pou_invocation_c::visit(real_literal_c *symbol)       { 
	TRACE("real_literal_c"); 
	if (NULL != symbol->type) {
		symbol->type->accept(*this);
	}
	return symbol->value->accept(*this);
}

void *generate_pou_invocation_c::visit(bit_string_literal_c *symbol) { TRACE("bit_string_literal_c"); return NULL;}
void *generate_pou_invocation_c::visit(boolean_literal_c *symbol)    { 
  TRACE("boolean_literal_c"); 

  /* useless code, just for structrue complete */
  if (NULL != symbol->type) {
    symbol->type->accept(*this);
  }
  /* formal code */
  std::string temp_code = std::string("kload ") ;
  std::string temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();

  temp_code += temp_reg_num + std::string(" ");

  IValue iv;
  iv.type = TUINT;
  iv.v.value_u = std::stoi((char*)symbol->value->accept(*this));
  pou_info->constant_value.push_back(iv);

  temp_code += pou_info->get_pou_const_num();
  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}

/* helper class for boolean_literal_c */
void *generate_pou_invocation_c::visit(boolean_true_c *symbol)       { 
  TRACE("boolean_true_c");  
  return strdup("1");
}
void *generate_pou_invocation_c::visit(boolean_false_c *symbol)      { 
  TRACE("boolean_false_c");  
  return strdup("0");
}

/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_pou_invocation_c::visit(symbolic_variable_c *symbol) {
	TRACE("symbolic_variable_c"); 
	int temp_num;
	std::string temp_num_str;
	std::string temp_str; 

	temp_str = (char*)symbol->var_name->accept(*this);
	if((temp_num = pou_info->find_var_return_num(temp_str)) == -1)
	  ERROR_MSG("cannot find the specific variable !");

	temp_num_str = utility_token_get_c::numeric_to_string(temp_num);

	return strdup(temp_num_str.c_str());
}

void *generate_pou_invocation_c::visit(symbolic_constant_c *symbol) {
	TRACE("symbolic_constant_c"); 
	return symbol->var_name->accept(*this);
}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_pou_invocation_c::visit(direct_variable_c *symbol) {
	TRACE("direct_variable_c"); 
	return NULL;
}


/***********************/
/* B 3.1 - Expressions */
/***********************/

/* arithmetic expressions */
void *generate_pou_invocation_c::visit( add_expression_c *symbol) {
	TRACE("add_expression_c"); 

	std::string temp_code = "add ";
	std::string temp_reg_num;

    temp_reg_num = pou_info->get_pou_reg_num();
    pou_info->inc_pou_reg_num();
    temp_code += temp_reg_num;
    temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);

    temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);
    pou_info->inst_code.push_back(temp_code);

   return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(   sub_expression_c *symbol) {
	TRACE("sub_expression_c"); 

	std::string temp_code = "sub ";
	std::string temp_reg_num;

	temp_reg_num = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();
	temp_code += temp_reg_num;
	temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);

    temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);
    pou_info->inst_code.push_back(temp_code);

  	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(   mul_expression_c *symbol) {
	TRACE("mul_expression_c"); 

	std::string temp_code = "mul ";
	std::string temp_reg_num;

    temp_reg_num = pou_info->get_pou_reg_num();
    pou_info->inc_pou_reg_num();
    temp_code += temp_reg_num;
    temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
 
    temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);
    pou_info->inst_code.push_back(temp_code);

  	return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(   div_expression_c *symbol) {
	TRACE("div_expression_c"); 

	std::string temp_code = "div ";
	std::string temp_reg_num;
  
    temp_reg_num = pou_info->get_pou_reg_num();
    pou_info->inc_pou_reg_num();
    temp_code += temp_reg_num;
    temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  
    temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);
    pou_info->inst_code.push_back(temp_code);

	return strdup(temp_reg_num.c_str());
}

/* comparison expressions */
void *generate_pou_invocation_c::visit(   equ_expression_c *symbol) {
  TRACE("equ_expression_c"); 
  std::string temp_code = "eq ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}
void *generate_pou_invocation_c::visit(notequ_expression_c *symbol) {
  TRACE("notequ_expression_c"); 
  std::string temp_code = "ne ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}
void *generate_pou_invocation_c::visit(    lt_expression_c *symbol) {
  TRACE("lt_expression_c"); 

  std::string temp_code = "lt ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}
void *generate_pou_invocation_c::visit(    gt_expression_c *symbol) {
  TRACE("gt_expression_c"); 
  std::string temp_code = "gt ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}
void *generate_pou_invocation_c::visit(    le_expression_c *symbol) {
  TRACE("le_expression_c"); 
  std::string temp_code = "le ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}
void *generate_pou_invocation_c::visit(    ge_expression_c *symbol) {
  TRACE("ge_expression_c"); 
  std::string temp_code = "ge ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}

/* logical expressions */
void *generate_pou_invocation_c::visit(    or_expression_c *symbol) {
  TRACE("or_expression_c"); 
  std::string temp_code = "lor ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(   xor_expression_c *symbol) {
  TRACE("xor_expression_c"); 
  std::string temp_code = "lxor ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(   and_expression_c *symbol) {
  TRACE("and_expression_c"); 
  std::string temp_code = "land ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->l_exp->accept(*this);
  temp_code += std::string(" ") + (char*)symbol->r_exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}

void *generate_pou_invocation_c::visit(   not_expression_c *symbol) {
  TRACE("not_expression_c"); 
  std::string temp_code = "lnot ";
  std::string temp_reg_num;

  temp_reg_num = pou_info->get_pou_reg_num();
  pou_info->inc_pou_reg_num();
  temp_code += temp_reg_num;
  temp_code += std::string(" ") + (char*)symbol->exp->accept(*this);

  pou_info->inst_code.push_back(temp_code);

  return strdup(temp_reg_num.c_str());
}


/*****************************************/
/* B 3.2.2 Subprogram Control Statements */
/*****************************************/

/*  RETURN */
void *generate_pou_invocation_c::visit(return_statement_c *symbol) {
  TRACE("return_statement_c");
  return NULL;
}


/* helper symbol for fb_invocation */
/* param_assignment_list ',' param_assignment */
void *generate_pou_invocation_c::visit(param_assignment_list_c *symbol) {
  TRACE("param_assignment_list_c"); 

  std::vector<std::string> param_list;
  std::string temp_code;
  std::string temp_reg_num;
  std::string pou_invo_reg_base;
  bool first_flag = true;

  for(int i = 0; i < symbol->n; i++) {
    param_list.push_back((char*)symbol->elements[i]->accept(*this));
  }
  for(auto elem : param_list) {
  	temp_code = "mov ";

  	temp_reg_num = pou_info->get_pou_reg_num();
  	pou_info->inc_pou_reg_num();

  	temp_code += temp_reg_num + std::string(" ");
  	temp_code += elem;
  	if(first_flag == true) {
  		pou_invo_reg_base = temp_reg_num;
  		first_flag = false;
  	}
  	pou_info->inst_code.push_back(temp_code);
  }
  return strdup(pou_invo_reg_base.c_str());
}


void *generate_pou_invocation_c::visit(input_variable_param_assignment_c *symbol) {
  TRACE("input_variable_param_assignment_c"); 
  symbol->variable_name->accept(*this);
  symbol->expression->accept(*this);
  return NULL;
}


void *generate_pou_invocation_c::visit(output_variable_param_assignment_c *symbol) {
  TRACE("output_variable_param_assignment_c"); 
  if (symbol->not_param != NULL)
    symbol->not_param->accept(*this);
  symbol->variable_name->accept(*this);
  symbol->variable->accept(*this);
  return NULL;
}


void *generate_pou_invocation_c::visit(not_paramassign_c *symbol) {
  TRACE("not_paramassign_c"); 
  return NULL;
}


