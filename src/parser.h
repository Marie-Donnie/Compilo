#ifndef PARSER_H
#define PARSER_H

#include "sets.h"
#include "definitions.h"
#include "hashmap.h"


const Set* first(char *head);
const Set* first_ptr(Ptr *p);
const Set* follow(char *head);
const Set* set_union_eps(const Set *set1, const Set *set2);
Ptr* get_production(char *code);
bool is_equal(char *ter1, char *ter2);
int index_of(char *ter, Vector *v);

#endif // PARSER_H
