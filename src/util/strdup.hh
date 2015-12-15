#ifndef STRDUP__H
#define STRDUP__H

#include <stdlib.h>   /* required for malloc() */
#include <string.h>   /* required for strcat() & strlen() */

/*
 * Join two strings together. Allocate space with malloc(3).
 */
static char *strdup2(const char *a, const char *b) {
  char *res = (char *)malloc(strlen(a) + strlen(b) + 1);

  if (res == NULL) return NULL;
  return strcat(strcpy(res, a), b);
}

/*
 * Join three strings together. Allocate space with malloc(3).
 */
static char *strdup3(const char *a, const char *b, const char *c) {
  char *res = (char *)malloc(strlen(a) + strlen(b) + strlen(c) + 1);

  if (res == NULL) return NULL;
  return strcat(strcat(strcpy(res, a), b), c);
}


#endif /* STRDUP__H */
