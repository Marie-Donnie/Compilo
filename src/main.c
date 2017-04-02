#include "lexer_G0.h"
#include "parser_G0.h"
#include "general_func.h"
#include "lexer_GPL.h"
#include "parser_GPL.h"

/*------------------- PRINT FUNC -------------------------*/


void print_vector(Vector *v){
  printf("<");
  for (size_t i = 0 ; i < v->nb_elts ; i++){
    printf("%s, ", (char*)v->elts[i]);
  }
  printf(">\n");
}

void print_p_code(){
  int c0 = 0;
  int code;
  while (c0 < vector_length(p_code)){
    code = p_code_get(c0);
    switch (code){
    case LDA:
      printf("LDA %d\n", p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case LDC:
      printf("LDC %d\n", p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case ADD:
      printf("ADD\n");
      c0 = c0 + 1;
      break;
    case SUB:
      printf("SUB\n");
      c0 = c0 + 1;
      break;
    case MULT:
      printf("MULT\n");
      c0 = c0 + 1;
      break;
    case DIV:
      printf("DIV\n");
      c0 = c0 + 1;
      break;
    case OR:
      printf("OR\n");
      c0 = c0 + 1;
      break;
    case AND:
      printf("AND\n");
      c0 = c0 + 1;
      break;
    case NOT:
      printf("NOT\n");
      c0 = c0 + 1;
      break;
    case EQ:
      printf("EQ\n");
      c0 = c0 + 1;
      break;
    case LT:
      printf("LT\n");
      c0 = c0 + 1;
      break;
    case GT:
      printf("GT\n");
      c0 = c0 + 1;
      break;
    case LEQ:
      printf("LEQ\n");
      c0 = c0 + 1;
      break;
    case GEQ:
      printf("GEQ\n");
      c0 = c0 + 1;
      break;
    case NEQ:
      printf("NEQ\n");
      c0 = c0 + 1;
      break;
    case AFF:
      printf("AFF\n");
      c0 = c0 + 1;
      break;
    default:
      printf("%d\n", code);
      c0 = c0 + 1;
    }
  }
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
 Token *t;
 do {
   t = lex(buffer, &idx);
   printf("%d Token type = %s, ", idx, t->type);
   if (t->str){
     printf("Token str = %s", t->str);
   }
   printf("\n");
 } while (strcmp(t->type, END_FILE_STR));
}

void test_g0(){
  char *str = "Ident42 ->       +(|'rter'|)(ident)'abc' ['ab'] '' ,;";
  test_lexer(str);
}

void test_parser(){
  int index;
  init_stack();
  scan();
  Rule *S = vector_get(A, 0);
  if (parse(S->body)) {
    printf("Parse ok\n");
  } else {
    printf("Parse error\n");
  }
  printf("Number of parsed rules: %d\n", vector_length(A)-5);
  for (index = 5 ; index < vector_length(A) ; index++) {
    Rule *r = vector_get(A, index);
    printf("Rule %s:\n", r->head);
    print_ptr(r->body, 0);
  }
}

void test_lexer_GPL(char *buffer){
 int idx = 0;
 Token *t;
 do {
   t = lex_GPL(buffer, &idx);
   printf("%d Token type = %s, ", idx, t->type);
   if (t->str){
     printf("Token str = %s", t->str);
   }
   printf("\n");
 } while (strcmp(t->type, END_FILE_STR));
}

void test_parser_GPL(){
  init_stack();
  init_parse();
  scan_GPL();
  Rule *r = vector_get(A, 5);
  if (parse_GPL(r->body)) {
    printf("Parse ok\n");
  } else {
    printf("Parse error\n");
  }
  print_p_code();
}


/*------------------- MAIN -------------------------*/

int main(int argc, char **argv){
  char *gpl_path;
  char *buffer;
  char *pgm_path;
  char *pgm;
  /* Ptr *a = gen_atom(';', 0, TERMINAL); */
  /* Ptr *b = gen_atom(';', 0, TERMINAL); */
  /* Ptr *c = gen_conc(a,b); */
  /* print_ptr(c, 0); */
  /* free_ptr(c); */

  /* Ptr *s = gen_F(); */
  /* print_ptr(s,0); */
  /* free_ptr(s); */

  /* printf("Nombre = %d\n", char_count("GPL")); */
  if (argc != 3) {
    perror("usage : compilo <GPL-path> <pgm>");
    exit(1);
  }
  gpl_path = argv[1];
  pgm_path = argv[2];

  printf("/*------------------ FOREST ------------------*/\n");
  gen_forest();
  test_A();
  printf("/*------------------ BUFFER ------------------*/\n");

  buffer = read_file(gpl_path);
  printf("Buffer:\n%s\n", buffer);


  printf("/*------------------ LEXER_G0 ------------------*/\n");
  test_lexer(buffer);


  printf("/*------------------ PARSER_G0 ------------------*/\n");
  init_scan(buffer);
  test_parser();


  printf("/*------------------ PGM ------------------*/\n");

  pgm = read_file(pgm_path);

  printf("Program:\n%s\n", pgm);

  test_lexer_GPL(pgm);
  init_scan(pgm);
  test_parser_GPL();

  return EXIT_SUCCESS;
}
