#include "parser.h"

const char *EPS = "eps";

const Set* first(Ptr *p){
  if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){
      return set_add(empty_set(), p->op.atom->code);
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      Ptr *ptr = get_production(p->op.atom->code);
      return first(ptr);
    }
  }
  else if (p->op_type == CONC){
    return set_union_eps(first(p->op.conc->left), first(p->op.conc->right));
  }
  else if (p->op_type == STAR){
    return set_add(first(p->op.star->stare), EPS);
  }
  else if (p->op_type == UN){
    return set_add(first(p->op.un->une), EPS);
  }
  else if (true){ printf("not implemented\n"); } //TODO
  return empty_set();
}

const Set* follow(Ptr *p){

}


const Set* set_union_eps(const Set *set1, const Set *set2){
  if (set_is_member(set1, EPS)){
    return set_union(set_remove(set1, EPS), set2);
  }
  else{
    return set1;
  }
}

void print_set(const Set *set){
  printf("{");
  for (size_t i = 0 ; i < set->size ; i++){
    printf("%s, ", (char*)set->set[i]);
  }
  printf("}\n");
}

Ptr* get_production(char *code){
  return gen_atom("ELTER",0,TERMINAL);
}
