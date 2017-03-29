#include "parser.h"
#include <assert.h>

const char *EPS = "eps";
const char *EF = "";

map_t *cache_first = NULL;

bool set_is_equal(const void *a, const void *b){
  return is_equal((char*)a, (char*)b);
}

const Set* first(char *head){
  Set *s;
  int error;

  // Terminal
  if (get_rule_by_head_lax(head) == NULL){
    return set_add(empty_set(), head);
  }

  if (cache_first == NULL){
    cache_first = hashmap_new();
  }

  if (hashmap_get(cache_first, head, (void**)&s) == MAP_MISSING) {
    const Set *set = first_ptr(get_rule_by_head(head)->body);
    error = hashmap_put(cache_first, head, set);
    if (error != MAP_OK){
      fprintf(stderr, "Problem while adding an element to the hashmap.\n");
      exit(-1);
    }
  }

  hashmap_get(cache_first, head, (void**)&s);

  return s;
}

const Set* first_ptr(Ptr *p){


  if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){
      return set_add(empty_set(), p->op.atom->code);
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      return first(p->op.atom->code);
    }
  }
  else if (p->op_type == CONC){
    const Set *left = first_ptr(p->op.conc->left);
    if (set_is_member(left, EPS)) {
      return set_union(set_remove(left, EPS), first_ptr(p->op.conc->right));
    }
    return left;
  }
  else if (p->op_type == UNION){
    return set_union(first_ptr(p->op.uni->left), first_ptr(p->op.uni->right));
  }
  else if (p->op_type == STAR){
    return set_add(first_ptr(p->op.star->stare), EPS);
  }
  else if (p->op_type == UN){
    return set_add(first_ptr(p->op.un->une), EPS);
  }
  else if (true){ printf("not implemented\n"); } //TODO
  return empty_set();
}

const Set* follow(char *head){
  size_t i, j;
  int idx;
  const Set *s = empty_set();
  // Rule = S
  if (is_equal(head, get_rule(0)->head)){
    return set_add(s, END_FILE_STR);
  }
  else {
    for (i = 0 ; i < get_A_length() ; i++){
      Rule *r = get_rule(i);
      Vector *vv = leaves(r->body, empty_vector());
      for (j = 0 ; j < vv->nb_elts ; j++){
	Vector *v = vv->elts[j];
	idx = index_of(head, v);
	if (idx > -1){
	  if ((size_t)idx == v->nb_elts -1){
	    s = set_union(s, follow(r->head));
	  }
	  else {
	    s = set_union(s, first(v->elts[idx+1]));
	    if (set_is_member(s, EPS)){
	      s = set_union(s, follow(r->head));
	      s = set_remove(s, EPS);
	    }
	  }
	}
      }
    }
  }
  return s;
}


const Set* set_union_eps(const Set *set1, const Set *set2){
  if (set_is_member(set1, EPS)){
    return set_union(set_remove(set1, EPS), set2);
  }
  else{
    return set1;
  }
}



Ptr* get_production(char *code){
  return gen_atom("ELTER",0,TERMINAL);
}



bool is_equal(char *ter1, char *ter2){
  if (ter1 == ter2){
    return true;
  }
  else return !strcmp(ter1, ter2);
}


int index_of(char *ter, Vector *v){
  size_t i;
  for (i = 0 ; i < v->nb_elts ; i++){
    if (is_equal(ter, v->elts[i])){
	return (int)i;
    }
  }
  return -1;
}
