#ifndef _SYMTABLE_HH
#define _SYMTABLE_HH

#include "../absyntax/absyntax.hh"

#include <map>
#include <string>




template<typename value_type> class symtable_c {
  /* Case insensitive string compare copied from
   * "The C++ Programming Language" - 3rd Edition
   * by Bjarne Stroustrup, ISBN 0201889544.
   */
  class nocase_c {
    public:
      bool operator() (const std::string& x, const std::string& y) const {
        std::string::const_iterator ix = x.begin();
        std::string::const_iterator iy = y.begin();

        for(; (ix != x.end()) && (iy != y.end()) && (toupper(*ix) == toupper(*iy)); ++ix, ++iy);
        if (ix == x.end()) return (iy != y.end());
        if (iy == y.end()) return false;
        return (toupper(*ix) < toupper(*iy));
      };
  };

  public:
    typedef value_type value_t;

  private:
    /* Comparison between identifiers must ignore case, therefore the use of nocase_c */
    typedef std::map<std::string, value_t, nocase_c> base_t;
    base_t _base;

  public:
  typedef typename base_t::iterator iterator;
  typedef typename base_t::const_iterator const_iterator;
  typedef typename base_t::reverse_iterator reverse_iterator;
  typedef typename base_t::const_reverse_iterator const_reverse_iterator;

  private:
      /* pointer to symbol table of the next inner scope */
    symtable_c *inner_scope;

  public:
    symtable_c(void);

    void clear(void); /* clear all entries... */

    void push(void); /* create new inner scope */
    int  pop(void);  /* clear most inner scope */

    void set(const char *identifier_str, value_t value);    // Will change value associated to string if already in map. Will create new entry if string not in map.
    void set(const symbol_c *symbol, value_t value);        // Will change value associated to string if already in map. Will create new entry if string not in map.
    void insert(const char *identifier_str, value_t value); // insert a new (string,value) pair. Give an error if string already in map associated to different value!
    void insert(const symbol_c *symbol, value_t value);     // insert a new (string,value) pair. Give an error if string already in map associated to different value!

    value_t& operator[](const       char *identifier_str);
    value_t& operator[](const std::string identifier_str);
 // value_t& operator[](const   symbol_c *identifier    ); // not yet implemented
   
    /* Since symtable_c does not allow duplicates in each level, count() will return
     *  - 0 : if not found in any level
     *  - n : number of level containing that entry (max is current number of levels!)
     */
    int count(const       char *identifier_str);
    int count(const std::string identifier_str);
 // int count(const   symbol_c *identifier    ); // not yet implemented
    
    /* Search for an entry. Will return end() if not found */
    iterator               begin(void);
    iterator               end  (void);
    iterator               find (const char       *identifier_str);
    iterator               find (const std::string identifier_str);
    iterator               find (const symbol_c   *symbol        );

    /* debuging function... */
    void print(void);
};



/* Templates must include the source into the code! */
#include "symtable.cc"

#endif /*  _SYMTABLE_HH */
