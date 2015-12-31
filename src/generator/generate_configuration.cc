#include "generate_configuration.hh"





void *generate_configuration_c::print_literal(symbol_c *type, symbol_c *value) {

  if (NULL != type) {
    type->accept(*this);
  }
  return value->accept(*this);
  // return NULL;
}


void *generate_configuration_c::print_list(list_c *list,
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
void *generate_configuration_c::visit(                 identifier_c *symbol) {
	TRACE("identifier_c");  
	return strdup(symbol->value); 
}
void *generate_configuration_c::visit(derived_datatype_identifier_c *symbol) {
	TRACE("derived_datatype_identifier_c"); 
	return NULL;
}
void *generate_configuration_c::visit(         poutype_identifier_c *symbol) {
	TRACE("poutype_identifier_c"); 
	return strdup(symbol->value); 
}


/******************************/
/* B 1.2.1 - Numeric Literals */
/******************************/
void *generate_configuration_c::visit(real_c *symbol)               { 
  TRACE("real_c"); 
  return utility_token_get_c::return_striped_token(symbol);
}

void *generate_configuration_c::visit(integer_c *symbol)            { 
  TRACE("integer_c");
  return utility_token_get_c::return_striped_token(symbol);
}

void *generate_configuration_c::visit(binary_integer_c *symbol)     { 
  TRACE("binary_integer_c"); 
  return utility_token_get_c::return_striped_binary_token(symbol, 2);
}

void *generate_configuration_c::visit(octal_integer_c *symbol)      { 
	TRACE("octal_integer_c"); 
	return utility_token_get_c::return_striped_octal_token(symbol, 2);
}
void *generate_configuration_c::visit(hex_integer_c *symbol)        { 
	TRACE("hex_integer_c"); 
	return utility_token_get_c::return_striped_hex_token(symbol, 3);
}

void *generate_configuration_c::visit(neg_real_c *symbol)           { 
  TRACE("neg_real_c"); 
  std::string temp_str = "-";
  temp_str += (char*)utility_token_get_c::return_striped_token(dynamic_cast<token_c*>(symbol->exp));
  return strdup(temp_str.c_str());
}

void *generate_configuration_c::visit(neg_integer_c *symbol)        { 
  TRACE("neg_integer_c"); 
  std::string temp_str = "-";
  temp_str += (char*)utility_token_get_c::return_striped_token(dynamic_cast<token_c*>(symbol->exp));
  return strdup(temp_str.c_str());
}

void *generate_configuration_c::visit(integer_literal_c *symbol)    { 
  TRACE("integer_literal_c"); 
  return print_literal(symbol->type, symbol->value);
}
void *generate_configuration_c::visit(real_literal_c *symbol)       { 
	TRACE("real_literal_c"); 
	return print_literal(symbol->type, symbol->value);
}
void *generate_configuration_c::visit(bit_string_literal_c *symbol) { 
	TRACE("bit_string_literal_c"); 
	return print_literal(symbol->type, symbol->value);
}
void *generate_configuration_c::visit(boolean_literal_c *symbol)    { 
  TRACE("boolean_literal_c"); 
  if (NULL != symbol->type) {
    symbol->type->accept(*this);
  }
  return symbol->value->accept(*this);
}

/* helper class for boolean_literal_c */
void *generate_configuration_c::visit(boolean_true_c *symbol)       { 
  TRACE("boolean_true_c");  
  return strdup("1");
}
void *generate_configuration_c::visit(boolean_false_c *symbol)      { 
  TRACE("boolean_false_c");  
  return strdup("0");
}





/************************/
/* B 1.2.3.1 - Duration */
/************************/
void *generate_configuration_c::visit(neg_time_c *symbol) { TRACE("neg_time_c");  return NULL;}

void *generate_configuration_c::visit(duration_c *symbol) {
  TRACE("duration_c");
  if (symbol->neg != NULL)
    symbol->neg->accept(*this);
  
  return symbol->interval->accept(*this);
}

void *generate_configuration_c::visit(fixed_point_c *symbol) { TRACE("fixed_point_c"); return NULL;}

/* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
void *generate_configuration_c::generate_configuration_c::visit(interval_c *symbol) {
  TRACE("interval_c");
  std::string temp_str;
  int temp_ms = 0;
  int temp = 0;
  if (NULL != symbol->days) {
    temp = std::stoi((char*)symbol->days->accept(*this));
    temp_ms += temp * 24 * 60 * 60 * 1000;
  }

  if (NULL != symbol->hours) {
    temp = std::stoi((char*)symbol->hours->accept(*this));
    temp_ms += temp * 60 * 60 * 1000;
  }

  if (NULL != symbol->minutes) {
    temp = std::stoi((char*)symbol->minutes->accept(*this));
    temp_ms += temp * 60 * 1000;
  }

  if (NULL != symbol->seconds) {
    temp = std::stoi((char*)symbol->seconds->accept(*this));
    temp_ms += temp * 1000;
  }

  if (NULL != symbol->milliseconds) {
    temp = std::stoi((char*)symbol->milliseconds->accept(*this));
    temp_ms += temp;
  }
  temp_str = std::to_string(temp_ms);
  return strdup(temp_str.c_str());
}

/***********************************/
/* B 1.3.1 - Elementary Data Types */
/***********************************/
void *generate_configuration_c::visit(time_type_name_c *symbol)        {TRACE("time_type_name_c");  return strdup("TIME");}
void *generate_configuration_c::visit(bool_type_name_c *symbol)        {TRACE("bool_type_name_c");  return strdup("BOOL");}
void *generate_configuration_c::visit(sint_type_name_c *symbol)        {TRACE("sint_type_name_c");  return strdup("SINT");}
void *generate_configuration_c::visit(int_type_name_c *symbol)         {TRACE("int_type_name_c");  return strdup("INT");}
void *generate_configuration_c::visit(dint_type_name_c *symbol)        {TRACE("dint_type_name_c");   return strdup("DINT");}
void *generate_configuration_c::visit(lint_type_name_c *symbol)        {TRACE("lint_type_name_c");   return strdup("USINT");}
void *generate_configuration_c::visit(usint_type_name_c *symbol)       {TRACE("usint_type_name_c");   return strdup("USINT");}
void *generate_configuration_c::visit(uint_type_name_c *symbol)        {TRACE("uint_type_name_c");   return strdup("UINT");}
void *generate_configuration_c::visit(udint_type_name_c *symbol)       {TRACE("udint_type_name_c");   return strdup("UDINT");}
void *generate_configuration_c::visit(ulint_type_name_c *symbol)       {TRACE("ulint_type_name_c");   return strdup("ULINT");}
void *generate_configuration_c::visit(real_type_name_c *symbol)        {TRACE("real_type_name_c");   return strdup("REAL");}
void *generate_configuration_c::visit(lreal_type_name_c *symbol)       {TRACE("lreal_type_name_c");   return strdup("LREAL");}
void *generate_configuration_c::visit(date_type_name_c *symbol)        {TRACE("date_type_name_c");   return strdup("DATE");}
void *generate_configuration_c::visit(tod_type_name_c *symbol)         {TRACE("tod_type_name_c");    return strdup("TOD");}
void *generate_configuration_c::visit(dt_type_name_c *symbol)          {TRACE("dt_type_name_c");  return strdup("DT");}
void *generate_configuration_c::visit(byte_type_name_c *symbol)        {TRACE("byte_type_name_c");   return strdup("BYTE");}
void *generate_configuration_c::visit(word_type_name_c *symbol)        {TRACE("word_type_name_c"); return strdup("WORD");}
void *generate_configuration_c::visit(lword_type_name_c *symbol)       {TRACE("lword_type_name_c");  return strdup("LWORD");}
void *generate_configuration_c::visit(dword_type_name_c *symbol)       {TRACE("dword_type_name_c");   return strdup("DWORD");}
void *generate_configuration_c::visit(string_type_name_c *symbol)      {TRACE("string_type_name_c");  return strdup("STRING");}
void *generate_configuration_c::visit(wstring_type_name_c *symbol)     {TRACE("wstring_type_name_c");   return strdup("WSTRING");}



/*********************/
/* B 1.4 - Variables */
/*********************/
void *generate_configuration_c::visit(symbolic_variable_c *symbol) {
	TRACE("symbolic_variable_c"); 
	return symbol->var_name->accept(*this);
}
void *generate_configuration_c::visit(symbolic_constant_c *symbol) {
	TRACE("symbolic_constant_c"); 
	return symbol->var_name->accept(*this);
}
/********************************************/
/* B.1.4.1   Directly Represented Variables */
/********************************************/
void *generate_configuration_c::visit(direct_variable_c *symbol) {
	TRACE("direct_variable_c"); 
	return strdup(symbol->value);
}



/********************************/
/* B 1.7 Configuration elements */
/********************************/

/* intermediate helper symbol for configuration_declaration  */
/*  { global_var_declarations_list }   */
void *generate_configuration_c::visit(global_var_declarations_list_c *symbol) {
  TRACE("global_var_declarations_list_c"); 
  return print_list(symbol);
}

/*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
/* option -> may be NULL ! */
void *generate_configuration_c::visit(global_var_declarations_c *symbol) {
  TRACE("global_var_declarations_c");
  if (symbol->option != NULL)
    symbol->option->accept(*this);
  symbol->global_var_decl_list->accept(*this);
  return NULL;
}

/* helper symbol for global_var_declarations */
/*| global_var_decl_list global_var_decl ';' */
void *generate_configuration_c::visit(global_var_decl_list_c *symbol) {
  TRACE("global_var_decl_list_c");
  return print_list(symbol);
}


/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
/* type_specification ->may be NULL ! */
void *generate_configuration_c::visit(global_var_decl_c *symbol) {
  TRACE("global_var_decl_c");
  CP(111)
  symbol->global_var_spec->accept(*this);
  CP(222)
  if (symbol->type_specification != NULL)
    symbol->type_specification->accept(*this);

  if(typeid(*(symbol->global_var_spec)) == typeid(global_var_spec_c) ) {
    temp_global_var->type_value.type = var_type;
    if(var_type == TINT) {
      if (!var_value.empty())
        temp_global_var->type_value.v.value_i = std::stoi(var_value);
    }
    else if(var_type == TUINT) {
      if (!var_value.empty())
        temp_global_var->type_value.v.value_u = std::stoi(var_value);
    }
    else if(var_type == TDOUBLE) {
      if (!var_value.empty())
       temp_global_var->type_value.v.value_d = std::stod(var_value);
    }
    else {
      temp_global_var->type_value.v.value_s.str = strdup(var_value.c_str());
      temp_global_var->type_value.v.value_s.length = strlen(var_value.c_str());
    }
    temp_res_info->resource_global_dir_set.push_back(*temp_global_var);

    delete temp_global_var;
  } else if(typeid(*(symbol->global_var_spec)) == typeid(global_var_list_c) ) {
    for(auto elem : var_set) {
      temp_global_var = new global_var_value_c();

      temp_global_var->type_value.name = elem;
      temp_global_var->type_value.type = var_type;

      if(var_type == TINT) {
      if (!var_value.empty())
        temp_global_var->type_value.v.value_i = std::stoi(var_value);
      }
      else if(var_type == TUINT) {
      if (!var_value.empty())
        temp_global_var->type_value.v.value_u = std::stoi(var_value);
      }
      else if(var_type == TDOUBLE) {
      if (!var_value.empty())
        temp_global_var->type_value.v.value_d = std::stod(var_value);
      }
      else {
        temp_global_var->type_value.v.value_s.str = strdup(var_value.c_str());
        temp_global_var->type_value.v.value_s.length = strlen(var_value.c_str());
      }
      temp_res_info->resource_global_var_set.push_back(*temp_global_var);

      delete temp_global_var;
    }
  }

  var_type = -1;
  var_value = "";

  return NULL;
}

/*| global_var_name location */
void *generate_configuration_c::visit(global_var_spec_c *symbol) {
  TRACE("global_var_spec_c");
  temp_global_var = new global_var_value_c();
  temp_global_var->type_value.name = (char*)symbol->global_var_name->accept(*this);
  temp_global_var->location = (char*)symbol->location->accept(*this);
  return NULL;
}


/*  AT direct_variable */
void *generate_configuration_c::visit(location_c *symbol) {
  TRACE("location_c");
  
  return symbol->direct_variable->accept(*this);
}

/*| global_var_list ',' global_var_name */
void *generate_configuration_c::visit(global_var_list_c *symbol) {
  TRACE("global_var_list_c"); 
  std::string temp_str;
  for(int i = 0; i < symbol->n; i++) {
    temp_str = (char*)symbol->elements[i]->accept(*this);
    var_set.push_back(temp_str);
  }
  return NULL;
}


/* simple_specification ASSIGN constant */
void *generate_configuration_c::visit(simple_spec_init_c *symbol) {
  TRACE("simple_spec_init_c"); 
  var_type = utility_token_get_c::variable_type_check((char*)symbol->simple_specification->accept(*this));
  
  if (symbol->constant != NULL) {
    CP(333)
    var_value = (char*)symbol->constant->accept(*this);
    CP(444)
  }
  

  return NULL;
}

/* helper symbol for configuration_declaration */
/*| resource_declaration_list resource_declaration */
void *generate_configuration_c::visit(resource_declaration_list_c *symbol) {
	TRACE("resource_declaration_list_c"); 
	return print_list(symbol);
}


/*
RESOURCE resource_name ON resource_type_name
   optional_global_var_declarations
   single_resource_declaration
END_RESOURCE
*/
void *generate_configuration_c::visit(resource_declaration_c *symbol) {
  TRACE("resource_declaration_c"); 
  temp_res_info = new resource_info_c();

  temp_res_info->resource_name = (char*)symbol->resource_name->accept(*this);

  temp_res_info->resource_typename = (char*)symbol->resource_type_name->accept(*this);

  if (symbol->global_var_declarations != NULL)
    symbol->global_var_declarations->accept(*this);

  symbol->resource_declaration->accept(*this);

  pre_code_info_ptr->configuration_info.res_list_set.push_back(*temp_res_info);
  delete temp_res_info;

  return NULL;
}


/* task_configuration_list program_configuration_list */
void *generate_configuration_c::visit(single_resource_declaration_c *symbol) {
  TRACE("single_resource_declaration_c"); 
  symbol->task_configuration_list->accept(*this);
  symbol->program_configuration_list->accept(*this);
  return NULL;
}

/* helper symbol for single_resource_declaration */
/*| task_configuration_list task_configuration ';'*/
void *generate_configuration_c::visit(task_configuration_list_c *symbol) {
  TRACE("task_configuration_list_c"); 
  return print_list(symbol);
}


/* helper symbol for single_resource_declaration */
/*| program_configuration_list program_configuration ';'*/
void *generate_configuration_c::visit(program_configuration_list_c *symbol) {
  TRACE("program_configuration_list_c"); 
  return print_list(symbol);
}


/* helper symbol for
 *  - access_path
 *  - instance_specific_init
 */
/* | any_fb_name_list any_identifier '.'*/
void *generate_configuration_c::visit(any_fb_name_list_c *symbol) {
	TRACE("any_fb_name_list_c"); 
	return print_list(symbol);
}


/*  [resource_name '.'] global_var_name ['.' structure_element_name] */
void *generate_configuration_c::visit(global_var_reference_c *symbol) {
  TRACE("global_var_reference_c");
  if (symbol->resource_name != NULL) {
    symbol->resource_name->accept(*this);
  }
  symbol->global_var_name->accept(*this);
  if (symbol->structure_element_name != NULL) {
    symbol->structure_element_name->accept(*this);
  }
  return NULL;
}

/* program_name '.' symbolic_variable */
void *generate_configuration_c::visit(program_output_reference_c *symbol) {
  TRACE("program_output_reference_c");
  symbol->program_name->accept(*this);
  symbol->symbolic_variable->accept(*this);
  return NULL;
}

/*  TASK task_name task_initialization */
void *generate_configuration_c::visit(task_configuration_c *symbol) {
  TRACE("task_configuration_c");
  temp_task_info = new task_info_c();

  temp_task_info->task_name = (char*)symbol->task_name->accept(*this);
  symbol->task_initialization->accept(*this);

  temp_res_info->task_list_set.push_back(*temp_task_info);
  delete temp_task_info;

  return NULL;
}

/*  '(' [SINGLE ASSIGN data_source ','] [INTERVAL ASSIGN data_source ','] PRIORITY ASSIGN integer ')' */
void *generate_configuration_c::visit(task_initialization_c *symbol) {
  TRACE("task_initialization_c");

  if (symbol->single_data_source != NULL) {
  	if(typeid(*(symbol->single_data_source)) == typeid(global_var_reference_c)) {
    	temp_task_info->task_signal = (char*)dynamic_cast<global_var_reference_c*>(symbol->single_data_source)->global_var_name->accept(*this);
    	temp_task_info->task_is_signal = true;
    }
  }
  if (symbol->interval_data_source != NULL) {
    temp_task_info->task_interval = std::stoi((char*)symbol->interval_data_source->accept(*this));
  	temp_task_info->task_is_signal = false;
  }
  temp_task_info->task_priority = std::stoi((char*)symbol->priority_data_source->accept(*this));
  return NULL;

}

/*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
void *generate_configuration_c::visit(program_configuration_c *symbol) {
  TRACE("program_configuration_c");
  temp_program_info = new program_info_c();

  if (symbol->retain_option != NULL)
    symbol->retain_option->accept(*this);
  temp_program_info->program_name = (char*)symbol->program_name->accept(*this);
  if (symbol->task_name != NULL) {
  	temp_program_info->bind_task_name = (char*)symbol->task_name->accept(*this);
  }
  temp_program_info->program_instance_name = (char*)symbol->program_type_name->accept(*this);

  if (symbol->prog_conf_elements != NULL) {
    symbol->prog_conf_elements->accept(*this);
  }

  temp_res_info->program_list_set.push_back(*temp_program_info);
  delete temp_program_info;
  return NULL;
}


/* prog_conf_elements ',' prog_conf_element */
void *generate_configuration_c::visit(prog_conf_elements_c *symbol) {
	TRACE("prog_conf_elements_c"); 
	return print_list(symbol);
}

/*  fb_name WITH task_name */
void *generate_configuration_c::visit(fb_task_c *symbol) {
  TRACE("fb_task_c"); 
  symbol->fb_name->accept(*this);
  symbol->task_name->accept(*this);
  return NULL;
}

/*  any_symbolic_variable ASSIGN prog_data_source */
void *generate_configuration_c::visit(prog_cnxn_assign_c *symbol) {
  TRACE("prog_cnxn_assign_c"); 
  temp_program_arguement_info = new program_arguement_c();

  temp_program_arguement_info->key = (char*)symbol->symbolic_variable->accept(*this);

	if(typeid(*(symbol->prog_data_source)) == typeid(global_var_reference_c)) {
		temp_program_arguement_info->value = (char*)dynamic_cast<global_var_reference_c*>(symbol->prog_data_source)->global_var_name->accept(*this);
	} else {
		temp_program_arguement_info->value = (char*)symbol->prog_data_source->accept(*this);
	}

  temp_program_info->assign_arguement.push_back(*temp_program_arguement_info);
  delete temp_program_arguement_info;
  return NULL;
}

/* any_symbolic_variable SENDTO data_sink */
void *generate_configuration_c::visit(prog_cnxn_sendto_c *symbol) {
  TRACE("prog_cnxn_sendto_c"); 
  temp_program_arguement_info = new program_arguement_c();

  temp_program_arguement_info->key = (char*)symbol->symbolic_variable->accept(*this);

  if(typeid(*(symbol->data_sink)) == typeid(global_var_reference_c)) {
    	temp_program_arguement_info->value = (char*)dynamic_cast<global_var_reference_c*>(symbol->data_sink)->global_var_name->accept(*this);
  } else {
  	temp_program_arguement_info->value = (char*)symbol->data_sink->accept(*this);
  }

  temp_program_info->sendto_arguement.push_back(*temp_program_arguement_info);
  delete temp_program_arguement_info;
  return NULL;
}

/* VAR_CONFIG instance_specific_init_list END_VAR */
void *generate_configuration_c::visit(instance_specific_initializations_c *symbol) {
  TRACE("instance_specific_initializations_c"); 
  symbol->instance_specific_init_list->accept(*this);
  return NULL;
}

/* helper symbol for instance_specific_initializations */
/*| instance_specific_init_list instance_specific_init ';'*/
void *generate_configuration_c::visit(instance_specific_init_list_c *symbol) {
  TRACE("instance_specific_init_list_c"); 
  return print_list(symbol);
}

/* resource_name '.' program_name '.' optional_fb_name_list '.'
    ((variable_name [location] ':' located_var_spec_init) | (fb_name ':' fb_initialization))
*/
void *generate_configuration_c::visit(instance_specific_init_c *symbol) {
  TRACE("instance_specific_init_c"); 
  symbol->resource_name->accept(*this);
  symbol->program_name->accept(*this);
  symbol->any_fb_name_list->accept(*this);
  if (symbol->variable_name != NULL) {
    symbol->variable_name->accept(*this);
  }
  if (symbol->location != NULL) {
    symbol->location->accept(*this);
  }
  symbol->initialization->accept(*this);
  return NULL;
}

/* helper symbol for instance_specific_init */
/* function_block_type_name ':=' structure_initialization */
void *generate_configuration_c::visit(fb_initialization_c *symbol) {
  TRACE("fb_initialization_c"); 
  symbol->function_block_type_name->accept(*this);
  symbol->structure_initialization->accept(*this);
  return NULL;
}




