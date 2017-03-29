#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "general_func.h"

typedef struct {
  void **elts;
  size_t size;
  size_t nb_elts;
} Vector;


Vector* empty_vector();

bool vector_is_member(Vector *v, void *e);

Vector* vector_push(Vector *v, void *e);
Vector* vector_concat(Vector *v, Vector *u);

# endif // VECTOR_H
