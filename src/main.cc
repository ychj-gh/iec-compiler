/**
 The compiler works in 4(+1) stages:
 Stage 1   - Lexical analyser      - implemented with flex (iec.flex)
 Stage 2   - Syntax parser         - implemented with bison (iec.y)
 Stage 3   - Semantics analyser    - not yet implemented
 Stage 4   - Code generator        - implemented in C++
 Stage 4+1 - Binary code generator - gcc, javac, etc...


 Data structures passed between stages, in global variables:
 1->2   : tokens (int), and token values (char *)
 2->1   : symbol tables (defined in symtable.hh)
 2->3   : abstract syntax tree (tree of C++ classes, in absyntax.hh file)
 3->4   : Same as 2->3
 4->4+1 : file with program in c, java, etc...


 The compiler works in several passes:
 Pass 1: executes stages 1 and 2 simultaneously
 Pass 2: executes stage 3
 Pass 3: executes stage 4
 Pass 4: executes stage 4+1
*/



#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>


#include "absyntax/absyntax.hh"
#include "absyntax_utils/absyntax_utils.hh"
#include "parser/stage1_2.hh"
// #include "semantics/stage3.hh"
#include "generator/stage4.hh"
#include "main.hh"




void error_exit(const char *file_name, int line_no, const char *errmsg, ...) {
  va_list argptr;
  va_start(argptr, errmsg); /* second argument is last fixed pamater of error_exit() */

  fprintf(stderr, "\nInternal compiler error in file %s at line %d", file_name, line_no);
  if (errmsg != NULL) {
    fprintf(stderr, ": ");
    vfprintf(stderr, errmsg, argptr);
  } else {
    fprintf(stderr, ".");
  }
  fprintf(stderr, "\n");
  va_end(argptr);
    
  exit(EXIT_FAILURE);
}


runtime_options_t runtime_options;

int main(int argc, char **argv) {
  symbol_c *tree_root, *ordered_tree_root;
  char * builddir = NULL;

  if (argc < 2) {
    printf("error: need more arguments !\n");
    exit(EXIT_FAILURE);
  }
  CP(0);
  runtime_options.pre_parsing = true;
  /* lexer and parser process */
  if (stage1_2(argv[1], &tree_root) < 0)
    return EXIT_FAILURE;
  CP(1);
  /* basically loads some symbol tables to speed up look ups later on */
  absyntax_utils_init(tree_root);  
  CP(2)
  /* semantics analysis */
  // if (stage3(tree_root, &ordered_tree_root) < 0)
  //   return EXIT_FAILURE;
  CP(3);
  /* code generator */
  if (stage4(tree_root, builddir) < 0)
    return EXIT_FAILURE;
  CP(4);
  
  return 0;
}


