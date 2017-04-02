#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser_GPL.h"
#include <unistd.h>

#define MAX_BUF_SIZE 256

void interpret();

void print_p_code();


void pilex_push(int code);

void pilex_set(int index, int code);

int pilex_pop();
int pilex_get(int index);

void print_pilex();

#endif //INTERPRETER_H
