#ifndef SETS_H
#define SETS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lexer.h"


typedef struct {
  Token **set;
  size_t size;
  size_t nb_elem;
} Set;

Set* empty_set();
void set_add(Set *set, void *e);
bool set_is_member(const Set *set, const void *e);
void set_union(Set *set1, const Set *set2);

#endif // SETS_H
