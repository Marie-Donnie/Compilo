#include <stdbool.h>
#include "minunit.h"
#include "sets.h"
#include "vector.h"
#include "lexer_G0.h"
#include "parser_G0.h"

MU_TEST(sets) {
  Set *s = empty_set();
  mu_check(set_length(s) == 0);

  // Add
  char *str = "A";
  Set *s2 = set_add(s, str);
  mu_check(set_length(s2) == 1);
  mu_check(set_is_member(s2, str));
  mu_check(set_is_member(s2, "A"));

  // Can't add the same string
  Set *s3 = set_add(s2, str);
  mu_check(set_length(s3) == 1);

  // Can't add an equal string
  Set *s4 = set_add(s2, "A");
  mu_check(set_length(s4) == 1);

  //  Union
  Set *s5 = set_add(empty_set(), "B");
  Set *s6 = set_union(s2, s5);
  mu_check(set_length(s6) == 2);
  mu_check(set_is_member(s6, "A"));
  mu_check(set_is_member(s6, "B"));

  // Remove
  Set *s7 = set_remove(s6, "B");
  mu_check(set_length(s7) == 1);
  mu_check(set_is_member(s7, "B") == false);
}

MU_TEST(vectors) {
  Vector *v = empty_vector();
  mu_check(vector_length(v) == 0);

  // Push
  char *A = "A";
  vector_push(v, A);
  mu_check(vector_length(v) == 1);
  mu_check(vector_get(v, 0) == A);

  // is_member
  mu_check(vector_is_member(v, A));
  mu_check(vector_is_member(v, "B") == false);

  // concat
  Vector *v2 = empty_vector();
  char *B = "B";
  char *C = "C";
  vector_push(v2, B);
  vector_push(v2, C);
  vector_concat(v, v2);
  mu_check(vector_length(v) == 3);
  mu_check(vector_get(v, 0) == A);
  mu_check(vector_get(v, 1) == B);
  mu_check(vector_get(v, 2) == C);
}

MU_TEST(lexer) {
  Token *t1 = gen_token("IDNTER", "A");
  mu_check(!strcmp(t1->type, "IDNTER"));
  mu_check(!strcmp(t1->str, "A"));
  mu_check(t1->action == 0);

  Token *t2 = gen_token("IDNTER", "foo#42");
  mu_check(!strcmp(t2->type, "IDNTER"));
  mu_check(!strcmp(t2->str, "foo"));
  mu_check(t2->action == 42);

  char *input = "Ident42 ->       +(|'rter'|)(ident)'abc' ['ab'] '' ,;";
  Token *output[] = {
    gen_token("IDNTER", "Ident42"),
    gen_token("->", "->"),
    gen_token("+", "+"),
    gen_token("(|", "(|"),
    gen_token("ELTER", "rter"),
    gen_token("|)", "|)"),
    gen_token("(", "("),
    gen_token("IDNTER", "ident"),
    gen_token(")", ")"),
    gen_token("ELTER", "abc"),
    gen_token("[", "["),
    gen_token("ELTER", "ab"),
    gen_token("]", "]"),
    gen_token("ELTER", ""),
    gen_token(",", ","),
    gen_token(";", ";"),
    gen_token(END_FILE_STR, END_FILE_STR),
  };
  size_t i = 0;
  size_t out_len = sizeof(output) / sizeof(Token*);
  int index = 0;
  Token *t;

  do {
    t = lex(input, &index);
    mu_check(i < out_len);
    mu_check(!strcmp(t->type, output[i]->type));
     mu_check(!strcmp(t->str, output[i]->str));
     i++;
  } while (t->type != END_FILE_STR);
}

MU_TEST(parser){
  gen_forest();
  Rule *S = vector_get(A, 0);

  init_stack();
  init_scan("S -> 'a',;");
  scan();
  mu_check(parse(S->body));

  init_stack();
  init_scan("S0 -> ['animal'] . 'bateau' ,;");
  scan();
  mu_check(parse(S->body));

  init_stack();
  init_scan("S0 -> ['a'] . 'b' + S1, \n S1 -> S1,;");
  scan();
  mu_check(parse(S->body));

  init_stack();
  init_scan("S");
  scan();
  mu_check(!parse(S->body));

}


int main() {
  MU_RUN_TEST(sets);
  MU_RUN_TEST(vectors);
  MU_RUN_TEST(lexer);
  MU_RUN_TEST(parser);
  MU_REPORT();
  return 0;
}
