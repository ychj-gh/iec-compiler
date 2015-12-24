#ifndef __UTILITY_TOKEN_GET_HH__
#define __UTILITY_TOKEN_GET_HH__

#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <vector>
#include "generate_iec.hh"

#include "stage4.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.

#include "pre_generate_info.hh"


class utility_token_get_c {
public:
	/*******************************************/
	/* ************ utility functions ******** */
	/*******************************************/

	static std::string numeric_to_string(int num) ;

	static std::string numeric_to_string(double num) ;

	static void *return_token(token_c *token) ;

	static void *return_striped_token(token_c *token, int offset = 0) ;

	static void *return_striped_binary_token(token_c *token, unsigned int offset = 0) ;
	static void *return_striped_octal_token(token_c *token, unsigned int offset = 0) ;
	static void *return_striped_hex_token(token_c *token, unsigned int offset = 0) ;
};




#endif