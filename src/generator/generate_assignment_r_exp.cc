#include "generate_assignment_r_exp.hh"




/*******************************************/
/* ************ utility functions ******** */
/*******************************************/

std::string generate_assign_r_exp_c::numeric_to_string(int num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

std::string generate_assign_r_exp_c::numeric_to_string(double num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

void *generate_assign_r_exp_c::return_token(token_c *token) {
  return strdup(token->value);
}

void *generate_assign_r_exp_c::return_striped_token(token_c *token, int offset) {
  std::string str = "";
  bool leading_zero = true;
  for (unsigned int i = offset; i < strlen(token->value); i++) {
    if (leading_zero
        && (   token->value[i] != '0'
            || i == strlen(token->value) - 1
            || token->value[i + 1] == '.'
            )
        )
      leading_zero = false;
        if (!leading_zero && token->value[i] != '_')
      str += token->value[i];
  }
  return strdup(str.c_str());
}

void *generate_assign_r_exp_c::return_striped_binary_token(token_c *token, unsigned int offset) {
  /* convert the binary value to decimal format... */
  unsigned long val = 0;
  unsigned int i;
  
  for (i = offset; i < strlen(token->value); i++) {
    if (token->value[i] != '_') {
      if(token->value[i] == '1')
        val = val * 2 + 1;
      else
        val = val * 2;
    }
  }

  std::stringstream stream;
  std::string result;
  stream << val; 
  stream >> result; 

  return strdup(result.c_str());
}

void *generate_assign_r_exp_c::return_striped_octal_token(token_c *token, unsigned int offset) {
  /* convert the octal value to decimal format... */
  unsigned long val = 0;
  unsigned int i;
  
  for (i = offset; i < strlen(token->value); i++) {
    if (token->value[i] != '_') {
      switch(token->value[i])
      {
        case '0':
          val = val * 8;
          break;
        case '1':
          val = val * 8 + 1;
          break;
        case '2':
          val = val * 8 + 2;
          break;
        case '3':
          val = val * 8 + 3;
          break;
        case '4':
          val = val * 8 + 4;
          break;
        case '5':
          val = val * 8 + 5;
          break;
        case '6':
          val = val * 8 + 6;
          break;
        case '7':
          val = val * 8 + 7;
          break;
        default:
          break;
      }
    }
  }

  std::stringstream stream;
  std::string result;
  stream << val; 
  stream >> result; 

  return strdup(result.c_str());
}


void *generate_assign_r_exp_c::return_striped_hex_token(token_c *token, unsigned int offset) {
  /* convert the hex value to decimal format... */
  unsigned long val = 0;
  unsigned int i;
  
  for (i = offset; i < strlen(token->value); i++) {
    if (token->value[i] != '_') {
      switch(token->value[i])
      {
        case '0':
          val = val * 16;
          break;
        case '1':
          val = val * 16 + 1;
          break;
        case '2':
          val = val * 16 + 2;
          break;
        case '3':
          val = val * 16 + 3;
          break;
        case '4':
          val = val * 16 + 4;
          break;
        case '5':
          val = val * 16 + 5;
          break;
        case '6':
          val = val * 16 + 6;
          break;
        case '7':
          val = val * 16 + 7;
          break;
        case '8':
          val = val * 16 + 8;
          break;
        case '9':
          val = val * 16 + 9;
          break;
        case 'A':
        case 'a':
          val = val * 16 + 10;
          break;
        case 'B':
        case 'b':
          val = val * 16 + 11;
          break;
        case 'C':
        case 'c':
          val = val * 16 + 12;
          break;
        case 'D':
        case 'd':
          val = val * 16 + 13;
          break;
        case 'E':
        case 'e':
          val = val * 16 + 14;
          break;
        case 'F':
        case 'f':
          val = val * 16 + 15;
          break;
        default:
          break;
      }
    }
  }

  std::stringstream stream;
  std::string result;
  stream << val; 
  stream >> result; 

  return strdup(result.c_str());
}

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
	iv.v.value_d = std::stod((char*)return_striped_token(symbol));
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
	iv.v.value_u = std::stoi((char*)return_striped_token(symbol));
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
	iv.v.value_u = std::stoi((char*)return_striped_binary_token(symbol, 2));
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
	iv.v.value_u = std::stoi((char*)return_striped_octal_token(symbol, 2));
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
	iv.v.value_u = std::stoi((char*)return_striped_hex_token(symbol, 3));
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
	iv.v.value_d = -1 * std::stod((char*)return_striped_token(dynamic_cast<token_c*>(symbol->exp)));
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
	iv.v.value_i = -1 * std::stoi((char*)return_striped_token(dynamic_cast<token_c*>(symbol->exp)));
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
void *generate_assign_r_exp_c::visit(boolean_literal_c *symbol)    { TRACE("boolean_literal_c"); return NULL;}

/* helper class for boolean_literal_c */
void *generate_assign_r_exp_c::visit(boolean_true_c *symbol)       { TRACE("boolean_true_c");  return NULL;}
void *generate_assign_r_exp_c::visit(boolean_false_c *symbol)      { TRACE("boolean_false_c");  return NULL;}

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

	temp_num_str = numeric_to_string(temp_num);

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
  symbol->record_variable->accept(*this);
  symbol->field_selector->accept(*this);
  return NULL;
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

/* logical expressions */
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

