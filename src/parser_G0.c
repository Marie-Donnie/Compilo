#include "parser_G0.h"
#include <assert.h>



/*------------------- PARSE -------------------------*/


bool parse(Ptr *p){
  if (p->op_type == CONC){
    return parse(p->op.conc->left) && parse(p->op.conc->right);
  }
  else if (p->op_type == UNION){
    return parse(p->op.uni->left) || parse(p->op.uni->right);
  }
  else if (p->op_type == STAR){
    while (parse(p->op.star->stare)) {}
    return true;
  }
  else if (p->op_type == UN){
    if (parse(p->op.un->une)) {}
    return true;
  }
  else if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){
      if (!strcmp(p->op.atom->code, scan_token()->type)){
	if (p->op.atom->action != 0){
	  g0_action(p->op.atom->action);
	}
	scan();
	return true;
      }
      else {
	return false;
      }
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      if (parse(get_rule_by_head(p->op.atom->code)->body)){
	if (p->op.atom->action != 0){
	  g0_action(p->op.atom->action);
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

Vector *stack;

void g0_action(int action){
  Ptr *t1, *t2;
  switch(action){
  case 1:
    t1 = pop();
    t2 = pop();
    Rule *r = gen_rule(t2->op.atom->code, t1);
    vector_push(A, r);
    break;
  case 2:
    push(gen_atom(scan_token()->str,0, NON_TERMINAL));
    break;
  case 3:
    t1 = pop();
    t2 = pop();
    push(gen_union(t2, t1));
    break;
  case 4:
    t1 = pop();
    t2 = pop();
    push(gen_conc(t2, t1));
    break;
  case 5:
    push(gen_atom(scan_token()->str,0, TERMINAL));
    break;
  case 6:
    t1 = pop();
    push(gen_star(t1));
    break;
  case 7:
    t1 = pop();
    push(gen_un(t1));
    break;
  }
}

void push(Ptr *p){
  vector_push(stack, p);
}

Ptr* pop(){
  return vector_pop(stack);
}

void init_stack(){
  stack = empty_vector();
}
