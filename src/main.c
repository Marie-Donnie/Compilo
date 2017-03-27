#include "lexer.h"
#include "general_func.h"


/*------------------- TESTS -------------------------*/

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

  buffer = read_file(path);
  printf("%s\n", buffer);
  test_lexer(buffer);



  return EXIT_SUCCESS;
}
