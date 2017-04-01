#include "vector.h"


Vector* empty_vector(){
  Vector * v = check_malloc(sizeof(Vector));
  v->size = 0;
  v->nb_elts = 0;
  v->elts = NULL;
  return v;
}

int vector_length(Vector *v){
  return v->nb_elts;
}

void* vector_get(Vector *v, int index){
  if (index < vector_length(v)) {
    return v->elts[index];
  }
  fail("vector_get: index ouf of range");
}

bool vector_is_member(Vector *v, void *e){
  size_t i;
  for (i = 0 ; i < v->nb_elts ; i++){
    if (v->elts[i] == e){
      return true;
    }
  }
  return false;
}

Vector* vector_push(Vector *v, void *e){
  if (v->nb_elts == v->size){
    size_t newsize = (v->size == 0 ? 5 : v->size*2);
    v->elts = check_realloc(v->elts, newsize*sizeof(e));
    v->size = newsize;
  }
  v->elts[v->nb_elts] = e;
  v->nb_elts++;
  return v;
}

Vector* vector_pop(Vector *v){
  if (vector_length(v) > 0){
    v->nb_elts--;
    return v;
  }
  fail("vector_pop: vector is empty");
}

Vector* vector_concat(Vector *v, Vector *u){
  size_t i;
  for (i = 0 ; i < u->nb_elts ; i++){
    vector_push(v, u->elts[i]);
  }
  return v;
}
