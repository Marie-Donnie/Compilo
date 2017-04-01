#ifndef PARSER_H
#define PARSER_H

#include "sets.h"
#include "definitions.h"
#include "hashmap.h"

/*------------------- ANALYZE -------------------------*/
extern char *code;

bool parse(Ptr* p);

/*------------------- ACTION -------------------------*/

void empiler(Ptr *pile, Ptr *T);
void depiler(Ptr *pile, Ptr *T);
void recherche(char *dico, char *atrouver);

void g0_action(int action);



#endif // PARSER_H
