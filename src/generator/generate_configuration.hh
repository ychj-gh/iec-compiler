#ifndef __GENERATE_CONFIGURATION_C_HH__
#define __GENERATE_CONFIGURATION_C_HH__


#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include "generate_iec.hh"

#include "stage4.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.

//add by yaoshun
#include "pre_generate_info.hh"
#include "generate_assignment_r_exp.hh"
#include "generate_assignment_l_exp.hh"
#include "generate_pou_var_declaration.hh"
#include "utility_token_get.hh"
#include "utility_case_exp_value.hh"
#include "generate_pou_invocation.hh"


class generate_configuration_c : public null_visitor_c
{
private:
    pre_generate_pou_info_c* pou_info;
    pre_generate_info_c *pre_code_info_ptr;

    task_info_c *temp_task_info;
	resource_info_c *temp_res_info;
	program_info_c *temp_program_info;
	program_arguement_c *temp_program_arguement_info;
	global_var_value_c *temp_global_var;

	int var_type;
	std::string var_value;	
	std::vector<std::string> var_set;

public:
	generate_configuration_c(pre_generate_pou_info_c* pou_info_param, pre_generate_info_c *pre_code_info_param) {
    this->pou_info = pou_info_param;
    this->pre_code_info_ptr = pre_code_info_param;
  }
	~generate_configuration_c() {}

private:

	void *print_literal(symbol_c *type, symbol_c *value) ;

	void *print_list(list_c *list,
		       std::string pre_elem_str = "",
		       std::string inter_elem_str = "",
		       std::string post_elem_str = "");

	/*******************************************/
	/* B 1.1 - Letters, digits and identifiers */
	/*******************************************/
	void *visit(                 identifier_c *symbol) ;
	void *visit(derived_datatype_identifier_c *symbol) ;
	void *visit(         poutype_identifier_c *symbol) ;

	/******************************/
	/* B 1.2.1 - Numeric Literals */
	/******************************/
	void *visit(real_c *symbol) ;

	void *visit(integer_c *symbol) ;
	void *visit(binary_integer_c *symbol)     ;

	void *visit(octal_integer_c *symbol) ;

	void *visit(hex_integer_c *symbol) ;

	void *visit(neg_real_c *symbol) ;

	void *visit(neg_integer_c *symbol) ;
	void *visit(integer_literal_c *symbol)    ;

	void *visit(real_literal_c *symbol)      ;

	void *visit(bit_string_literal_c *symbol) ;
	void *visit(boolean_literal_c *symbol)    ;

	/* helper class for boolean_literal_c */
	void *visit(boolean_true_c *symbol)    ;   
	void *visit(boolean_false_c *symbol)      ;

	/************************/
	/* B 1.2.3.1 - Duration */
	/************************/
	void *visit(neg_time_c *symbol) ;

	void *visit(duration_c *symbol) ;

	void *visit(fixed_point_c *symbol) ;

	/* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
	void *visit(interval_c *symbol) ;

	/***********************************/
	/* B 1.3.1 - Elementary Data Types */
	/***********************************/
	void *visit(time_type_name_c *symbol)        ;
	void *visit(bool_type_name_c *symbol)        ;
	void *visit(sint_type_name_c *symbol)        ;
	void *visit(int_type_name_c *symbol)         ;
	void *visit(dint_type_name_c *symbol)        ;
	void *visit(lint_type_name_c *symbol)        ;
	void *visit(usint_type_name_c *symbol)       ;
	void *visit(uint_type_name_c *symbol)        ;
	void *visit(udint_type_name_c *symbol)       ;
	void *visit(ulint_type_name_c *symbol)       ;
	void *visit(real_type_name_c *symbol)        ;
	void *visit(lreal_type_name_c *symbol)       ;
	void *visit(date_type_name_c *symbol)        ;
	void *visit(tod_type_name_c *symbol)         ;
	void *visit(dt_type_name_c *symbol)          ;
	void *visit(byte_type_name_c *symbol)        ;
	void *visit(word_type_name_c *symbol)        ;
	void *visit(lword_type_name_c *symbol)       ;
	void *visit(dword_type_name_c *symbol)       ;
	void *visit(string_type_name_c *symbol)      ;
	void *visit(wstring_type_name_c *symbol)     ;

		

	/*********************/
	/* B 1.4 - Variables */
	/*********************/
	void *visit(symbolic_variable_c *symbol) ;
	void *visit(symbolic_constant_c *symbol) ;

	/********************************************/
	/* B.1.4.1   Directly Represented Variables */
	/********************************************/
	void *visit(direct_variable_c *symbol) ;


	/********************************/
	/* B 1.7 Configuration elements */
	/********************************/
	/* intermediate helper symbol for configuration_declaration  */
	/*  { global_var_declarations_list }   */
	void *visit(global_var_declarations_list_c *symbol) ;

	/*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
	/* option -> may be NULL ! */
	void *visit(global_var_declarations_c *symbol) ;

	/* helper symbol for global_var_declarations */
	/*| global_var_decl_list global_var_decl ';' */
	void *visit(global_var_decl_list_c *symbol) ;

	/*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
	/* type_specification ->may be NULL ! */
	void *visit(global_var_decl_c *symbol);

	/*| global_var_name location */
	void *visit(global_var_spec_c *symbol) ;

	/*| global_var_list ',' global_var_name */
	void *visit(global_var_list_c *symbol) ;

	/* simple_specification ASSIGN constant */
	void *visit(simple_spec_init_c *symbol) ;

	/* helper symbol for configuration_declaration */
	/*| resource_declaration_list resource_declaration */
	void *visit(resource_declaration_list_c *symbol) ;

	/*
	RESOURCE resource_name ON resource_type_name
	   optional_global_var_declarations
	   single_resource_declaration
	END_RESOURCE
	*/
	void *visit(resource_declaration_c *symbol) ;


	/* task_configuration_list program_configuration_list */
	void *visit(single_resource_declaration_c *symbol) ;

	/* helper symbol for single_resource_declaration */
	/*| task_configuration_list task_configuration ';'*/
	void *visit(task_configuration_list_c *symbol) ;

	/* helper symbol for single_resource_declaration */
	/*| program_configuration_list program_configuration ';'*/
	void *visit(program_configuration_list_c *symbol) ;


	/* helper symbol for
	 *  - access_path
	 *  - instance_specific_init
	 */
	/* | any_fb_name_list any_identifier '.'*/
	void *visit(any_fb_name_list_c *symbol) ;


	/*  [resource_name '.'] global_var_name ['.' structure_element_name] */
	void *visit(global_var_reference_c *symbol) ;

	/* program_name '.' symbolic_variable */
	void *visit(program_output_reference_c *symbol) ;

	
	/*  TASK task_name task_initialization */
	void *visit(task_configuration_c *symbol) ;

	/*  '(' [SINGLE ASSIGN data_source ','] [INTERVAL ASSIGN data_source ','] PRIORITY ASSIGN integer ')' */
	void *visit(task_initialization_c *symbol) ;

	/*  PROGRAM [RETAIN | NON_RETAIN] program_name [WITH task_name] ':' program_type_name ['(' prog_conf_elements ')'] */
	void *visit(program_configuration_c *symbol) ;


	/* prog_conf_elements ',' prog_conf_element */
	void *visit(prog_conf_elements_c *symbol) ;

	/*  fb_name WITH task_name */
	void *visit(fb_task_c *symbol) ;

	/*  any_symbolic_variable ASSIGN prog_data_source */
	void *visit(prog_cnxn_assign_c *symbol) ;

	/* any_symbolic_variable SENDTO data_sink */
	void *visit(prog_cnxn_sendto_c *symbol) ;

	/* VAR_CONFIG instance_specific_init_list END_VAR */
	void *visit(instance_specific_initializations_c *symbol) ;

	/* helper symbol for instance_specific_initializations */
	/*| instance_specific_init_list instance_specific_init ';'*/
	void *visit(instance_specific_init_list_c *symbol) ;

	/* resource_name '.' program_name '.' optional_fb_name_list '.'
	    ((variable_name [location] ':' located_var_spec_init) | (fb_name ':' fb_initialization))
	*/
	void *visit(instance_specific_init_c *symbol) ;

	/* helper symbol for instance_specific_init */
	/* function_block_type_name ':=' structure_initialization */
	void *visit(fb_initialization_c *symbol) ;

	/*  AT direct_variable */
	void *visit(location_c *symbol);




	
};




#endif