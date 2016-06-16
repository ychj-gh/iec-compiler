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

	static internal_value_t variable_type_check(std::string type);

	////字符串分割函数
	static std::vector<std::string> split(std::string str,std::string pattern)
	{
		  std::string::size_type pos;
		  std::vector<std::string> result;
		  std::vector<std::string> realresult;
		  str += pattern;//扩展字符串以方便操作
		  int size=str.size();

		  for(int i = 0; i < size; i ++)
		  {
			    pos = str.find(pattern, i);
			    if(pos < size)
			    {
				      std::string s = str.substr(i, pos - i);
				      result.push_back(s);
				      i = pos+pattern.size() - 1;
			    }
		  }
		  for(auto elem : result) {
			  	if(!elem.empty()){
			  		realresult.push_back(elem);
			  	}
		  }
		  return realresult;
	}
};




#endif
