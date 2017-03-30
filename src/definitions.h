#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"

extern char *EPS;

/*------------------- DECLARATION -------------------------*/

typedef enum atomType {TERMINAL, NON_TERMINAL} AtomType;
typedef enum operation {CONC, UNION, STAR, UN, ATOM} Op;
typedef enum cod {ELTER, IDNTER} Code;
#define TER_SIZE 10
#define ARRAY_SIZE 50

Vector *A;
extern bool is_in_G0_phase;

typedef struct ptr Ptr;

typedef struct sconc {
  Ptr *left;
  Ptr *right;
} Conc;

typedef struct sunion {
  Ptr *left;
  Ptr *right;
} Union;

typedef struct sstar {
  Ptr *stare;
} Star;

typedef struct sun {
  Ptr *une;
} Un;

typedef struct satom{
  char *code;
  int action;
  AtomType a_type;
} Atom;

struct ptr{
  Op op_type;
  union {
    Conc *conc;
    Union *uni;
    Star *star;
    Un *un;
    Atom *atom;
  } op;
};

/*------------------- LEXICAL UNIT -------------------------*/

typedef struct sl_u {
  Code code;
  int action;
  AtomType type;
  char* str;
} Lexical_unit ;

typedef struct {
  char *head;
  Ptr *body;
} Rule;

/*------------------- GENERATION -------------------------*/

Ptr* gen_conc(Ptr *p1, Ptr *p2);
Ptr* gen_star(Ptr *p1);
Ptr* gen_atom(char *code, int action, AtomType at);
Ptr* gen_union(Ptr *p1, Ptr *p2);
Ptr* gen_un(Ptr *p1);

/*------------------- FOREST GENERATION -------------------------*/

Ptr* gen_S();
Ptr* gen_N();
Ptr* gen_E();
Ptr* gen_T();
Ptr* gen_F();

void gen_Forest();
Rule* gen_rule(char *head, Ptr *body);
Rule *get_rule(size_t index);
Rule* get_rule_by_head(char *head);
Rule* get_rule_by_head_lax(char *head);
size_t get_A_length();

/*------------------- EQUALITY -----------------------*/

bool ptr_equal(Ptr *a, Ptr *b);
bool atom_equal(Atom *a, Atom *b);
bool conc_equal(Conc *a, Conc *b);
bool union_equal(Union *a, Union *b);
bool star_equal(Star *a, Star *b);
bool un_equal(Un *a, Un *b);
bool rule_equal(Rule *a, Rule *b);
bool grammar_equal(Vector *a, Vector *b);

/*------------------- NORMALIZATION -----------------------*/

Vector* normalize_grammar(Vector *g);
Vector* normalize_rule(Rule *r);
Ptr* normalize_ptr(Ptr *p, char *head, Vector *rules);
char *gen_symbol(char *head, Vector *rules);

/*------------------- PTR SPECIFIC FUNCTIONS -----------------------*/

Vector* leaves(Ptr *p, Vector *v);
Vector* leaves_normalized(Ptr *p, Vector *atoms);

/*------------------- DESTRUCTION -------------------------*/

void free_ptr(Ptr *p);

void free_conc(Conc *c);
void free_star(Star *s);
void free_atom(Atom *a);
void free_union(Union *u);
void free_un(Un *un);

/*------------------- PRINT -------------------------*/

void print_indent(int indent);
void print_conc(Conc *c, int indent);
void print_star(Star *s, int indent);
void print_union(Union *u, int indent);
void print_un(Un *un, int indent);
void print_atom(Atom *a, int indent);
void print_atom_type(AtomType at);
void print_ptr(Ptr *p, int indent);


/*------------------- ANALYZE -------------------------*/

bool analyze(Ptr* p);

/*------------------- ACTION -------------------------*/

void empiler(Ptr *pile, Ptr *T);
void depiler(Ptr *pile, Ptr *T);
void recherche(char *dico, char *atrouver);

void go_action(int action);

#endif // DEFINITIONS_H
