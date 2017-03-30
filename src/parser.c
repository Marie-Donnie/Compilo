#include "parser.h"
#include <assert.h>

char *EPS = "eps";
char *EF = "";
map_t *parsing_table = NULL;
map_t *cache_first = NULL;

bool set_is_equal(void *a, void *b){
  return is_equal((char*)a, (char*)b);
}

Set* first(char *head){
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
    Set *set = first_ptr(get_rule_by_head(head)->body);
    error = hashmap_put(cache_first, head, set);
    if (error != MAP_OK){
      fprintf(stderr, "Problem while adding an element to the hashmap.\n");
      exit(-1);
    }
  }

  hashmap_get(cache_first, head, (void**)&s);

  return s;
}

Set* first_ptr(Ptr *p){
  if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){
      return set_add(empty_set(), p->op.atom->code);
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      return first(p->op.atom->code);
    }
  }
  else if (p->op_type == CONC){
    Set *left = first_ptr(p->op.conc->left);
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

Set* follow(char *head){
  size_t i, j;
  int idx;
  Set *s = empty_set();
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

      }
    }
  }
  return s;
}


Set* set_union_eps(Set *set1, Set *set2){
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


/*------------------- PARSING_TABLE -------------------------*/

void init_parsing_table(){
  size_t i, j;
  parsing_table = hashmap_new();
  for (i = 0 ; i < get_A_length() ; i++){
    Rule *r = get_rule(i);
    Set *s = first(r->head);
    for (j = 0 ; j < s->size ; j++){
      if (!is_equal(s->set[j], EPS)){
        parsing_table_put(r->head, (char*)s->set[j], r);
      }
    }
    if (set_is_member(s, EPS)){
      Set *set = follow(r->head);
      for (j = 0; j < set->size ; j++){
        parsing_table_put(r->head, (char*)set->set[j], r);
      }
    }
  }

}

void parsing_table_put(char *head, char *ter, Rule *r){
  map_t *row;
  int error;
  error = hashmap_get(parsing_table, head, (void**)&row);
  if (error == MAP_MISSING){
    row = hashmap_new();
    hashmap_put(parsing_table, head, row);
  }
  hashmap_put(row, ter, r);
}

Rule* parsing_table_get(char *head, char *ter){
  map_t *row;
  int ret;
  Rule *r;
  ret = hashmap_get(parsing_table, head, (void**)&row);
  if (ret == MAP_OK){
    ret = hashmap_get(row, ter, (void**)&r);
    if (ret == MAP_OK){
      return r;
    }
    else {
      fprintf(stderr, "Column %s missing from row %s in parsing table.\n", ter, head);
      exit(-1);
    }
  }
  else {
    fprintf(stderr, "Row %s missing in parsing table.\n", head);
    exit(-1);
  }
}
