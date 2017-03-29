#ifndef SETS_H
#define SETS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lexer.h"
#include "general_func.h"


typedef struct {
  const void **set;
  size_t size;
} Set;

Set* empty_set();
bool set_is_member(const Set *set, const void *e);
const Set* set_add(const Set *set, const void *e);
const Set* set_union(const Set *set1, const Set *set2);
const Set* set_remove(const Set *set, const void *e);

extern bool set_is_equal(const void *a, const void *b);

#endif // SETS_H
