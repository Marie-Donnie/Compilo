#ifndef PARSER_H
#define PARSER_H

#include "sets.h"
#include "definitions.h"
#include "hashmap.h"

extern map_t *parsing_table;

Set *first_str(Vector *prod, int start, Vector *G);
Set* first(char *symbol, Vector *G);
Set* first_ptr(Ptr *p, Vector *G);
Set* follow(char *head, Vector *G);
Set* follow_normalized(char *head);
Set* set_union_eps(Set *set1, Set *set2);
Ptr* get_production(char *code);
bool is_equal(char *ter1, char *ter2);
int index_of(char *ter, Vector *v);
void reset_cache();


/*------------------- PARSING_TABLE -------------------------*/

void init_parsing_table(Vector *G);
void parsing_table_put(char *head, char *ter, Rule *r);
Rule* parsing_table_get(char *head, char *ter);

/*------------------- PARSE -------------------------*/

void parse(char *input);
bool is_terminal(char *sym);
bool is_same(char *sym, Token *t);


#endif // PARSER_H
