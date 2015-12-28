#include "generate_condition_statement.hh"





/********************************/
/*       utility function       */
/********************************/
void *generate_conditon_statement_c::print_list(list_c *list,
			       std::string pre_elem_str ,
			       std::string inter_elem_str ,
			       std::string post_elem_str ) {

  for(int i = 0; i < list->n; i++) {
    list->elements[i]->accept(*this);
  }

  return NULL;
}

/********************************/
/* B 3.2.3 Selection Statements */
/********************************/
void *generate_conditon_statement_c::visit(if_statement_c *symbol) {
  TRACE("if_statement_c"); 

  symbol->expression->accept(*this);
  symbol->statement_list->accept(*this);
  symbol->elseif_statement_list->accept(*this);

  if (symbol->else_statement_list != NULL) {
    symbol->else_statement_list->accept(*this);
  }
  return NULL;
}

/* helper symbol for if_statement */
void *generate_conditon_statement_c::visit(elseif_statement_list_c *symbol) {
	TRACE("elseif_statement_list_c"); 
	return print_list(symbol);
}

/* helper symbol for elseif_statement_list */
void *generate_conditon_statement_c::visit(elseif_statement_c *symbol) {
  TRACE("elseif_statement_c"); 
  symbol->expression->accept(*this);
  symbol->statement_list->accept(*this);
  return NULL;
}