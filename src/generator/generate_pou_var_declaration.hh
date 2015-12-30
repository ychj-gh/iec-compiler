#ifndef __GENERATE_POU_VAR_DECLARATION_HH__
#define __GENERATE_POU_VAR_DECLARATION_HH__

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






class generate_pou_var_declaration_c: public null_visitor_c {
private:
    pre_generate_pou_info_c* pou_info;

public:
  generate_pou_var_declaration_c(pre_generate_pou_info_c* pou_info_parm) {
    this->pou_info = pou_info_parm;
  }
  ~generate_pou_var_declaration_c(void) {}

private:
  std::string var_value;
  std::string var_type;
  std::vector<std::string> var_name_set;
  internal_value_t ivt;

private:

  void *print_token(token_c *token) ;

  void *print_literal(symbol_c *type, symbol_c *value) ;
  void *print_list(list_c *list,
  			       std::string pre_elem_str = "",
  			       std::string inter_elem_str = "",
  			       std::string post_elem_str = "") ;


  void *print_binary_expression(symbol_c *symbol,
  			      symbol_c *l_exp,
  			      symbol_c *r_exp,
  			      const char *operation) ;

  void *print_unary_expression(symbol_c *symbol,
  			     symbol_c *exp,
  			     const char *operation) ;



public:



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
  void *visit(ref_value_null_literal_c *symbol)  ;

  /******************************/
  /* B 1.2.1 - Numeric Literals */
  /******************************/
  void *visit(real_c *symbol)               ;
  void *visit(integer_c *symbol)            ;
  void *visit(binary_integer_c *symbol)     ;

  void *visit(octal_integer_c *symbol)      ;
  void *visit(hex_integer_c *symbol)        ;

  void *visit(neg_real_c *symbol)           ;
  void *visit(neg_integer_c *symbol)        ;

  void *visit(integer_literal_c *symbol)    ;
  void *visit(real_literal_c *symbol)       ;
  void *visit(bit_string_literal_c *symbol) ;
  void *visit(boolean_literal_c *symbol)    ;

  /* helper class for boolean_literal_c */
  void *visit(boolean_true_c *symbol)       ;
  void *visit(boolean_false_c *symbol)      ;

  /*******************************/
  /* B.1.2.2   Character Strings */
  /*******************************/
  void *visit(double_byte_character_string_c *symbol) ;
  void *visit(single_byte_character_string_c *symbol) ;


  
  /***********************************/
  /* B 1.3.1 - Elementary Data Types */
  /***********************************/
  void *visit(time_type_name_c *symbol);
  void *visit(bool_type_name_c *symbol);
  void *visit(sint_type_name_c *symbol);
  void *visit(int_type_name_c *symbol);
  void *visit(dint_type_name_c *symbol);
  void *visit(lint_type_name_c *symbol);
  void *visit(usint_type_name_c *symbol);
  void *visit(uint_type_name_c *symbol);
  void *visit(udint_type_name_c *symbol);
  void *visit(ulint_type_name_c *symbol);
  void *visit(real_type_name_c *symbol);
  void *visit(lreal_type_name_c *symbol);
  void *visit(date_type_name_c *symbol);
  void *visit(tod_type_name_c *symbol);
  void *visit(dt_type_name_c *symbol);
  void *visit(byte_type_name_c *symbol);
  void *visit(word_type_name_c *symbol);
  void *visit(lword_type_name_c *symbol);
  void *visit(dword_type_name_c *symbol);
  void *visit(string_type_name_c *symbol);
  void *visit(wstring_type_name_c *symbol);

  /********************************/
  /* B.1.3.2 - Generic data types */
  /********************************/
  void *visit(generic_type_any_c      *symbol);

  /********************************/
  /* B 1.3.3 - Derived data types */
  /********************************/
  /*  TYPE type_declaration_list END_TYPE */
  void *visit(data_type_declaration_c *symbol) ;


  /* helper symbol for data_type_declaration */
  /*| type_declaration_list type_declaration ';' */
  void *visit(type_declaration_list_c *symbol) ;

  /*  simple_type_name ':' simple_spec_init */
  void *visit(simple_type_declaration_c *symbol) ;


  /* simple_specification ASSIGN constant */
  void *visit(simple_spec_init_c *symbol) ;




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


  /******************************************/
  /* B 1.4.3 - Declaration & Initialisation */
  /******************************************/
  void *visit(constant_option_c *symbol) ;
  void *visit(retain_option_c *symbol) ;
  void *visit(non_retain_option_c *symbol);

  /* VAR_INPUT [RETAIN | NON_RETAIN] input_declaration_list END_VAR */
  /* option -> the RETAIN/NON_RETAIN/<NULL> directive... */
  void *visit(input_declarations_c *symbol) ;

  /* helper symbol for input_declarations */
  /*| input_declaration_list input_declaration ';' */
  void *visit(input_declaration_list_c *symbol) ;
  /* edge -> The F_EDGE or R_EDGE directive */
  void *visit(edge_declaration_c *symbol) ;

  /* dummy classes only used as flags! */
  void *visit(explicit_definition_c *symbol) ;
  void *visit(implicit_definition_c *symbol) ;

  /* EN : BOOL := 1 */
  void *visit(en_param_declaration_c *symbol) ;

  /* ENO : BOOL */
  void *visit(eno_param_declaration_c *symbol) ;

  void *visit(raising_edge_option_c *symbol) ;

  void *visit(falling_edge_option_c *symbol) ;


  /* var1_list is one of the following...
   *    simple_spec_init_c *
   *    subrange_spec_init_c *
   *    enumerated_spec_init_c *
   */

  void *visit(var1_init_decl_c *symbol) ;

  void *visit(var1_list_c *symbol) ;


  /* VAR_OUTPUT [RETAIN | NON_RETAIN] var_init_decl_list END_VAR */
  /* option -> may be NULL ! */
  void *visit(output_declarations_c *symbol) ;

  /*  VAR_IN_OUT  END_VAR */
  void *visit(input_output_declarations_c *symbol) ;

  /* helper symbol for input_output_declarations */
/* var_declaration_list var_declaration ';' */
  void *visit(var_declaration_list_c *symbol) ;

  /* VAR [CONSTANT] var_init_decl_list END_VAR */
  /* option -> may be NULL ! */
  void *visit(var_declarations_c *symbol) ;

  /*  VAR RETAIN var_init_decl_list END_VAR */
  void *visit(retentive_var_declarations_c *symbol) ;

  /*  VAR [CONSTANT|RETAIN|NON_RETAIN] located_var_decl_list END_VAR */
  /* option -> may be NULL ! */
  void *visit(located_var_declarations_c *symbol) ;
  /* helper symbol for located_var_declarations */
  /* located_var_decl_list located_var_decl ';' */
  void *visit(located_var_decl_list_c *symbol) ;

  /*  [variable_name] location ':' located_var_spec_init */
  /* variable_name -> may be NULL ! */
  void *visit(located_var_decl_c *symbol) ;

  /*| VAR_EXTERNAL [CONSTANT] external_declaration_list END_VAR */
  /* option -> may be NULL ! */
  void *visit(external_var_declarations_c *symbol) ;

  /* helper symbol for external_var_declarations */
  /*| external_declaration_list external_declaration';' */
  void *visit(external_declaration_list_c *symbol) ;
  /*  global_var_name ':' (simple_specification|subrange_specification|enumerated_specification|array_specification|prev_declared_structure_type_name|function_block_type_name) */
  void *visit(external_declaration_c *symbol) ;

  /*| VAR_GLOBAL [CONSTANT|RETAIN] global_var_decl_list END_VAR */
  /* option -> may be NULL ! */
  void *visit(global_var_declarations_c *symbol) ;
  /* helper symbol for global_var_declarations */
  /*| global_var_decl_list global_var_decl ';' */
  void *visit(global_var_decl_list_c *symbol) ;

  /*| global_var_spec ':' [located_var_spec_init|function_block_type_name] */
  /* type_specification ->may be NULL ! */
  void *visit(global_var_decl_c *symbol) ;

  /*| global_var_name location */
  void *visit(global_var_spec_c *symbol) ;

  /*  AT direct_variable */
  void *visit(location_c *symbol) ;

  /*| global_var_list ',' global_var_name */
  void *visit(global_var_list_c *symbol) ;



  /*| VAR [RETAIN|NON_RETAIN] incompl_located_var_decl_list END_VAR */
  /* option ->may be NULL ! */
  void *visit(incompl_located_var_declarations_c *symbol) ;

  /* helper symbol for incompl_located_var_declarations */
  /*| incompl_located_var_decl_list incompl_located_var_decl ';' */
  void *visit(incompl_located_var_decl_list_c *symbol) ;
  /*  variable_name incompl_location ':' var_spec */
  void *visit(incompl_located_var_decl_c *symbol) ;


  /*  AT incompl_location_token */
  void *visit(incompl_location_c *symbol) ;


  /* intermediate helper symbol for:
   *  - non_retentive_var_decls
   *  - output_declarations
   */
  /* | var_init_decl_list var_init_decl ';' */
  void *visit(var_init_decl_list_c *symbol) ;

  /***********************/
  /* B 1.5.1 - Functions */
  /***********************/
  /* intermediate helper symbol for function_declaration */
  void *visit(var_declarations_list_c *symbol) ;

  void *visit(function_var_decls_c *symbol) ;

  /* intermediate helper symbol for function_var_decls */
  void *visit(var2_init_decl_list_c *symbol) ;

  /*****************************/
  /* B 1.5.2 - Function Blocks */
  /*****************************/
  /*  VAR_TEMP temp_var_decl_list END_VAR */
  void *visit(temp_var_decls_c *symbol) ;

  /* intermediate helper symbol for temp_var_decls */
  void *visit(temp_var_decls_list_c *symbol) ;

  /*  VAR NON_RETAIN var_init_decl_list END_VAR */
  void *visit(non_retentive_var_decls_c *symbol) ;






}; /* class generate_var_declaration */




#endif












