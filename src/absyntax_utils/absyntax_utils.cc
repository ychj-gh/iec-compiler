/*
 * This is the main stage 3a file.
 *
 * In stage 3a some helpful symbol tables are instanciated and populated.
 * These symbol tables wll then be used by stage3b and atage4 code generators.
 */






// #include <stdio.h>  /* required for NULL */
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <list>
#include <strings.h>


#include "../util/symtable.hh"
#include "../util/dsymtable.hh"
#include "../absyntax/visitor.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.



//#define DEBUG
#ifdef DEBUG
#define TRACE(classname) printf("\n____%s____\n",classname);
#else
#define TRACE(classname)
#endif



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


/* returns 0 if the names are equal!! */
/* NOTE: it must ignore case!! */
int compare_identifiers(symbol_c *ident1, symbol_c *ident2) {

  token_c *name1 = dynamic_cast<token_c *>(ident1);
  token_c *name2 = dynamic_cast<token_c *>(ident2);
  
  if ((name1 == NULL) || (name2 == NULL))
    /* invalid identifiers... */
    return -1;

  if (strcasecmp(name1->value, name2->value) == 0)
    return 0;

  /* identifiers do not match! */
  return 1;
}



/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/



/* A symbol table with all globally declared functions... */
dsymtable_c<function_declaration_c *> function_symtable;

/* A symbol table with all globally declared functions block types... */
symtable_c<function_block_declaration_c *> function_block_type_symtable;

/* A symbol table with all globally declared program types... */
symtable_c<program_declaration_c *> program_type_symtable;

/* A symbol table with all user declared type definitions... */
/* Note that function block types and program types have their
 * own symbol tables, so do not get placed in this symbol table!
 *
 * The symbol_c * associated to the value will point to the data type declaration.
 */
symtable_c<symbol_c *> type_symtable;


/***********************************************************************/
/***********************************************************************/
/***********************************************************************/
/***********************************************************************/


class populate_symtables_c: public iterator_visitor_c {

  private:
	symbol_c *current_enumerated_type;

  public:
    populate_symtables_c(void) {
    	current_enumerated_type = NULL;
    };
    virtual ~populate_symtables_c(void) {}


  public:

  /*************************/
  /* B.1 - Common elements */
  /*************************/
  /*******************************************/
  /* B 1.1 - Letters, digits and identifiers */
  /*******************************************/
  /*********************/
  /* B 1.2 - Constants */
  /*********************/
  /******************************/
  /* B 1.2.1 - Numeric Literals */
  /******************************/
  /*******************************/
  /* B.1.2.2   Character Strings */
  /*******************************/
  /***************************/
  /* B 1.2.3 - Time Literals */
  /***************************/
  /************************/
  /* B 1.2.3.1 - Duration */
  /************************/
  /************************************/
  /* B 1.2.3.2 - Time of day and Date */
  /************************************/
  /**********************/
  /* B.1.3 - Data types */
  /**********************/
  /***********************************/
  /* B 1.3.1 - Elementary Data Types */
  /***********************************/
  /********************************/
  /* B.1.3.2 - Generic data types */
  /********************************/
  /********************************/
  /* B 1.3.3 - Derived data types */
  /********************************/

  /*  subrange_type_name ':' subrange_spec_init */
  void *visit(subrange_type_declaration_c *symbol) {type_symtable.insert(symbol->subrange_type_name, symbol->subrange_spec_init); return NULL;}

  /*  enumerated_type_name ':' enumerated_spec_init */
  void *visit(enumerated_type_declaration_c *symbol) {
    type_symtable.insert(symbol->enumerated_type_name, symbol);
    current_enumerated_type = symbol->enumerated_type_name;
    symbol->enumerated_spec_init->accept(*this);
    current_enumerated_type = NULL;
    return NULL;
  }

  /* enumerated_specification ASSIGN enumerated_value */
  void *visit(enumerated_spec_init_c *symbol) {return symbol->enumerated_specification->accept(*this);}
  /*  identifier ':' array_spec_init */
  void *visit(array_type_declaration_c *symbol) {type_symtable.insert(symbol->identifier, symbol->array_spec_init); return NULL;}
  /*  simple_type_name ':' simple_spec_init */
  void *visit(simple_type_declaration_c *symbol) {type_symtable.insert(symbol->simple_type_name, symbol->simple_spec_init); return NULL;}
  /*  structure_type_name ':' structure_specification */
  void *visit(structure_type_declaration_c *symbol) {type_symtable.insert(symbol->structure_type_name, symbol->structure_specification); return NULL;}
  /*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
  void *visit(string_type_declaration_c *symbol) {type_symtable.insert(symbol->string_type_name, symbol); return NULL;}
  /* identifier ':' ref_spec_init */
  void *visit(ref_type_decl_c *symbol) {type_symtable.insert(symbol->ref_type_name, symbol); return NULL;}

  /*********************/
  /* B 1.4 - Variables */
  /*********************/
  /********************************************/
  /* B.1.4.1   Directly Represented Variables */
  /********************************************/
  /*************************************/
  /* B.1.4.2   Multi-element Variables */
  /*************************************/
  /******************************************/
  /* B 1.4.3 - Declaration & Initialisation */
  /******************************************/
  /**************************************/
  /* B.1.5 - Program organization units */
  /**************************************/
  /***********************/
  /* B 1.5.1 - Functions */
  /***********************/
  public:
  /*   FUNCTION derived_function_name ':' elementary_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
  /* | FUNCTION derived_function_name ':' derived_type_name io_OR_function_var_declarations_list function_body END_FUNCTION */
  void *visit(function_declaration_c *symbol) {
    TRACE("function_declaration_c");
    function_symtable.insert(symbol->derived_function_name, symbol);
  
    /* symbol->derived_function_name->accept(*this);  */ /* Function name */
    /* symbol->type_name->accept(*this);              */ /* return data type */
    /* symbol->var_declarations_list->accept(*this);  */ /* Function parameters and variables */
    /* symbol->function_body->accept(*this);          */ /* Function body */
    return NULL;
  }
  

  /*****************************/
  /* B 1.5.2 - Function Blocks */
  /*****************************/
  public:
  /*  FUNCTION_BLOCK derived_function_block_name io_OR_other_var_declarations function_block_body END_FUNCTION_BLOCK */
  //SYM_REF4(function_block_declaration_c, fblock_name, var_declarations, fblock_body, unused)
  void *visit(function_block_declaration_c *symbol) {
    TRACE("function_block_declaration_c");
    function_block_type_symtable.insert(symbol->fblock_name, symbol);
  /*
    symbol->fblock_name->accept(*this);
    symbol->var_declarations->accept(*this);
    symbol->fblock_body->accept(*this);
  */
    return NULL;
  }
  
  
  /**********************/
  /* B 1.5.3 - Programs */
  /**********************/
  public:
  /*  PROGRAM program_type_name program_var_declarations_list function_block_body END_PROGRAM */
  //SYM_REF4(program_declaration_c, program_type_name, var_declarations, function_block_body, unused)
  void *visit(program_declaration_c *symbol) {
    TRACE("program_declaration_c");
    program_type_symtable.insert(symbol->program_type_name, symbol);
  /*
    symbol->program_type_name->accept(*this);
    symbol->var_declarations->accept(*this);
    symbol->function_block_body->accept(*this);
  */
    return NULL;
  }
  
}; /* populate_symtables_c */





void absyntax_utils_init(symbol_c *tree_root) {
  populate_symtables_c populate_symbols;

  tree_root->accept(populate_symbols);
  function_symtable.print();
  function_block_type_symtable.print();
  program_type_symtable.print();
  type_symtable.print();
}

