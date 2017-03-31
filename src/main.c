#include "lexer.h"
#include "parser.h"
#include "general_func.h"

/*------------------- PRINT FUNC -------------------------*/

void print_set(Set *set){
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
  for (int i = 0 ; i < vector_length(A) ; i++){
    Rule *r = vector_get(A, i);
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

void test_parser(){
  printf("Testing first(E):\n");
  Set *set = first("E", A);
  print_set(set);
  printf("Testing follow(E):\n");
  Set *set2 = follow("E", A);
  print_set(set2);
  printf("Testing parsing table:\n");
  init_parsing_table(A);
  Rule *r = parsing_table_get("F", "[");
  printf("Head for M[F,'[']:%s.\n", r->head);
  print_ptr(r->body, 0);
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

  return EXIT_SUCCESS;
}
