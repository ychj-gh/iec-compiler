#ifndef _GENERATE_POU_INVOCATION_HH__
#define _GENERATE_POU_INVOCATION_HH__



#include <stdio.h>  /* required for NULL */
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
#include "utility_token_get.hh"






class generate_pou_invocation_c: public null_visitor_c {
private:
    pre_generate_pou_info_c* pou_info;

public:
  generate_pou_invocation_c(pre_generate_pou_info_c* pou_info_parm) {
    this->pou_info = pou_info_parm;
  }
  ~generate_pou_invocation_c(void) {}

private:

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

	/*********************/
	/* B 1.4 - Variables */
	/*********************/
	void *visit(symbolic_variable_c *symbol) ;
	void *visit(symbolic_constant_c *symbol) ;

	/********************************************/
	/* B.1.4.1   Directly Represented Variables */
	/********************************************/
	void *visit(direct_variable_c *symbol) ;

	/***********************/
	/* B 3.1 - Expressions */
	/***********************/

	/* arithmetic expressions */
	void *visit( add_expression_c *symbol) ;

	void *visit(   sub_expression_c *symbol) ;

	void *visit(   mul_expression_c *symbol) ;

	void *visit(   div_expression_c *symbol) ;

	/* comparison expressions */
	void *visit(   equ_expression_c *symbol) ;
	void *visit(notequ_expression_c *symbol) ;
	void *visit(    lt_expression_c *symbol) ;
	void *visit(    gt_expression_c *symbol) ;
	void *visit(    le_expression_c *symbol) ;
	void *visit(    ge_expression_c *symbol) ;

	/* logical expressions */
	void *visit(    or_expression_c *symbol) ;

	void *visit(   xor_expression_c *symbol) ;
	void *visit(   and_expression_c *symbol) ;

	void *visit(   not_expression_c *symbol) ;


	/*****************************************/
	/* B 3.2.2 Subprogram Control Statements */
	/*****************************************/

	/*  RETURN */
	void *visit(return_statement_c *symbol) ;

	/* helper symbol for fb_invocation */
	/* param_assignment_list ',' param_assignment */
	void *visit(param_assignment_list_c *symbol) ;

	void *visit(input_variable_param_assignment_c *symbol) ;

	void *visit(output_variable_param_assignment_c *symbol) ;

	void *visit(not_paramassign_c *symbol) ;








};




#endif