#include "definitions.h"

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
