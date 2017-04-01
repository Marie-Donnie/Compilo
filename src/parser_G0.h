#ifndef PARSER_H
#define PARSER_H

#include "definitions.h"
#include "lexer_G0.h"

/*------------------- ANALYZE -------------------------*/

bool parse(Ptr* p);


void g0_action(int action);

void push(Ptr *p);
Ptr* pop();
void lookup(char *elt);
void init_stack();

#endif // PARSER_H
