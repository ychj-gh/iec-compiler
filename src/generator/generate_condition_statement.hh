#ifndef __GENERATE_CONDITION_STATEMENT_HH__
#define __GENERATE_CONDITION_STATEMENT_HH__


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
#include "generate_assignment_r_exp.hh"


class generate_conditon_statement_c : public null_visitor_c {
private:
    pre_generate_pou_info_c *pou_info;

public:
	generate_conditon_statement_c(pre_generate_pou_info_c* pou_info_param) : pou_info(pou_info_param) {
	}
	~generate_conditon_statement_c(void) {} ;

private:

	/********************************/
	/*       utility function       */
	/********************************/
	void *print_list(list_c *list,
			       std::string pre_elem_str = "",
			       std::string inter_elem_str = "",
			       std::string post_elem_str = "") ;

	/********************************/
	/* B 3.2.3 Selection Statements */
	/********************************/
	void *visit(if_statement_c *symbol) ;

	/* helper symbol for if_statement */
	void *visit(elseif_statement_list_c *symbol) ;

	/* helper symbol for elseif_statement_list */
	void *visit(elseif_statement_c *symbol) ;



};

#endif