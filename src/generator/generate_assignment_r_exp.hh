#ifndef __GENERATE_ASSIGNMENT_STATEMENT_R_EXP_HH__
#define __GENERATE_ASSIGNMENT_STATEMENT_R_EXP_HH__


#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>

#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.
#include "stage4.hh"


#include "pre_generate_info.hh"
#include "../absyntax/visitor.hh"


class generate_assign_r_exp_c : public null_visitor_c {
private:
    pre_generate_pou_info_c *pou_info;

public:
	generate_assign_r_exp_c(pre_generate_pou_info_c* pou_info_param) {
		this->pou_info = pou_info_param;
	}
	~generate_assign_r_exp_c(void) {} ;

private:

	std::string numeric_to_string(int num) ;

	std::string numeric_to_string(double num);

	void *return_token(token_c *token) ;

	void *return_striped_token(token_c *token, int offset = 0);

	void *return_striped_binary_token(token_c *token, unsigned int offset = 0);

	void *return_striped_octal_token(token_c *token, unsigned int offset = 0);

	void *return_striped_hex_token(token_c *token, unsigned int offset = 0);

	/*******************************************/
	/* B 1.1 - Letters, digits and identifiers */
	/*******************************************/
	void *visit(                 identifier_c *symbol) ;
	void *visit(derived_datatype_identifier_c *symbol) ;
	void *visit(         poutype_identifier_c *symbol) ;


	/*********************/
	/* B 1.2 - Constants */
	/*********************/
	/*********************************/
	/* B 1.2.XX - Reference Literals */
	/*********************************/
	/* defined in IEC 61131-3 v3 - Basically the 'NULL' keyword! */
	void *visit(ref_value_null_literal_c *symbol);
	/******************************/
	/* B 1.2.1 - Numeric Literals */
	/******************************/
	void *visit(real_c *symbol);
	void *visit(integer_c *symbol);
	void *visit(binary_integer_c *symbol);

	void *visit(octal_integer_c *symbol) ;
	void *visit(hex_integer_c *symbol);

	void *visit(neg_real_c *symbol);
	void *visit(neg_integer_c *symbol);

	void *visit(integer_literal_c *symbol);
	void *visit(real_literal_c *symbol) ;
	void *visit(bit_string_literal_c *symbol);
	void *visit(boolean_literal_c *symbol);

	/* helper class for boolean_literal_c */
	void *visit(boolean_true_c *symbol);
	void *visit(boolean_false_c *symbol);

	/*******************************/
	/* B.1.2.2   Character Strings */
	/*******************************/
	void *visit(double_byte_character_string_c *symbol);
	void *visit(single_byte_character_string_c *symbol);


	/***************************/
	/* B 1.2.3 - Time Literals */
	/***************************/

	/************************/
	/* B 1.2.3.1 - Duration */
	/************************/
	void *visit(neg_time_c *symbol);

	void *visit(duration_c *symbol);

	void *visit(fixed_point_c *symbol) ;

	/* SYM_REF5(interval_c, days, hours, minutes, seconds, milliseconds) */
	void *visit(interval_c *symbol) ;

	/************************************/
	/* B 1.2.3.2 - Time of day and Date */
	/************************************/

	void *visit(time_of_day_c *symbol) ;

	void *visit(daytime_c *symbol) ;

	void *visit(date_c *symbol) ;

	void *visit(date_literal_c *symbol) ;

	void *visit(date_and_time_c *symbol) ;


	/*********************/
	/* B 1.4 - Variables */
	/*********************/
	void *visit(symbolic_variable_c *symbol) ;
	void *visit(symbolic_constant_c *symbol) ;

	/********************************************/
	/* B.1.4.1   Directly Represented Variables */
	/********************************************/
	void *visit(direct_variable_c *symbol) ;

	/*************************************/
	/* B.1.4.2   Multi-element Variables */
	/*************************************/
	/*  subscripted_variable '[' subscript_list ']' */
	void *visit(array_variable_c *symbol) ;

	/* subscript_list ',' subscript */
	void *visit(subscript_list_c *symbol) ;

	/*  record_variable '.' field_selector */
	void *visit(structured_variable_c *symbol) ;

	/***********************/
	/* B 3.1 - Expressions */
	/***********************/
	void *visit( add_expression_c *symbol);

	void *visit(   sub_expression_c *symbol);

	void *visit(   mul_expression_c *symbol);

	void *visit(   div_expression_c *symbol);

	void *visit(   equ_expression_c *symbol) ;
	void *visit(notequ_expression_c *symbol) ;
	void *visit(    lt_expression_c *symbol) ;
	void *visit(    gt_expression_c *symbol) ;
	void *visit(    le_expression_c *symbol) ;
	void *visit(    ge_expression_c *symbol) ;

	void *visit(    or_expression_c *symbol) ;
	void *visit(   xor_expression_c *symbol) ;
	void *visit(   and_expression_c *symbol) ;
	void *visit(   not_expression_c *symbol) ;



};








#endif

