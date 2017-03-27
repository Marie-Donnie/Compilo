#ifndef GENERAL_FUNC_H
#define GENERAL_FUNC_H

#include <stdbool.h>
#include <stdio.h>

long char_count(FILE *file);
char* read_file(char *path);

void eat_space();

bool might_be_double(char c);
bool is_double(char c, char cc);

/*------------------- SCAN -------------------------*/
void scan(char* chaine);

#endif //GENERAL_FUNC_H
