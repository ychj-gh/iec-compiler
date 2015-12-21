#include "generate_pou_var_declaration.hh"





void *generate_pou_var_declaration_c::print_token(token_c *token) {

  return NULL;
}

//add by yaoshun
std::string generate_pou_var_declaration_c::numeric_to_string(int num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

std::string generate_pou_var_declaration_c::numeric_to_string(double num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

void *generate_pou_var_declaration_c::return_token(token_c *token) {
  return strdup(token->value);
}

void *generate_pou_var_declaration_c::return_striped_token(token_c *token, int offset) {
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

void *generate_pou_var_declaration_c::return_striped_binary_token(token_c *token, unsigned int offset ) {
  /* convert the binary value to hexadecimal format... */
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

void *generate_pou_var_declaration_c::return_striped_octal_token(token_c *token, unsigned int offset ) {
  /* convert the binary value to hexadecimal format... */
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


void *generate_pou_var_declaration_c::return_striped_hex_token(token_c *token, unsigned int offset ) {
  /* convert the binary value to hexadecimal format... */
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

void *generate_pou_var_declaration_c::print_literal(symbol_c *type, symbol_c *value) {

  if (NULL != type) {
    type->accept(*this);
  }
  return value->accept(*this);
  // return NULL;
}

void *generate_pou_var_declaration_c::print_list(list_c *list,
             std::string pre_elem_str ,
             std::string inter_elem_str ,
             std::string post_elem_str ) {
 
  for(int i = 0; i < list->n; i++) {
    list->elements[i]->accept(*this);
  }

  return NULL;
}


void *generate_pou_var_declaration_c::print_binary_expression(symbol_c *symbol,
            symbol_c *l_exp,
            symbol_c *r_exp,
            const char *operation) {


  l_exp->accept(*this);

  r_exp->accept(*this);

  return NULL;
}

void *generate_pou_var_declaration_c::print_unary_expression(symbol_c *symbol,
           symbol_c *exp,
           const char *operation) {


  exp->accept(*this);
  return NULL;
}



/*******************************************/
/* B 1.1 - Letters, digits and identifiers */
/*******************************************/
void *generate_pou_var_declaration_c::visit(                 identifier_c *symbol) { TRACE("identifier_c"); print_token(symbol); return strdup(symbol->value); }
void *generate_pou_var_declaration_c::visit(derived_datatype_identifier_c *symbol) { TRACE("derived_datatype_identifier_c"); return print_token(symbol);}
void *generate_pou_var_declaration_c::visit(         poutype_identifier_c *symbol) { TRACE("poutype_identifier_c"); return print_token(symbol);}

/*********************/
/* B 1.2 - Constants */
/*********************/
/*********************************/
/* B 1.2.XX - Reference Literals */
/*********************************/
/* defined in IEC 61131-3 v3 - Basically the 'NULL' keyword! */
void *generate_pou_var_declaration_c::visit(ref_value_null_literal_c *symbol)  { TRACE("ref_value_null_literal_c");  return NULL;}

/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_pou_var_declaration_c::visit(real_c *symbol)               { TRACE("real_c"); print_token(symbol); return return_striped_token(symbol);}
void *generate_pou_var_declaration_c::visit(integer_c *symbol)            { TRACE("integer_c"); print_token(symbol); return return_striped_token(symbol);}
void *generate_pou_var_declaration_c::visit(binary_integer_c *symbol)     { 
  TRACE("binary_integer_c"); 
  // std::cout << (char*)return_striped_binary_token(symbol, 2) << "===" << std::endl;
  return return_striped_binary_token(symbol, 2);
}

void *generate_pou_var_declaration_c::visit(octal_integer_c *symbol)      { TRACE("octal_integer_c"); return return_striped_octal_token(symbol, 2);}
void *generate_pou_var_declaration_c::visit(hex_integer_c *symbol)        { TRACE("hex_integer_c"); return return_striped_hex_token(symbol, 3);}

void *generate_pou_var_declaration_c::visit(neg_real_c *symbol)           { TRACE("neg_real_c"); return print_unary_expression(symbol, symbol->exp, "-");}
void *generate_pou_var_declaration_c::visit(neg_integer_c *symbol)        { TRACE("neg_integer_c"); return print_unary_expression(symbol, symbol->exp, "-");}

void *generate_pou_var_declaration_c::visit(integer_literal_c *symbol)    { TRACE("integer_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_pou_var_declaration_c::visit(real_literal_c *symbol)       { TRACE("real_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_pou_var_declaration_c::visit(bit_string_literal_c *symbol) { TRACE("bit_string_literal_c"); return print_literal(symbol->type, symbol->value);}
void *generate_pou_var_declaration_c::visit(boolean_literal_c *symbol)    { TRACE("boolean_literal_c"); return print_literal(symbol->type, symbol->value);}

/* helper class for boolean_literal_c */
void *generate_pou_var_declaration_c::visit(boolean_true_c *symbol)       { TRACE("boolean_true_c");  return NULL;}
void *generate_pou_var_declaration_c::visit(boolean_false_c *symbol)      { TRACE("boolean_false_c");  return NULL;}

/*******************************/
/* B.1.2.2   Character Strings */
/*******************************/
void *generate_pou_var_declaration_c::visit(double_byte_character_string_c *symbol) { TRACE("double_byte_character_string_c"); return print_token(symbol);}
void *generate_pou_var_declaration_c::visit(single_byte_character_string_c *symbol) { TRACE("single_byte_character_string_c"); return print_token(symbol);}




/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
void *generate_pou_var_declaration_c::visit(time_type_name_c *symbol)        {TRACE("time_type_name_c");  return strdup("TIME");}
void *generate_pou_var_declaration_c::visit(bool_type_name_c *symbol)        {TRACE("bool_type_name_c");  return strdup("BOOL");}
void *generate_pou_var_declaration_c::visit(sint_type_name_c *symbol)        {TRACE("sint_type_name_c");  return strdup("SINT");}
void *generate_pou_var_declaration_c::visit(int_type_name_c *symbol)         {TRACE("int_type_name_c");  return strdup("INT");}
void *generate_pou_var_declaration_c::visit(dint_type_name_c *symbol)        {TRACE("dint_type_name_c");   return strdup("DINT");}
void *generate_pou_var_declaration_c::visit(lint_type_name_c *symbol)        {TRACE("lint_type_name_c");   return strdup("USINT");}
void *generate_pou_var_declaration_c::visit(usint_type_name_c *symbol)       {TRACE("usint_type_name_c");   return strdup("USINT");}
void *generate_pou_var_declaration_c::visit(uint_type_name_c *symbol)        {TRACE("uint_type_name_c");   return strdup("UINT");}
void *generate_pou_var_declaration_c::visit(udint_type_name_c *symbol)       {TRACE("udint_type_name_c");   return strdup("UDINT");}
void *generate_pou_var_declaration_c::visit(ulint_type_name_c *symbol)       {TRACE("ulint_type_name_c");   return strdup("ULINT");}
void *generate_pou_var_declaration_c::visit(real_type_name_c *symbol)        {TRACE("real_type_name_c");   return strdup("REAL");}
void *generate_pou_var_declaration_c::visit(lreal_type_name_c *symbol)       {TRACE("lreal_type_name_c");   return strdup("LREAL");}
void *generate_pou_var_declaration_c::visit(date_type_name_c *symbol)        {TRACE("date_type_name_c");   return strdup("DATE");}
void *generate_pou_var_declaration_c::visit(tod_type_name_c *symbol)         {TRACE("tod_type_name_c");    return strdup("TOD");}
void *generate_pou_var_declaration_c::visit(dt_type_name_c *symbol)          {TRACE("dt_type_name_c");  return strdup("DT");}
void *generate_pou_var_declaration_c::visit(byte_type_name_c *symbol)        {TRACE("byte_type_name_c");   return strdup("BYTE");}
void *generate_pou_var_declaration_c::visit(word_type_name_c *symbol)        {TRACE("word_type_name_c"); return strdup("WORD");}
void *generate_pou_var_declaration_c::visit(lword_type_name_c *symbol)       {TRACE("lword_type_name_c");  return strdup("LWORD");}
void *generate_pou_var_declaration_c::visit(dword_type_name_c *symbol)       {TRACE("dword_type_name_c");   return strdup("DWORD");}
void *generate_pou_var_declaration_c::visit(string_type_name_c *symbol)      {TRACE("string_type_name_c");  return strdup("STRING");}
void *generate_pou_var_declaration_c::visit(wstring_type_name_c *symbol)     {TRACE("wstring_type_name_c");   return strdup("WSTRING");}

/********************************/
/* B.1.3.2 - Generic data types */
/********************************/
void *generate_pou_var_declaration_c::visit(generic_type_any_c      *symbol) {TRACE("generic_type_any_c");   return NULL;}

/********************************/
/* B 1.3.3 - Derived data types */
/********************************/
/*  TYPE type_declaration_list END_TYPE */
void *generate_pou_var_declaration_c::visit(data_type_declaration_c *symbol) {
  TRACE("data_type_declaration_c"); 
  
  symbol->type_declaration_list->accept(*this);
  
  return NULL;
}


/* helper symbol for data_type_declaration */
/*| type_declaration_list type_declaration ';' */
void *generate_pou_var_declaration_c::visit(type_declaration_list_c *symbol) {
  TRACE("type_declaration_list_c"); 
  return print_list(symbol,  std::string(""), ";\n" + std::string(""), ";\n");
}


/*  simple_type_name ':' simple_spec_init */
void *generate_pou_var_declaration_c::visit(simple_type_declaration_c *symbol) {
  TRACE("simple_type_declaration_c"); 
  symbol->simple_type_name->accept(*this);
  
  symbol->simple_spec_init->accept(*this);
  return NULL;
}


/* simple_specification ASSIGN constant */
void *generate_pou_var_declaration_c::visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c"); 
  var_type = (char*)symbol->simple_specification->accept(*this);
  
  if (symbol->constant != NULL) {
    
    var_value = (char*)symbol->constant->accept(*this);
  } else {
    var_value = "0";
  }

  return NULL;
}




/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_pou_var_declaration_c::visit(symbolic_variable_c *symbol) {TRACE("symbolic_variable_c"); return symbol->var_name->accept(*this);}
void *generate_pou_var_declaration_c::visit(symbolic_constant_c *symbol) {TRACE("symbolic_constant_c"); return symbol->var_name->accept(*this);}

/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_pou_var_declaration_c::visit(direct_variable_c *symbol) {TRACE("direct_variable_c"); return print_token(symbol);}


/*************************************/
/* B.1.4.2   Multi-element Variables */
/*************************************/
/*  subscripted_variable '[' subscript_list ']' */
void *generate_pou_var_declaration_c::visit(array_variable_c *symbol) {
  TRACE("array_variable_c");
  symbol->subscripted_variable->accept(*this);
  
  symbol->subscript_list->accept(*this);
  
  return NULL;
}


/* subscript_list ',' subscript */
void *generate_pou_var_declaration_c::visit(subscript_list_c *symbol) {TRACE("subscript_list_c"); return print_list(symbol, std::string(""), ", ");}

/*  record_variable '.' field_selector */
void *generate_pou_var_declaration_c::visit(structured_variable_c *symbol) {
  TRACE("structured_variable_c"); 
  symbol->record_variable->accept(*this);
  
  symbol->field_selector->accept(*this);
  return NULL;
}


/******************************************/
/* B 1.4.3 - Declaration & Initialisation */
/******************************************/
void *generate_pou_var_declaration_c::visit(constant_option_c *symbol) {TRACE("constant_option_c");  return NULL;}
void *generate_pou_var_declaration_c::visit(retain_option_c *symbol) {TRACE("retain_option_c");  return NULL;}
void *generate_pou_var_declaration_c::visit(non_retain_option_c *symbol) {TRACE("non_retain_option_c");  return NULL;}

/* VAR_INPUT [RETAIN | NON_RETAIN] input_declaration_list END_VAR */
/* option -> the RETAIN/NON_RETAIN/<NULL> directive... */
void *generate_pou_var_declaration_c::visit(input_declarations_c *symbol) {
  TRACE("input_declarations_c"); 
  pou_info->set_pou_status(POU_STA_VAR_IN_DEC);
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {

    if (symbol->option != NULL)
      symbol->option->accept(*this);
    
    symbol->input_declaration_list->accept(*this);
    
  }
  return NULL;
}

/* helper symbol for input_declarations */
/*| input_declaration_list input_declaration ';' */
void *generate_pou_var_declaration_c::visit(input_declaration_list_c *symbol) {
  TRACE("input_declaration_list_c"); 

  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/* edge -> The F_EDGE or R_EDGE directive */
void *generate_pou_var_declaration_c::visit(edge_declaration_c *symbol) {
  TRACE("edge_declaration_c"); 
  symbol->var1_list->accept(*this);

  symbol->edge->accept(*this);
  return NULL;
}

/* dummy classes only used as flags! */
void *generate_pou_var_declaration_c::visit(explicit_definition_c *symbol) {TRACE("explicit_definition_c"); return NULL;}
void *generate_pou_var_declaration_c::visit(implicit_definition_c *symbol) {TRACE("implicit_definition_c"); return NULL;}

/* EN : BOOL := 1 */
void *generate_pou_var_declaration_c::visit(en_param_declaration_c *symbol) {
  TRACE("en_param_declaration_c"); 
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {
    symbol->name->accept(*this);

    symbol->type_decl->accept(*this);
  }
  return NULL;
}

/* ENO : BOOL */
void *generate_pou_var_declaration_c::visit(eno_param_declaration_c *symbol) {
  TRACE("eno_param_declaration_c"); 
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {
    symbol->name->accept(*this);

    symbol->type->accept(*this);
  }
  return NULL;
}

void *generate_pou_var_declaration_c::visit(raising_edge_option_c *symbol) {
  TRACE("raising_edge_option_c"); 

  return NULL;
}

void *generate_pou_var_declaration_c::visit(falling_edge_option_c *symbol) {
  TRACE("falling_edge_option_c"); 

  return NULL;
}


/* var1_list is one of the following...
 *    simple_spec_init_c *
 *    subrange_spec_init_c *
 *    enumerated_spec_init_c *
 */
void *generate_pou_var_declaration_c::visit(var1_init_decl_c *symbol) {
  TRACE("var1_init_decl_c");
  symbol->var1_list->accept(*this);

  symbol->spec_init->accept(*this);
  if((ivt = pou_info->variable_type_check(var_type)) == TUNDEF){
     ERROR_MSG("variable type check error!");
  }
  
  for(auto elem : var_name_set) {
    IValue iv;
    iv.type = ivt;
    iv.name = elem;
    if(ivt == TINT) {
      if (!var_value.empty())
        iv.v.value_i = std::stoi(var_value);
    }
    else if(ivt == TUINT) {
      if (!var_value.empty())
        iv.v.value_u = std::stoi(var_value);
    }
    else if(ivt == TDOUBLE) {
      if (!var_value.empty())
       iv.v.value_d = std::stod(var_value);
    }
    else {
      iv.v.value_s.str = strdup(var_value.c_str());
      iv.v.value_s.length = strlen(var_value.c_str());
    }
    if(POU_STA_VAR_IN_DEC == pou_info->get_pou_status())
      pou_info->input_variable.push_back(iv);
    else if(POU_STA_VAR_OUT_DEC == pou_info->get_pou_status())
      pou_info->output_variable.push_back(iv);
    else if(POU_STA_VAR_INOUT_DEC == pou_info->get_pou_status())
      pou_info->input_output_variable.push_back(iv);
    else if(POU_STA_VAR_LOCAL_DEC == pou_info->get_pou_status())
      pou_info->local_variable.push_back(iv);
    else
      ERROR_MSG("wrong pou status !");

  }
  var_name_set.clear();

  return NULL;
}


void *generate_pou_var_declaration_c::visit(var1_list_c *symbol) {
  TRACE("var1_list_c");

  for(int i = 0; i < symbol->n; i++) {
    std::string str = (char*)symbol->elements[i]->accept(*this);

    var_name_set.push_back(str);
  }

  return NULL;
}


/* VAR_OUTPUT [RETAIN | NON_RETAIN] var_init_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(output_declarations_c *symbol) {
  TRACE("output_declarations_c"); 
  pou_info->set_pou_status(POU_STA_VAR_OUT_DEC);
  if (typeid(*(symbol->method)) == typeid(explicit_definition_c)) {

    if (symbol->option != NULL)
      symbol->option->accept(*this);

    symbol->var_init_decl_list->accept(*this);

  }
  return NULL;
}

/*  VAR_IN_OUT  END_VAR */
void *generate_pou_var_declaration_c::visit(input_output_declarations_c *symbol) {
  TRACE("input_output_declarations_c"); 
  pou_info->set_pou_status(POU_STA_VAR_INOUT_DEC);

  symbol->var_declaration_list->accept(*this);

  return NULL;
}


/* VAR [CONSTANT] var_init_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(var_declarations_c *symbol) {
  TRACE("var_declarations_c");
  
  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->var_init_decl_list->accept(*this);

  return NULL;
}

/*  VAR RETAIN var_init_decl_list END_VAR */
void *generate_pou_var_declaration_c::visit(retentive_var_declarations_c *symbol) {
  TRACE("retentive_var_declarations_c");

  symbol->var_init_decl_list->accept(*this);

  return NULL;
}

/*  VAR [CONSTANT|RETAIN|NON_RETAIN] located_var_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(located_var_declarations_c *symbol) {
  TRACE("located_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->located_var_decl_list->accept(*this);

  return NULL;
}

/* helper symbol for located_var_declarations */
/* located_var_decl_list located_var_decl ';' */
void *generate_pou_var_declaration_c::visit(located_var_decl_list_c *symbol) {
  TRACE("located_var_decl_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*  [variable_name] location ':' located_var_spec_init */
/* variable_name -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(located_var_decl_c *symbol) {
  TRACE("located_var_decl_c");
  if (symbol->variable_name != NULL) {
    symbol->variable_name->accept(*this);

  }
  symbol->location->accept(*this);

  symbol->located_var_spec_init->accept(*this);
  return NULL;
}


/*| VAR_EXTERNAL [CONSTANT] external_declaration_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(external_var_declarations_c *symbol) {
  TRACE("external_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->external_declaration_list->accept(*this);

  return NULL;
}

/* helper symbol for external_var_declarations */
/*| external_declaration_list external_declaration';' */
void *generate_pou_var_declaration_c::visit(external_declaration_list_c *symbol) {
  TRACE("external_declaration_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name) */
void *generate_pou_var_declaration_c::visit(external_declaration_c *symbol) {
  TRACE("external_declaration_c");
  symbol->global_var_name->accept(*this);

  symbol->specification->accept(*this);
  return NULL;
}

/*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_pou_var_declaration_c::visit(global_var_declarations_c *symbol) {
  TRACE("global_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->global_var_decl_list->accept(*this);

  return NULL;
}

/* helper symbol for global_var_declarations */
/*| global_var_decl_list global_var_decl ';' */
void *generate_pou_var_declaration_c::visit(global_var_decl_list_c *symbol) {
  TRACE("global_var_decl_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
void *generate_pou_var_declaration_c::visit(global_var_decl_c *symbol) {
  TRACE("global_var_decl_c");
  symbol->global_var_spec->accept(*this);

  if (symbol->type_specification != NULL)
    symbol->type_specification->accept(*this);
  return NULL;
}

/*| global_var_name location */
void *generate_pou_var_declaration_c::visit(global_var_spec_c *symbol) {
  TRACE("global_var_spec_c");
  symbol->global_var_name->accept(*this);

  symbol->location->accept(*this);
  return NULL;
}

/*  AT direct_variable */
void *generate_pou_var_declaration_c::visit(location_c *symbol) {
  TRACE("location_c");

  symbol->direct_variable->accept(*this);
  return NULL;
}

/*| global_var_list ',' global_var_name */
void *generate_pou_var_declaration_c::visit(global_var_list_c *symbol) {TRACE("global_var_list_c"); return print_list(symbol, std::string(""), ", ");}



/*| VAR [RETAIN|NON_RETAIN] incompl_located_var_decl_list END_VAR */
/* option ->may be NULL ! */
void *generate_pou_var_declaration_c::visit(incompl_located_var_declarations_c *symbol) {
  TRACE("incompl_located_var_declarations_c");

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->incompl_located_var_decl_list->accept(*this);

  return NULL;
}

/* helper symbol for incompl_located_var_declarations */
/*| incompl_located_var_decl_list incompl_located_var_decl ';' */
void *generate_pou_var_declaration_c::visit(incompl_located_var_decl_list_c *symbol) {
  TRACE("incompl_located_var_decl_list_c");
  return print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
}

/*  variable_name incompl_location ':' var_spec */
void *generate_pou_var_declaration_c::visit(incompl_located_var_decl_c *symbol) {
  TRACE("incompl_located_var_decl_c");
  symbol->variable_name->accept(*this);

  symbol->incompl_location->accept(*this);

  symbol->var_spec->accept(*this);
  return NULL;
}


/*  AT incompl_location_token */
void *generate_pou_var_declaration_c::visit(incompl_location_c *symbol) {
  TRACE("incompl_location_c");

  return print_token(symbol);
}


/* intermediate helper symbol for:
 *  - non_retentive_var_decls
 *  - output_declarations
 */
/* | var_init_decl_list var_init_decl ';' */
void *generate_pou_var_declaration_c::visit(var_init_decl_list_c *symbol) {
  TRACE("var_init_decl_list_c");
  return print_list(symbol,std::string(""), ";\n" + std::string(""), ";\n");
}


/***********************/
/* B 1.5.1 - Functions */
/***********************/

/* intermediate helper symbol for function_declaration */
void *generate_pou_var_declaration_c::visit(var_declarations_list_c *symbol) { 
  TRACE("var_declarations_list_c"); 
  pou_info->set_pou_status(POU_STA_VAR_DEC);
  return print_list(symbol);
}

void *generate_pou_var_declaration_c::visit(function_var_decls_c *symbol) {
  TRACE("function_var_decls_c"); 
  pou_info->set_pou_status(POU_STA_VAR_LOCAL_DEC);

  if (symbol->option != NULL)
    symbol->option->accept(*this);

  symbol->decl_list->accept(*this);

  return NULL;
}

/* intermediate helper symbol for function_var_decls */
void *generate_pou_var_declaration_c::visit(var2_init_decl_list_c *symbol) {
  TRACE("var2_init_decl_list_c"); 
  print_list(symbol, std::string(""), ";\n" + std::string(""), ";\n");
  return NULL;
}

/*****************************/
/* B 1.5.2 - Function Blocks */
/*****************************/
/*  VAR_TEMP temp_var_decl_list END_VAR */
void *generate_pou_var_declaration_c::visit(temp_var_decls_c *symbol) {
  TRACE("temp_var_decls_c"); 

  symbol->var_decl_list->accept(*this);

  return NULL;
}

/* intermediate helper symbol for temp_var_decls */
void *generate_pou_var_declaration_c::visit(temp_var_decls_list_c *symbol) {TRACE("temp_var_decls_list_c"); return print_list(symbol);}

/*  VAR NON_RETAIN var_init_decl_list END_VAR */
void *generate_pou_var_declaration_c::visit(non_retentive_var_decls_c *symbol) {
  TRACE("non_retentive_var_decls_c"); 

  symbol->var_decl_list->accept(*this);

  return NULL;
}

