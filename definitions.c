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


Ptr* gen_conc(Ptr *p1, Ptr *p2){
  Conc *c = (Conc*) malloc(sizeof(Conc));
  c->left = p1;
  c->right = p2;
  Ptr *p = (Ptr*) malloc(sizeof(Ptr));
  p->op_type = CONC;
  p->op.conc = c;
  return p;
}

Ptr* gen_star(Ptr *p1){
  Star *s = (Star*) malloc(sizeof(Star));
  s->stare = p1;
  Ptr *p = (Ptr*) malloc(sizeof(Ptr));
  p->op_type = STAR;
  p->op.star = s;
  return p;
}

Ptr* gen_atom(char *code, int action, AtomType at){
  Atom *a = (Atom*) malloc(sizeof(Atom));
  a->code = (char*) malloc(sizeof(char)*TER_SIZE);
  strncpy(a->code, code, TER_SIZE);
  a->code[9] = 0;
  a->action = action;
  a->a_type = at;
  Ptr *p = (Ptr*) malloc(sizeof(Ptr));
  p->op_type = ATOM;
  p->op.atom = a;
  return p;
}

Ptr* gen_union(Ptr *p1, Ptr *p2){
  Union *u = (Union*) malloc(sizeof(Union));
  u->left = p1;
  u->right = p2;
  Ptr *p = (Ptr*) malloc(sizeof(Ptr));
  p->op_type = UNION;
  p->op.uni = u;
  return p;
}

Ptr* gen_un(Ptr *p1){
  Un *une = (Un*) malloc(sizeof(Un));
  une->une = p1;
  Ptr *p = (Ptr*) malloc(sizeof(Ptr));
  p->op_type = UN;
  p->op.un = une;
  return p;
}


/*------------------- FOREST GENERATION -------------------------*/

Ptr* gen_S(){
  return gen_conc(gen_star(gen_conc(gen_conc(gen_conc(gen_atom("N",0,NON_TERMINAL),
						      gen_atom("Fleche",0,TERMINAL)),
					     gen_atom("E",0,NON_TERMINAL)),
				    gen_atom(",",1,TERMINAL))),
		  gen_atom(";",0,TERMINAL));
}

Ptr* gen_N(){
  return gen_atom("IDNTER",0,TERMINAL);
}

Ptr* gen_E(){
  return gen_conc(gen_star(gen_conc(gen_atom("T",0,NON_TERMINAL),
				    gen_atom("+",0,TERMINAL))),
		  gen_atom("T",0,NON_TERMINAL));
}

Ptr* gen_T(){
  return gen_conc(gen_star(gen_conc(gen_atom("F",0,NON_TERMINAL),
				    gen_atom(".",0,TERMINAL))),
		  gen_atom("F",0,NON_TERMINAL));
}

Ptr* gen_F(){
  return gen_union(gen_atom("IDNTER",0,TERMINAL),
		   gen_union(gen_atom("ELTER",0,TERMINAL),
			     gen_union(gen_conc(gen_conc(gen_atom("(",0,TERMINAL),
							 gen_atom("E",0,NON_TERMINAL)),
						gen_atom(")",0,TERMINAL)),
				       gen_union(gen_star(gen_atom("E",0,NON_TERMINAL)),
						 gen_un(gen_atom("E",0,NON_TERMINAL)))
						 )));
}



/*------------------- DESTRUCTION -------------------------*/

void free_ptr(Ptr *p);

void free_conc(Conc *c){
  free_ptr(c->left);
  c->left = NULL;
  free_ptr(c->right);
  c->right = NULL;
  free(c);
}

void free_star(Star *s){
  free_ptr(s->stare);
  s->stare = NULL;
  free(s);
}

void free_atom(Atom *a){
  free(a->code);
  a->code = NULL;
  free(a);
}

void free_union(Union *u){
  free_ptr(u->left);
  u->left = NULL;
  free_ptr(u->right);
  u->right = NULL;
  free(u);
}

void free_un(Un *un){
  free_ptr(un->une);
  un->une = NULL;
  free(un);
}

void free_ptr(Ptr *p){
  if (p->op_type == CONC){
    free_conc(p->op.conc);
    p->op.conc = NULL;
  }
  else if (p->op_type == STAR){
    free_star(p->op.star);
    p->op.star = NULL;
  }
  else if (p->op_type == ATOM){
    free_atom(p->op.atom);
    p->op.atom = NULL;
  }
  else if (p->op_type == UNION){
    free_union(p->op.uni);
    p->op.uni = NULL;
  }
  else if (p->op_type == UN){
    free_un(p->op.un);
    p->op.un =NULL;
  }
  free(p);
}



/*------------------- PRINT -------------------------*/

void print_ptr(Ptr *p, int indent);
void print_atom_type(AtomType at);

void print_indent(int indent){
  for (int i=0; i < indent ; ++i){
    printf("-");
  }
}

void print_conc(Conc *c, int indent){
  print_indent(indent);
  printf("> Conc \n");
  print_ptr(c->left, indent+3);
  print_ptr(c->right, indent+3);
}

void print_star(Star *s, int indent){
  print_indent(indent);
  printf(">Star \n");
  print_ptr(s->stare, indent+3);
}

void print_union(Union *u, int indent){
  print_indent(indent);
  printf("> Union \n");
  print_ptr(u->left, indent+3);
  print_ptr(u->right, indent+3);
}

void print_un(Un *un, int indent){
  print_indent(indent);
  printf(">Un \n");
  print_ptr(un->une, indent+3);
}

void print_atom(Atom *a, int indent){
  print_indent(indent);
  printf("> Atom : %s %d ", a->code, a->action);
  print_atom_type(a->a_type);
  printf("\n");
}

void print_atom_type(AtomType at){
  if (at == TERMINAL){
    printf("Terminal");
  }
  else if (at == NON_TERMINAL){
    printf("Non Terminal");
  }
}

void print_ptr(Ptr *p, int indent){
  if (p->op_type == CONC){
    print_conc(p->op.conc, indent);
  }
  else if (p->op_type == ATOM){
    print_atom(p->op.atom, indent);
  }
  else if (p->op_type == STAR){
    print_star(p->op.star, indent);
  }
  else if (p->op_type == UNION){
    print_union(p->op.uni, indent);
  }
  else if (p->op_type == UN){
    print_un(p->op.un, indent);
  }
  else {
    printf("Undefined type : op_type is %d \n", p->op_type);
  }
}

/*------------------- SCAN -------------------------*/


Ptr* scan(char* chaine){

  /* Terminal si " " ou entier, NT tout le reste qui n'est pas blanc */
  /* On accepte pas un nom de variable type 1toto, mais toto1 oui */
  /* Construit trois listes différentes pour blancs (nouvelle page, espace, retour chariot, etc.), unité lexicale (tout ce qui n'est pas un blanc), et les opérateurs */



  int memory_read;    /*this will be used as the variable for the value of the bytes read from the getline function*/

  int nbytes = 200;    /*this is the variable for the number of bytes initially allocated for your stream*/

  char *your_string;    /*this is the variable for the character file object used for your stream*/

  puts (“Enter stream, or line of text, here:”);    /*prompt for user to enter text*/

  your_string = (char *) malloc (nbytes + 1);    /*note the char cast operator as the pointer used will be a character pointer and also note that it’s added 1 to nbytes for the malloc function; the last character read by getline should be a null character and it’s added the one to account for the last null character that will be read*/

  memory_read = getline (&your_string, &nbytes, stdin);     /*the value of memory read will be determined by the return of your getline function*/

  if (memory_read == -1) { /* if a character is not read by getline, then -1 will be returned*/
      puts (“Error: only EOF without text read”);    /*displays error no bytes had been read, hence, if -1 had been returned*/
  }

  else {  /*if -1 had not been returned*/
    puts (your_string);   /*displays string that had been entered*/




  }

}



/*------------------- ANALYZE -------------------------*/

bool analyze(Ptr* p){
  bool ana = true;
  if (p->op_type == CONC){
  if (analyze(p->left)){
  ana = analyze(p->right);
    }
    else {
      ana = false;
    }
  }
  else if (p->op_type == UNION){
  if (analyze(p->left)){
      ana = true;
    }
    else {
      ana = analyze(p->right);
    }
  }
  else if (p->op_type == STAR){
    ana = true;
    /* while (analyze(p->stare)) {} */
  }
  else if (p->op_type == UN){
    ana = true;
    /* if (anlyze(p->une)) {} */
  }
  else if (p->op_type == ATOM){
  if (p->atom->a_type == TERMINAL){
  if (p->atom->code == code){
  ana = true;
  if (p->atom->action != 0){
  go_action(p->action);

	}
      }
    }
    if (p->atom->a_type == NON_TERMINAL){
      if (analyze()){
      }
    }
  }
  return ana;
}


/*------------------- ACTION -------------------------*/

void empiler(*Ptr pile, *Ptr T);
void depiler(*Ptr pile, *Ptr T);
void recherche(*char dico, *char atrouver);

void go_action(int action){

  *Ptr pile[ARRAY_SIZE];
  *char DICONT[ARRAY_SIZE];
  *char DICOT[ARRAY_SIZE];
  *Ptr T1;
  *Ptr T2;

  if (action == 1){
    depiler(pile,T1);
    depiler(pile,T2);
    A
  }
  else if (action == 2){
    empiler(gen_atom(recherche(DICONT,T1), action, atype));
  }
  else if (action == 3){

  }
  else if (action == 4){

  }
  else if (action == 5){

  }
  else if (action == 6){

  }
  else if (action == 7){

  }



}

void empiler(*Ptr pile, *Ptr T){
}

void depiler(*Ptr pile, *Ptr T){
}

void recherche(*char dico, *char atrouver){
}




/*------------------- MAIN -------------------------*/

int main(){
  /* Ptr *a = gen_atom(';', 0, TERMINAL); */
  /* Ptr *b = gen_atom(';', 0, TERMINAL); */
  /* Ptr *c = gen_conc(a,b); */
  /* print_ptr(c, 0); */
  /* free_ptr(c); */

  Ptr *s = gen_F();
  print_ptr(s,0);
  free_ptr(s);


  return EXIT_SUCCESS;
}


/* TODO : - scan, analyze*/
/* G0action -> GPL dans l'arbre*/
