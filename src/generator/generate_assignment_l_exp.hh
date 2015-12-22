#ifndef __GENERATE_ASSIGNMENT_L_EXP_HH__
#define __GENERATE_ASSIGNMENT_L_EXP_HH__


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
#include "utility_token_get.hh"


class generate_assign_l_exp_c : public null_visitor_c {
private:
    pre_generate_pou_info_c *pou_info;

public:
	generate_assign_l_exp_c(pre_generate_pou_info_c* pou_info_param) {
		this->pou_info = pou_info_param;
	}
	~generate_assign_l_exp_c(void) {} ;

private:

	/*******************************************/
	/* B 1.1 - Letters, digits and identifiers */
	/*******************************************/
	void *visit(                 identifier_c *symbol) ;
	void *visit(derived_datatype_identifier_c *symbol) ;
	void *visit(         poutype_identifier_c *symbol) ;


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


};








#endif

