#include "generate_assignment_r_exp.hh"
#include "utility_token_get.hh"



/*******************************************/
/* ************ utility functions ******** */
/*******************************************/






/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_assign_r_exp_c::visit(                 identifier_c *symbol) { TRACE("identifier_c");  return strdup(symbol->value); }
void *generate_assign_r_exp_c::visit(derived_datatype_identifier_c *symbol) { TRACE("derived_datatype_identifier_c"); return NULL;}
void *generate_assign_r_exp_c::visit(         poutype_identifier_c *symbol) { TRACE("poutype_identifier_c"); return NULL;}


/*********************/
/* B 1.2 - Constants */
/*********************/
/*********************************/
/* B 1.2.XX - Reference Literals */
/*********************************/
/* defined in IEC 61131-3 v3 - Basically the 'NULL' keyword! */
void *generate_assign_r_exp_c::visit(ref_value_null_literal_c *symbol)  { TRACE("ref_value_null_literal_c"); return NULL;}

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_assign_r_exp_c::visit(real_c *symbol)               {
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

void *generate_assign_r_exp_c::visit(integer_c *symbol) {
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
void *generate_assign_r_exp_c::visit(binary_integer_c *symbol)     {
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

void *generate_assign_r_exp_c::visit(octal_integer_c *symbol) {
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


void *generate_assign_r_exp_c::visit(hex_integer_c *symbol) {
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

void *generate_assign_r_exp_c::visit(neg_real_c *symbol) {
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

void *generate_assign_r_exp_c::visit(neg_integer_c *symbol) {
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

void *generate_assign_r_exp_c::visit(integer_literal_c *symbol)    {
	TRACE("integer_literal_c");
	if (NULL != symbol->type) {
		symbol->type->accept(*this);
	}
	return symbol->value->accept(*this);
}

void *generate_assign_r_exp_c::visit(real_literal_c *symbol)       {
	TRACE("real_literal_c");
	if (NULL != symbol->type) {
		symbol->type->accept(*this);
	}
	return symbol->value->accept(*this);
}

void *generate_assign_r_exp_c::visit(bit_string_literal_c *symbol) { TRACE("bit_string_literal_c"); return NULL;}
void *generate_assign_r_exp_c::visit(boolean_literal_c *symbol)    {
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
void *generate_assign_r_exp_c::visit(boolean_true_c *symbol)       {
  TRACE("boolean_true_c");
  return strdup("1");
}
void *generate_assign_r_exp_c::visit(boolean_false_c *symbol)      {
  TRACE("boolean_false_c");
  return strdup("0");
}

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
void *generate_assign_r_exp_c::visit(double_byte_character_string_c *symbol) { TRACE("double_byte_character_string_c"); return NULL;}
void *generate_assign_r_exp_c::visit(single_byte_character_string_c *symbol) { TRACE("single_byte_character_string_c"); return NULL;}


/***************************/
/* B 1.2.3 - Time Literals */
/***************************/

/************************/
/* B 1.2.3.1 - Duration */
/************************/
void *generate_assign_r_exp_c::visit(neg_time_c *symbol) { TRACE("neg_time_c");  return NULL;}

void *generate_assign_r_exp_c::visit(duration_c *symbol) {
  TRACE("duration_c");
  if (symbol->neg != NULL)
    symbol->neg->accept(*this);
  symbol->interval->accept(*this);
  return NULL;
}

void *generate_assign_r_exp_c::visit(fixed_point_c *symbol) { TRACE("fixed_point_c"); return NULL;}

/* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
void *generate_assign_r_exp_c::visit(interval_c *symbol) {
  TRACE("interval_c");
  if (NULL != symbol->days) {
    symbol->days->accept(*this);
  }

  if (NULL != symbol->hours) {
    symbol->hours->accept(*this);
  }

  if (NULL != symbol->minutes) {
    symbol->minutes->accept(*this);
  }

  if (NULL != symbol->seconds) {
    symbol->seconds->accept(*this);
  }

  if (NULL != symbol->milliseconds) {
    symbol->milliseconds->accept(*this);
  }

  return NULL;
}



/************************************/
/* B 1.2.3.2 - Time of day and Date */
/************************************/

void *generate_assign_r_exp_c::visit(time_of_day_c *symbol) {
  TRACE("time_of_day_c");
  symbol->daytime->accept(*this);
  return NULL;
}

void *generate_assign_r_exp_c::visit(daytime_c *symbol) {
  TRACE("daytime_c");
  symbol->day_hour->accept(*this);
  symbol->day_minute->accept(*this);
  symbol->day_second->accept(*this);
  return NULL;
}


void *generate_assign_r_exp_c::visit(date_c *symbol) {
  TRACE("date_c");
  symbol->date_literal->accept(*this);
  return NULL;
}

void *generate_assign_r_exp_c::visit(date_literal_c *symbol) {
  TRACE("date_literal_c");
  symbol->year->accept(*this);
  symbol->month->accept(*this);
  symbol->day->accept(*this);
  return NULL;
}

void *generate_assign_r_exp_c::visit(date_and_time_c *symbol) {
  TRACE("date_and_time_c");
  symbol->date_literal->accept(*this);
  symbol->daytime->accept(*this);
  return NULL;
}


/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_assign_r_exp_c::visit(symbolic_variable_c *symbol) {
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


void *generate_assign_r_exp_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_assign_r_exp_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c"); return NULL;}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_assign_r_exp_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c");
  symbol->subscripted_variable->accept(*this);
  symbol->subscript_list->accept(*this);
  return NULL;
}


/* subscript_list ',' subscript */
void *generate_assign_r_exp_c::visit(subscript_list_c *symbol) {TRACE("subscript_list_c"); return NULL; }

/*  record_variable '.' field_selector */
void *generate_assign_r_exp_c::visit(structured_variable_c *symbol) {
	TRACE("structured_variable_c");
	std::string record_str = (char*)symbol->record_variable->accept(*this);
	int record_num = std::stoi(record_str);		// 获得变量在struct_var_collector中的索引
	std::cout << record_str << std::endl;

	std::string field_str = (char*)symbol->field_selector->accept(*this);
	std::cout << field_str << std::endl;
	int field_num = -1;
	/* 获得对应字段在该结构体类型中的索引 */
	for(int i = 0; i < pou_info->struct_var_collector[record_num].elements.size(); i ++){
	  std::string temp = pou_info->struct_var_collector[record_num].elements[i].name;
	  if(temp == field_str){
		  field_num = i;
		  break;
	  }
	}
	// getfield指令格式：getfield 寄存器A 寄存器B 寄存器C；故需要先加载常量到寄存器中
	std::string temp_code = std::string("kload ") ;
	std::string temp_reg_numB = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_numB + std::string(" ");

	IValue iv;
	iv.type = TUINT;
	iv.v.value_u = record_num;
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);
// ********************************************************
	temp_code = std::string("kload ") ;
	std::string temp_reg_numC = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();

	temp_code += temp_reg_numC + std::string(" ");

	iv.type = TUINT;
	iv.v.value_u = field_num;
	pou_info->constant_value.push_back(iv);

	temp_code += pou_info->get_pou_const_num();
	pou_info->inst_code.push_back(temp_code);

// ********************************************************
// ********************************************************
	temp_code = "getfield ";

	std::string temp_reg_numA = pou_info->get_pou_reg_num();
	pou_info->inc_pou_reg_num();
	temp_code += temp_reg_numA;

	temp_code += std::string(" ") + temp_reg_numB + std::string(" ") + temp_reg_numC;
	pou_info->inst_code.push_back(temp_code);

  	return strdup(temp_reg_numA.c_str());
}

/***********************/
/* B 3.1 - Expressions */
/***********************/

/* arithmetic expressions */
void *generate_assign_r_exp_c::visit( add_expression_c *symbol) {
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

void *generate_assign_r_exp_c::visit(   sub_expression_c *symbol) {
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

void *generate_assign_r_exp_c::visit(   mul_expression_c *symbol) {
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

void *generate_assign_r_exp_c::visit(   div_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(   equ_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(notequ_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(    lt_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(    gt_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(    le_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(    ge_expression_c *symbol) {
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
void *generate_assign_r_exp_c::visit(    or_expression_c *symbol) {
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

void *generate_assign_r_exp_c::visit(   xor_expression_c *symbol) {
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

void *generate_assign_r_exp_c::visit(   and_expression_c *symbol) {
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

void *generate_assign_r_exp_c::visit(   not_expression_c *symbol) {
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
