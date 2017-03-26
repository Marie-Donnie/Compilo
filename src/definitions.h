#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*------------------- DECLARATION -------------------------*/

typedef enum atomType {TERMINAL, NON_TERMINAL} AtomType;
typedef enum operation {CONC, UNION, STAR, UN, ATOM} Op;
#define TER_SIZE 10
#define ARRAY_SIZE 50

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

/*------------------- DESTRUCTION -------------------------*/

void free_ptr(Ptr *p);

void free_conc(Conc *c);
void free_star(Star *s);
void free_atom(Atom *a);
void free_union(Union *u);
void free_un(Un *un);

/*------------------- PRINT -------------------------*/

void print_ptr(Ptr *p, int indent);
void print_atom_type(AtomType at);

void print_indent(int indent);
void print_conc(Conc *c, int indent);
void print_star(Star *s, int indent);
void print_union(Union *u, int indent);
void print_un(Un *un, int indent);
void print_atom(Atom *a, int indent);
void print_atom_type(AtomType at);
void print_ptr(Ptr *p, int indent);

/*------------------- SCAN -------------------------*/

Ptr* scan(char* chaine);

/*------------------- ANALYZE -------------------------*/

bool analyze(Ptr* p);

/*------------------- ACTION -------------------------*/

void empiler(Ptr *pile, Ptr *T);
void depiler(Ptr *pile, Ptr *T);
void recherche(char *dico, char *atrouver);

void go_action(int action);
