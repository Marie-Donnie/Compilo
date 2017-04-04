#ifndef PARSER_GPL_H
#define PARSER_GPL_H

#include "definitions.h"
#include "lexer_G0.h"
#include "lexer_GPL.h"


extern Vector *p_code;
extern int spx_start;

typedef enum {
  LDA,
  LDC,
  LDV,
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
  JMP,
  READ,
  WRITE,
  WRITELN,
  STOP
} Opcode;

typedef struct {
  int val;
} Code;


bool parse_GPL(Ptr* p);

void GPL_action(int action);

void init_parse();

int lookup_var(char *var);

void p_code_push(int code);
void p_code_set(int index, int code);
int p_code_get(int index);
Code *gen_code(int code);

void stack_push(int code);
int stack_get(int index);
int stack_pop();

#endif //PARSER_GPL_H
