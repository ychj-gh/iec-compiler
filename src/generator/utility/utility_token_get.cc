#include "utility_token_get.hh"


/*******************************************/
/* ************ utility functions ******** */
/*******************************************/

std::string utility_token_get_c::numeric_to_string(int num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

std::string utility_token_get_c::numeric_to_string(double num) {
  std::stringstream strm;
  std::string result;
  strm << num;
  strm >> result;
  return result;
}

void *utility_token_get_c::return_token(token_c *token) {
  return strdup(token->value);
}

void *utility_token_get_c::return_striped_token(token_c *token, int offset) {
  std::string str = "";
  bool leading_zero = true;
  for (unsigned int i = offset; i < strlen(token->value); i++) {
    if (leading_zero
        && (   token->value[i] != '0'
            || i == strlen(token->value) - 1
            || token->value[i + 1] == '.'
            )
        )
      leading_zero = false;
        if (!leading_zero && token->value[i] != '_')
      str += token->value[i];
  }
  return strdup(str.c_str());
}

void *utility_token_get_c::return_striped_binary_token(token_c *token, unsigned int offset) {
  /* convert the binary value to decimal format... */
  unsigned long val = 0;
  unsigned int i;
  
  for (i = offset; i < strlen(token->value); i++) {
    if (token->value[i] != '_') {
      if(token->value[i] == '1')
        val = val * 2 + 1;
      else
        val = val * 2;
    }
  }

  std::stringstream stream;
  std::string result;
  stream << val; 
  stream >> result; 

  return strdup(result.c_str());
}

void *utility_token_get_c::return_striped_octal_token(token_c *token, unsigned int offset) {
  /* convert the octal value to decimal format... */
  unsigned long val = 0;
  unsigned int i;
  
  for (i = offset; i < strlen(token->value); i++) {
    if (token->value[i] != '_') {
      switch(token->value[i])
      {
        case '0':
          val = val * 8;
          break;
        case '1':
          val = val * 8 + 1;
          break;
        case '2':
          val = val * 8 + 2;
          break;
        case '3':
          val = val * 8 + 3;
          break;
        case '4':
          val = val * 8 + 4;
          break;
        case '5':
          val = val * 8 + 5;
          break;
        case '6':
          val = val * 8 + 6;
          break;
        case '7':
          val = val * 8 + 7;
          break;
        default:
          break;
      }
    }
  }

  std::stringstream stream;
  std::string result;
  stream << val; 
  stream >> result; 

  return strdup(result.c_str());
}


void *utility_token_get_c::return_striped_hex_token(token_c *token, unsigned int offset) {
  /* convert the hex value to decimal format... */
  unsigned long val = 0;
  unsigned int i;
  
  for (i = offset; i < strlen(token->value); i++) {
    if (token->value[i] != '_') {
      switch(token->value[i])
      {
        case '0':
          val = val * 16;
          break;
        case '1':
          val = val * 16 + 1;
          break;
        case '2':
          val = val * 16 + 2;
          break;
        case '3':
          val = val * 16 + 3;
          break;
        case '4':
          val = val * 16 + 4;
          break;
        case '5':
          val = val * 16 + 5;
          break;
        case '6':
          val = val * 16 + 6;
          break;
        case '7':
          val = val * 16 + 7;
          break;
        case '8':
          val = val * 16 + 8;
          break;
        case '9':
          val = val * 16 + 9;
          break;
        case 'A':
        case 'a':
          val = val * 16 + 10;
          break;
        case 'B':
        case 'b':
          val = val * 16 + 11;
          break;
        case 'C':
        case 'c':
          val = val * 16 + 12;
          break;
        case 'D':
        case 'd':
          val = val * 16 + 13;
          break;
        case 'E':
        case 'e':
          val = val * 16 + 14;
          break;
        case 'F':
        case 'f':
          val = val * 16 + 15;
          break;
        default:
          break;
      }
    }
  }

  std::stringstream stream;
  std::string result;
  stream << val; 
  stream >> result; 

  return strdup(result.c_str());
}



internal_value_t utility_token_get_c::variable_type_check(std::string type)
{
  if(type == "SINT" || type == "INT" || type == "DINT" || type == "LINT")
    return TINT;
  else if(type == "USINT" || type == "UINT" || type == "UDINT" || type == "ULINT" 
    || type == "BYTE" || type == "WORD" || type == "LWORD" || type == "DWORD" || type == "BOOL")
    return TUINT;
  else if(type == "REAL" || type == "LREAL")
    return TDOUBLE;
  else if(type == "STRING" || type == "WSTRING")
    return TSTRING;
  else
    return TUNDEF;
  
}

