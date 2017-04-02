#include "parser_GPL.h"

bool parse_GPL(Ptr *p){
  if (p->op_type == CONC){
    return parse_GPL(p->op.conc->left) && parse_GPL(p->op.conc->right);
  }
  else if (p->op_type == UNION){
    return parse_GPL(p->op.uni->left) || parse_GPL(p->op.uni->right);
  }
  else if (p->op_type == STAR){
    while (parse_GPL(p->op.star->stare)) {}
    return true;
  }
  else if (p->op_type == UN){
    if (parse_GPL(p->op.un->une)) {}
    return true;
  }
  else if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){

      printf("atom: %s token: %s\n", p->op.atom->code, scan_token()->type);

      if (!strcmp(p->op.atom->code, scan_token()->type)){
	if (p->op.atom->action != 0){
	  GPL_action(p->op.atom->action);
	}
	scan_GPL();
	return true;
      }
      else {
	return false;
      }
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      if (parse_GPL(get_rule_by_head(p->op.atom->code)->body)){
	if (p->op.atom->action != 0){
	  GPL_action(p->op.atom->action);
	}
	return true;
      }
      else {
	return false;
      }
    }
  }
  return false;
}

Vector *dic_var;
int spx_start;
Vector *stack;
Vector *p_code;

void GPL_action(int action){
  Token *t;
  int index;
  printf("action number: %d\n", action);
  switch(action){
  case 1:
    if (lookup_var(scan_token()->str) == -1){
      vector_push(dic_var, scan_token()->str);
      spx_start++;
    }
    break;
  case 2:
    t = scan_token();
    index = lookup_var(t->str);
    if (index == -1){
      fprintf(stderr, "Var %s has not been declared.\n", t->str);
      exit(3);
    }
    else {
      p_code_push(LDA);
      p_code_push(index);
    }
    break;
  case 3:
    p_code_push(AFF);
    break;
  case 4:
    t = scan_token();
    p_code_push(LDC);
    p_code_push(atoi(t->str));
    break;
  case 5:
    t = scan_token();
    stack_push(DIV);
    break;
  case 6:
    t = scan_token();
    stack_push(MULT);
    break;
  case 7:
    t = scan_token();
    stack_push(SUB);
    break;
  case 8:
    t = scan_token();
    stack_push(ADD);
    break;
  case 9:
    p_code_push(stack_pop());
    break;
  case 10:
    t = scan_token();
    stack_push(OR);
    break;
  case 11:
    t = scan_token();
    stack_push(AND);
    break;
  case 12:
    t = scan_token();
    stack_push(NOT);
    break;
  case 13:
    t = scan_token();
    stack_push(EQ);
    break;
  case 14:
    t = scan_token();
    stack_push(LT);
    break;
  case 15:
    t = scan_token();
    stack_push(GT);
    break;
  case 16:
    t = scan_token();
    stack_push(LEQ);
    break;
  case 17:
    t = scan_token();
    stack_push(GEQ);
    break;
  case 18:
    t = scan_token();
    stack_push(NEQ);
    break;
  case 19:
    p_code_push(JIF);
    p_code_push(0);
    stack_push(vector_length(p_code) - 1);
    break;
  case 20:
    p_code_push(JMP);
    p_code_push(0);
    index = stack_pop();
    p_code_set(index, vector_length(p_code));
    stack_push(vector_length(p_code) - 1);
    break;
  case 21:
    index = stack_pop();
    p_code_set(index, vector_length(p_code));
    break;
  case 22:
    stack_push(vector_length(p_code));
    break;
  case 23:
    p_code_push(JIF);
    p_code_push(0);
    stack_push(vector_length(p_code) - 1);
    break;
  case 24:
    // JIF argument address from #23
    index = stack_pop();
    p_code_set(index, vector_length(p_code) + 2);
    p_code_push(JMP);
    // Adress before booleanexp from #22
    p_code_push(stack_pop());
    break;
  case 25:
    p_code_push(1);
    break;
  case 26:
    p_code_push(0);
    break;
  case 27:
    p_code_push(STOP);
    break;
  case 28:
    t = scan_token();
    index = lookup_var(t->str);
    if (index == -1){
      fprintf(stderr, "Var %s has not been declared.\n", t->str);
      exit(3);
    }
    else {
      p_code_push(LDV);
      p_code_push(index);
    }
    break;
  case 29:
    p_code_push(READ);
    break;
  case 30:
    p_code_push(WRITE);
    break;
  }
}

void init_parse(){
  dic_var = empty_vector();
  spx_start = 0;
  stack = empty_vector();
  p_code = empty_vector();
}

int lookup_var(char *var){
  int i;
  for (i = 0 ; i < vector_length(dic_var) ; i++){
    if (!strcmp(vector_get(dic_var, i), var)){
      return i;
    }
  }
  return -1;

}

void p_code_push(int code){
  vector_push(p_code, gen_code(code));
}

int p_code_get(int index){
  Code *c = vector_get(p_code, index);
  return c->val;
}

void p_code_set(int index, int code){
  p_code->elts[index] = gen_code(code);
}

Code *gen_code(int code) {
  Code *c = check_malloc(sizeof(Code));
  c->val = code;
  return c;
}

void stack_push(int code){
  printf("%d code\n", code);
  vector_push(stack, gen_code(code));
}

int stack_get(int index){
  Code *c = vector_get(stack, index);
  return c->val;
}

int stack_pop(){
  Code *c = vector_pop(stack);
  return c->val;
}
