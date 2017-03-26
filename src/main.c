#include "scanner.h"

/*------------------- TESTS -------------------------*/

void test_scanner(){
 int idx = 0;
  char *str = "->   'abc' ['ab'] '' ,;";
  Token t;
  do {
    t = scanner(str, &idx);
    printf("%d Token type = %d, ", idx, t.type);
    if (t.str){
      printf("Token str = %s", t.str);
    }
    printf("\n");
  } while (t.type != EF);
}


/*------------------- MAIN -------------------------*/

int main(){
  /* Ptr *a = gen_atom(';', 0, TERMINAL); */
  /* Ptr *b = gen_atom(';', 0, TERMINAL); */
  /* Ptr *c = gen_conc(a,b); */
  /* print_ptr(c, 0); */
  /* free_ptr(c); */

  /* Ptr *s = gen_F(); */
  /* print_ptr(s,0); */
  /* free_ptr(s); */

  /* printf("Nombre = %d\n", char_count("GPL")); */





  return EXIT_SUCCESS;
}
