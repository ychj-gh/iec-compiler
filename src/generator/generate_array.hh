#ifndef __GENERATE_ARRAY_HH__
#define __GENERATE_ARRAY_HH__

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

class generate_array_c : public null_visitor_c{
private:
    array_type_c *array_type;

    std::string var_value;
    std::string var_type;

public:
    generate_array_c(array_type_c *array_type_param){
        this->array_type = array_type_param;
    }
    ~generate_array_c() {};

    void *print_token(token_c *token) {
    //   print_const_value(token);
      return strdup(token->value);
    }

    void *print_literal(symbol_c *type, symbol_c *value) {
    //   print_const_value(value);
      if (NULL != type) {
        type->accept(*this);
      }
      return value->accept(*this);

    }

    void *print_list(list_c *list,
    			       std::string pre_elem_str = "",
    			       std::string inter_elem_str = "",
    			       std::string post_elem_str = "") {

      for(int i = 0; i < list->n; i++) {
        list->elements[i]->accept(*this);
      }

      return NULL;
    }


    void *print_binary_expression(symbol_c *symbol,
    			      symbol_c *l_exp,
    			      symbol_c *r_exp,
    			      const char *operation) {
    //   print_const_value(symbol);
      l_exp->accept(*this);
      r_exp->accept(*this);
      return NULL;
    }

    void *print_unary_expression(symbol_c *symbol,
    			     symbol_c *exp,
    			     const char *operation) {
    //   print_const_value(symbol);
      std::string str = std::string(operation) + std::string((char*)exp->accept(*this)) ;
      return strdup(str.c_str());
    }

private:

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


    /***************************/
    /* B 1.2.3 - Time Literals */
    /***************************/

    /************************/
    /* B 1.2.3.1 - Duration */
    /************************/
    void *visit(neg_time_c *symbol) ;

    void *visit(duration_c *symbol) ;

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

    void *visit(safetime_type_name_c *symbol)    ;
    void *visit(safebool_type_name_c *symbol)    ;
    void *visit(safesint_type_name_c *symbol)    ;
    void *visit(safeint_type_name_c *symbol)     ;
    void *visit(safedint_type_name_c *symbol)    ;
    void *visit(safelint_type_name_c *symbol)    ;
    void *visit(safeusint_type_name_c *symbol)   ;
    void *visit(safeuint_type_name_c *symbol)    ;
    void *visit(safeudint_type_name_c *symbol)   ;
    void *visit(safeulint_type_name_c *symbol)   ;
    void *visit(safereal_type_name_c *symbol)    ;
    void *visit(safelreal_type_name_c *symbol)   ;
    void *visit(safedate_type_name_c *symbol)    ;
    void *visit(safetod_type_name_c *symbol)     ;
    void *visit(safedt_type_name_c *symbol)      ;
    void *visit(safebyte_type_name_c *symbol)    ;
    void *visit(safeword_type_name_c *symbol)    ;
    void *visit(safelword_type_name_c *symbol)   ;
    void *visit(safedword_type_name_c *symbol)   ;
    void *visit(safestring_type_name_c *symbol)  ;
    void *visit(safewstring_type_name_c *symbol) ;

    /********************************/
    /* B.1.3.2 - Generic data types */
    /********************************/
    void *visit(generic_type_any_c      *symbol) ;

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

    /*  subrange_type_name ':' subrange_spec_init */
    void *visit(subrange_type_declaration_c *symbol) ;

    /* subrange_specification ASSIGN signed_integer */
    void *visit(subrange_spec_init_c *symbol) ;

    /*  integer_type_name '(' subrange')' */
    void *visit(subrange_specification_c *symbol) ;

    /*  signed_integer DOTDOT signed_integer */
    void *visit(subrange_c *symbol) ;

    /*  enumerated_type_name ':' enumerated_spec_init */
    void *visit(enumerated_type_declaration_c *symbol) ;

    /* enumerated_specification ASSIGN enumerated_value */
    void *visit(enumerated_spec_init_c *symbol) ;

    /* helper symbol for enumerated_specification->enumerated_spec_init */
    /* enumerated_value_list ',' enumerated_value */
    void *visit(enumerated_value_list_c *symbol) ;

    /* enumerated_type_name '#' identifier */
    void *visit(enumerated_value_c *symbol) ;

    /*  identifier ':' array_spec_init */
    void *visit(array_type_declaration_c *symbol) ;

    /* array_specification [ASSIGN array_initialization} */
    /* array_initialization may be NULL ! */
    void *visit(array_spec_init_c *symbol) ;

    /* ARRAY '[' array_subrange_list ']' OF non_generic_type_name */
    void *visit(array_specification_c *symbol) ;

    /* helper symbol for array_specification */
    /* array_subrange_list ',' subrange */
    void *visit(array_subrange_list_c *symbol) ;

    /* helper symbol for array_initialization */
    /* array_initial_elements_list ',' array_initial_elements */
    void *visit(array_initial_elements_list_c *symbol) ;

    /* integer '(' [array_initial_element] ')' */
    /* array_initial_element may be NULL ! */
    void *visit(array_initial_elements_c *symbol) ;

    /*  structure_type_name ':' structure_specification */
    void *visit(structure_type_declaration_c *symbol) ;

    /* structure_type_name ASSIGN structure_initialization */
    /* structure_initialization may be NULL ! */
    void *visit(initialized_structure_c *symbol) ;

    /* helper symbol for structure_declaration */
    /* structure_declaration:  STRUCT structure_element_declaration_list END_STRUCT */
    /* structure_element_declaration_list structure_element_declaration ';' */
    void *visit(structure_element_declaration_list_c *symbol) ;

    /*  structure_element_name ':' *_spec_init */
    void *visit(structure_element_declaration_c *symbol) ;

    /* helper symbol for structure_initialization */
    /* structure_initialization: '(' structure_element_initialization_list ')' */
    /* structure_element_initialization_list ',' structure_element_initialization */
    void *visit(structure_element_initialization_list_c *symbol) ;

    /*  structure_element_name ASSIGN value */
    void *visit(structure_element_initialization_c *symbol) ;

    /*  string_type_name ':' elementary_string_type_name string_type_declaration_size string_type_declaration_init */
    void *visit(string_type_declaration_c *symbol) ;

    /*  function_block_type_name ASSIGN structure_initialization */
    /* structure_initialization -> may be NULL ! */
    void *visit(fb_spec_init_c *symbol) ;



    /* ref_spec:  REF_TO (non_generic_type_name | function_block_type_name) */
    // SYM_REF1(ref_spec_c, type_name)
    void *visit(ref_spec_c *symbol) ;

    /* For the moment, we do not support initialising reference data types */
    /* ref_spec_init: ref_spec [ ASSIGN ref_initialization ]; */
    /* NOTE: ref_initialization may be NULL!! */
    // SYM_REF2(ref_spec_init_c, ref_spec, ref_initialization)
    void *visit(ref_spec_init_c *symbol) ;

    /* ref_type_decl: identifier ':' ref_spec_init */
    // SYM_REF2(ref_type_decl_c, ref_type_name, ref_spec_init)
    void *visit(ref_type_decl_c *symbol) ;


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
