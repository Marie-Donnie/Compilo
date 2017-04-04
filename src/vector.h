#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "general_func.h"

typedef struct {
  void **elts;
  size_t size;
  size_t nb_elts;
} Vector;

typedef bool (*eq_func)(void *, void *);

Vector* empty_vector();
int vector_length(Vector *v);
void* vector_get(Vector *v, int index);
bool vector_is_member(Vector *v, void *e);

Vector* vector_push(Vector *v, void *e);
void* vector_pop(Vector *v);

Vector* vector_concat(Vector *v, Vector *u);

bool vector_equal(Vector *a, Vector *b, eq_func fn);
bool identity(void *a, void *b);
bool str_eq(void *a, void *b);

# endif // VECTOR_H
