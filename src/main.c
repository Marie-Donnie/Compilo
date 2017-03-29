#include "lexer.h"
#include "parser.h"
#include "general_func.h"

/*------------------- PRINT FUNC -------------------------*/

void print_set(const Set *set){
  printf("{");
  for (size_t i = 0 ; i < set->size ; i++){
    printf("%s, ", (char*)set->set[i]);
  }
  printf("}\n");
}

void print_vector(Vector *v){
  printf("<");
  for (size_t i = 0 ; i < v->nb_elts ; i++){
    printf("%s, ", (char*)v->elts[i]);
  }
  printf(">\n");
}

/*------------------- TESTS -------------------------*/

void test_A(){
  for (size_t i = 0 ; i < get_A_length() ; i++){
    Rule *r = get_rule(i);
    printf("Rule for %s:\n", r->head);
    print_ptr(r->body, 0);
  }
}

void test_lexer(char *buffer){
 int idx = 0;
 Token t;
    do {
    t = lex(buffer, &idx);
    printf("%d Token type = %d, ", idx, t.type);
    if (t.str){
      printf("Token str = %s", t.str);
    }
    printf("\n");
  } while (t.type != END_FILE);
}

void test_g0(){
  char *str = "Ident42 ->       +(|'rter'|)(ident)'abc' ['ab'] '' ,;";
  test_lexer(str);
}

void test_parser(){
  size_t i;
  /* const Set *set = first(gen_star(gen_conc(gen_atom("T",0,NON_TERMINAL), */
  /* 					   gen_atom("+",0,TERMINAL)))); */
  /* const Set *set = first(gen_conc(gen_star(gen_conc(gen_atom("T",0,NON_TERMINAL), */
  /* 						    gen_atom("+",0,TERMINAL))), */
  /* 				  gen_atom("T2",0,TERMINAL))); */
  printf("Testing first:\n");
  Set *set = first("E");
  print_set(set);
  printf("Testing follow:\n");
  Set *set2 = follow("E");
  print_set(set2);
  printf("Testing parsing table:\n");
  init_parsing_table();
  Rule *r = parsing_table_get("F", "[");
  printf("Head for M[F,'[']:%s.\n", r->head);
  print_ptr(r->body, 0);
}

void test_leaves(){
  size_t i;
  Vector *u = leaves(gen_conc(gen_atom("T",0,NON_TERMINAL),
			      gen_atom("+",0,TERMINAL)),
		     empty_vector());
  Vector *v = leaves(gen_F(), empty_vector());
  for (i = 0 ; i < v->nb_elts ; i++){
    print_vector(v->elts[i]);
  }
}


/*------------------- MAIN -------------------------*/

int main(int argc, char **argv){
  char *path;
  char *buffer;
  /* Ptr *a = gen_atom(';', 0, TERMINAL); */
  /* Ptr *b = gen_atom(';', 0, TERMINAL); */
  /* Ptr *c = gen_conc(a,b); */
  /* print_ptr(c, 0); */
  /* free_ptr(c); */

  /* Ptr *s = gen_F(); */
  /* print_ptr(s,0); */
  /* free_ptr(s); */

  /* printf("Nombre = %d\n", char_count("GPL")); */
  if (argc != 2) {
    perror("usage : compilo <GPL-path>");
    exit(1);
  }
  path = argv[1];

  printf("/*------------------ FOREST ------------------*/\n");
  gen_Forest();
  test_A();

  buffer = read_file(path);
  printf("Buffer:\n%s\n", buffer);
  printf("/*------------------ LEXER ------------------*/\n");
  test_lexer(buffer);
  printf("/*------------------ PARSER ------------------*/\n");
  test_parser();
  printf("/*------------------ LEAVES ------------------*/\n");
  test_leaves();


  return EXIT_SUCCESS;
}
