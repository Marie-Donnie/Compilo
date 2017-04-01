#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"

/*------------------- DECLARATION -------------------------*/

/** \enum AtomType
 *  \brief Describes the type of an atom
 */
typedef enum atomType {
  TERMINAL,     /**< Atom contains a Terminal */
  NON_TERMINAL  /**< Atom contains a Non-Terminal */
} AtomType;

/** \enum Op
 *  \brief Describes the operations available for the grammar
 */
typedef enum operation {
  CONC,        /**< Concatenation: '.' */
  UNION,       /**< Union: '+' $\equiv$ | */
  STAR,        /**< Star: [ ] $\equiv$ * */
  UN,          /**< Un: (| |) $\equiv$ ? */
  ATOM         /**< Atom: ELTER or IDNTER (cf Code)*/
} Op;


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

/** \struct Ptr
 *  \brief Describes the Ptr
 */
struct ptr{
  Op op_type;     /**< The operation contained (cf Op enum) */
  union {
    Conc *conc;
    Union *uni;
    Star *star;
    Un *un;
    Atom *atom;
  } op;
};

/*------------------- RULE -------------------------*/

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

void gen_forest();
Rule* gen_rule(char *head, Ptr *body);
Rule *get_rule(size_t index);
Rule* get_rule_by_head(char *head);
Rule* get_rule_by_head_lax(char *head);
size_t get_A_length();


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



#endif // DEFINITIONS_H
