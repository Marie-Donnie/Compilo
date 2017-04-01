#include "parser.h"
#include <assert.h>

char *EPS = "eps";
char *EF = "";
map_t *parsing_table = NULL;
map_t *cache_first = NULL;

bool set_is_equal(void *a, void *b){
  return is_equal((char*)a, (char*)b);
}

void reset_cache(){
  cache_first = hashmap_new();
}

Set *first_str(Vector *prod, int start, Vector *G){
  int i = start;
  Set *s = set_add(empty_set(), EPS);
  while (set_is_member(s, EPS) && i < vector_length(prod)) {
    s = set_remove(s, EPS);
    s = set_union(s, first(vector_get(prod, i), G));
    i++;
  }
  return s;
}

Set* first(char *symbol, Vector *G){
  Set *s = empty_set();
  /* int error; */

  Vector *rules = grammar_get_rules_for(G, symbol);

  // symbol is terminal
  if (vector_length(rules) == 0) {
    return set_add(s, symbol);
  }

  // symbol is non-terminal, union the first of each rule
  for (int i = 0; i < vector_length(rules); ++i){
    Rule *r = vector_get(rules, i);
    Set *f = first_ptr(r->body, G);
    s = set_union(s, f);
  }

  return s;

  // No caching for now

  /* if (cache_first == NULL){ */
  /*   cache_first = hashmap_new(); */
  /* } */

  /* if (hashmap_get(cache_first, head, (void**)&s) == MAP_MISSING) { */
  /*   Set *set = first_ptr(get_rule_by_head(head)->body); */
  /*   error = hashmap_put(cache_first, head, set); */
  /*   if (error != MAP_OK){ */
  /*     fprintf(stderr, "Problem while adding an element to the hashmap.\n"); */
  /*     exit(-1); */
  /*   } */
  /* } */

  /* hashmap_get(cache_first, head, (void**)&s); */

  /* return s; */
}

Set* first_ptr(Ptr *p, Vector *G){
  if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){
      return set_add(empty_set(), p->op.atom->code);
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      return first(p->op.atom->code, G);
    }
  }
  else if (p->op_type == CONC){
    Set *left = first_ptr(p->op.conc->left, G);
    if (set_is_member(left, EPS)) {
      return set_union(set_remove(left, EPS), first_ptr(p->op.conc->right, G));
    }
    return left;
  }

  fprintf(stderr, "Grammar is not normalized\n");
  exit(1);
}

Set* follow(char *head, Vector *G){
  Set *s = empty_set();

  // First rule -> follow = {$}
  if (is_equal(head, ((Rule*)vector_get(G, 0))->head)){
    return set_add(s, END_FILE_STR);
  }

  for (int i = 0 ; i < vector_length(G) ; i++){
    Rule *r = vector_get(G, i);
    Vector *prod = leaves(r->body, empty_vector());
    int idx = index_of(head, prod);
    if (idx > -1){
      // Symbol at end of production
      if (idx == vector_length(prod) - 1){
        // Don't recurse for the same head
        if(strcmp(head, r->head)){
          s = set_union(s, follow(r->head, G));
        }
      }
      // There's a symbol after head
      else {
        Set *f = first_str(prod, idx + 1, G);
        if (set_is_member(f, EPS)){
          f = set_remove(f, EPS);
          // Don't recurse for the same head
          if (strcmp(head, r->head)){
            s = set_union(s, follow(r->head, G));
          }
        }
        s = set_union(f, s);
      }
    }
  }
  return s;
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

void init_parsing_table(Vector *G){
  parsing_table = hashmap_new();
  for (int i = 0 ; i < vector_length(G) ; i++){
    Rule *r = vector_get(G, i);
    Vector *prod = leaves(r->body, empty_vector());
    Set *firsts = first_str(prod, 0, G);
    for (int j = 0 ; j < set_length(firsts) ; j++){
      if (!is_equal(firsts->set[j], EPS)){
        parsing_table_put(r->head, (char*)firsts->set[j], r);
      }
    }
    if (set_is_member(firsts, EPS)){
      Set *s = follow(r->head, G);
      for (int j = 0; j < set_length(s) ; j++){
        parsing_table_put(r->head, (char*)s->set[j], r);
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
      return NULL;
    }
  }
  else {
    return NULL;
  }
}

/*------------------- PARSE -------------------------*/

void parse(char *input) {
  Vector *stack = empty_vector();
  Rule *start = vector_get(A, 0);
  vector_push(stack, start->head);
  int input_idx = 0;
  Token t = lex(input, &input_idx);
  Rule *r;

  while (vector_length(stack) > 0) {
    char *sym = vector_get(stack, vector_length(stack) - 1);

    printf("parse: sym(%s) t(%d, %s)\n", sym, t.type, t.str);

    if (is_same(sym, &t)) {
      vector_pop(stack);
      if (t.type == END_FILE) {
        fail("Syntax error");
      }
      t = lex(input, &input_idx);
    }
    else if (is_terminal(sym)) {
      fail("Syntax error");
    }
    else if ((r = parsing_table_get(sym, t.str)) == NULL) {
      fail("Syntax error");
    }
    else {
      print_ptr(r->body, 0);
      vector_pop(stack);
      Vector *l = leaves(r->body, empty_vector());
      for (int i=vector_length(l)-1; i >= 0; i--){
        vector_push(stack, vector_get(l, i));
      }
    }
  }
}

bool is_terminal(char *sym) {
  return get_rule_by_head_lax(sym) == NULL;
}

bool is_same(char *sym, Token *t){
  bool ret = false;

  if (t->type == IDENT && !strcmp(sym, t->str)){
    ret = true;
  }

  printf("%s == (%d, %s): %d\n", sym, t->type, t->str, ret);

  return false;
}
