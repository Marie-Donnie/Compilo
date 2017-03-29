#ifndef SETS_H
#define SETS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lexer.h"
#include "general_func.h"


typedef struct {
  void **set;
  size_t size;
} Set;

Set* empty_set();
bool set_is_member(Set *set, void *e);
Set* set_add(Set *set, void *e);
Set* set_union(Set *set1, Set *set2);
Set* set_remove(Set *set, void *e);

extern bool set_is_equal(void *a, void *b);

#endif // SETS_H
