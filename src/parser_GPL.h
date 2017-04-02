#ifndef PARSER_GPL_H
#define PARSER_GPL_H

#include "definitions.h"
#include "lexer_G0.h"
#include "lexer_GPL.h"


extern Vector *p_code;

typedef enum {
  LDA,
  LDC,
  AFF,
  ADD,
  SUB,
  MULT,
  DIV,
  OR,
  AND,
  NOT,
  EQ,
  LT,
  GT,
  LEQ,
  GEQ,
  NEQ,
  JIF,
  JUMP

} Opcode;

typedef struct {
  int val;
} Code;


bool parse_GPL(Ptr* p);

void GPL_action(int action);

void init_parse();

int lookup_var(char *var);

void p_code_push(int code);

int p_code_get(int index);
Code *gen_code(int code);

void stack_push(int code);
int stack_get(int index);
int stack_pop();

#endif //PARSER_GPL_H
