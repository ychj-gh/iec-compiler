/*
 * A generic symbol table.
 *
 * This is used to create symbol tables such as a list of
 * variables currently in scope, etc...
 * Note that the list of previously defined funstions uses the
 * dsymtable_c instead, as it requires the table to store duplicate values.
 */


#include <iostream>
#include "symtable.hh"
#include "../main.hh" // required for ERROR() and ERROR_MSG() macros.






template<typename value_type>
symtable_c<value_type>::symtable_c(void) {inner_scope = NULL;}


 /* clear all entries... */
template<typename value_type>
void symtable_c<value_type>::clear(void) {
  _base.clear();
}

 /* create new inner scope */
template<typename value_type>
void symtable_c<value_type>::push(void) {
  if (inner_scope != NULL) {
    inner_scope->push();
  } else {
    inner_scope = new symtable_c();
  }
}

  /* clear most inner scope */
  /* returns 1 if this is the inner most scope	*/
  /*         0 otherwise			*/
template<typename value_type>
int symtable_c<value_type>::pop(void) {
  if (inner_scope != NULL) {
    if (inner_scope->pop() == 1) {
      delete inner_scope;
      inner_scope = NULL;
    }
    return 0;
  } else {
    _base.clear();
    return 1;
  }
}

template<typename value_type>
void symtable_c<value_type>::set(const symbol_c *symbol, value_t new_value) {
  if (inner_scope != NULL) {
    inner_scope->set(symbol, new_value);
    return;
  }

  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  set(name->value, new_value);
}


template<typename value_type>
void symtable_c<value_type>::set(const char *identifier_str, value_t new_value) {
  if (inner_scope != NULL) {
    inner_scope->set(identifier_str, new_value);
    return;
  }

  // std::cout << "set_identifier(" << identifier_str << "): \n";
  iterator i = _base.find(identifier_str);
  if (i == _base.end())
    /* identifier not already in map! */
    ERROR;

  _base[identifier_str] = new_value;
}

template<typename value_type>
void symtable_c<value_type>::insert(const char *identifier_str, value_t new_value) {
  if (inner_scope != NULL) {
    inner_scope->insert(identifier_str, new_value);
    return;
  }

  // std::cout << "store_identifier(" << identifier_str << "): \n";
  iterator i = _base.find(identifier_str);
  if ((i != _base.end()) && (i->second != new_value)) {ERROR;}  /* error inserting new identifier: identifier already in map associated to a different value */
  if ((i != _base.end()) && (i->second == new_value)) {return;} /* identifier already in map associated with the same value */

  std::pair<const char *, value_t> new_element(identifier_str, new_value);
  std::pair<iterator, bool> res = _base.insert(new_element);
  if (!res.second) {ERROR;} /* unknown error inserting new identifier */
}

template<typename value_type>
void symtable_c<value_type>::insert(const symbol_c *symbol, value_t new_value) {
/*
// not required...
  if (inner_scope != NULL) {
    inner_scope->insert(symbol, new_value);
    return;
  }
*/
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  insert(name->value, new_value);
}


template<typename value_type>
int symtable_c<value_type>::count(const       char *identifier_str) {return _base.count(identifier_str)+((inner_scope == NULL)?0:inner_scope->count(identifier_str));}
template<typename value_type>
int symtable_c<value_type>::count(const std::string identifier_str) {return _base.count(identifier_str)+((inner_scope == NULL)?0:inner_scope->count(identifier_str));}


// in the operator[] we delegate to find(), since that method will also search in the inner scopes!
template<typename value_type>
typename symtable_c<value_type>::value_t& symtable_c<value_type>::operator[] (const       char *identifier_str) {iterator i = find(identifier_str); return (i!=end())?i->second:_base[identifier_str];}
template<typename value_type>
typename symtable_c<value_type>::value_t& symtable_c<value_type>::operator[] (const std::string identifier_str) {iterator i = find(identifier_str); return (i!=end())?i->second:_base[identifier_str];}


template<typename value_type>
typename symtable_c<value_type>::iterator symtable_c<value_type>::end  (void) {return _base.end  ();}

template<typename value_type>
typename symtable_c<value_type>::iterator symtable_c<value_type>::begin(void) {return _base.begin();}

/* returns end() if not found! */
template<typename value_type>
typename symtable_c<value_type>::iterator symtable_c<value_type>::find(const       char *identifier_str) {
  iterator i;
  if ((inner_scope != NULL) && ((i = inner_scope->find(identifier_str)) != inner_scope->end()))  // NOTE: must use the end() value of the inner scope!
      return i;  // found in the lower level
  /* if no lower level, or not found in lower level... */
  return _base.find(identifier_str);
}


template<typename value_type>
typename symtable_c<value_type>::iterator symtable_c<value_type>::find(const std::string identifier_str) {
  iterator i;
  if ((inner_scope != NULL) && ((i = inner_scope->find(identifier_str)) != inner_scope->end()))  // NOTE: must use the end() value of the inner scope!
      return i;  // found in the lower level
  /* if no lower level, or not found in lower level... */
  return _base.find(identifier_str);
}


template<typename value_type>
typename symtable_c<value_type>::iterator symtable_c<value_type>::find(const   symbol_c *symbol) {
  const token_c *name = dynamic_cast<const token_c *>(symbol);
  if (name == NULL)
    ERROR;
  return find(name->value);
}



/* debuging function... */
template<typename value_type>
void symtable_c<value_type>::print(void) {
  for(iterator i = _base.begin();
      i != _base.end();
      i++)
    std::cout << i->second << ":" << i->first << "\n";
  std::cout << "=====================\n";

  if (inner_scope != NULL) {
    inner_scope->print();
  }
}








