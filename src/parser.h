#ifndef PARSER_H
#define PARSER_H

#include "sets.h"
#include "definitions.h"



const Set* first(Ptr *p);
Set* follow(Ptr *p);
const Set* set_union_eps(const Set *set1, const Set *set2);
Ptr* get_production(char *code);
void print_set(const Set *set);

#endif // PARSER_H
