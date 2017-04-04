#include <stdbool.h>
#include <string.h>
#include "minunit.h"
#include "vector.h"
#include "lexer_G0.h"
#include "parser_G0.h"


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

  // Equality
  v = empty_vector();
  Vector *u = empty_vector();
  mu_check(vector_equal(v, u, &identity));

  vector_push(v, A);
  vector_push(u, A);
  mu_check(vector_equal(v, u, &identity));

  char *A2 = strdup(A);
  vector_push(v, A);
  vector_push(u, A2);
  mu_check(!vector_equal(v, u, &identity));
  mu_check(vector_equal(v, u, &str_eq));

  // concat
  v = empty_vector();
  u = empty_vector();
  vector_push(v, "A");
  char *B = "B";
  char *C = "C";
  vector_push(u, B);
  vector_push(u, C);
  vector_concat(v, u);
  mu_check(vector_length(v) == 3);
  mu_check(vector_get(v, 0) == A);
  mu_check(vector_get(v, 1) == B);
  mu_check(vector_get(v, 2) == C);
}

MU_TEST(ptr_test) {
  mu_check(ptr_equal(gen_atom("a", 0, TERMINAL),
                     gen_atom("a", 0, TERMINAL)));

  mu_check(!ptr_equal(gen_atom("a", 0, TERMINAL),
                      gen_atom("b", 0, TERMINAL)));

  mu_check(!ptr_equal(gen_atom("a", 0, TERMINAL),
                      gen_atom("a", 0, NON_TERMINAL)));

  mu_check(!ptr_equal(gen_atom("a", 0, TERMINAL),
                      gen_atom("a", 1, TERMINAL)));

  mu_check(ptr_equal(gen_S(), gen_S()));
  mu_check(ptr_equal(gen_N(), gen_N()));
  mu_check(ptr_equal(gen_T(), gen_T()));
  mu_check(ptr_equal(gen_E(), gen_E()));
  mu_check(ptr_equal(gen_F(), gen_F()));
}

MU_TEST(rule_test) {
  mu_check(rule_equal(gen_rule("S", gen_atom("a", 0, TERMINAL)),
                      gen_rule("S", gen_atom("a", 0, TERMINAL))));
  mu_check(!rule_equal(gen_rule("S", gen_atom("a", 0, TERMINAL)),
                       gen_rule("A", gen_atom("a", 0, TERMINAL))));
  mu_check(!rule_equal(gen_rule("S", gen_atom("a", 0, TERMINAL)),
                       gen_rule("S", gen_atom("b", 0, TERMINAL))));

  mu_check(rule_equal(gen_rule("S", gen_S()),
                      gen_rule("S", gen_S())));
}

MU_TEST(grammar_test) {
  Vector *G = empty_vector();
  vector_push(G, gen_rule("S", gen_S()));
  vector_push(G, gen_rule("N", gen_N()));
  vector_push(G, gen_rule("E", gen_E()));
  vector_push(G, gen_rule("T", gen_T()));
  vector_push(G, gen_rule("F", gen_F()));

  Vector *G2 = empty_vector();
  vector_push(G2, gen_rule("S", gen_S()));
  vector_push(G2, gen_rule("N", gen_N()));
  vector_push(G2, gen_rule("E", gen_E()));
  vector_push(G2, gen_rule("T", gen_T()));
  vector_push(G2, gen_rule("F", gen_F()));

  mu_check(grammar_equal(G, G2));
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
  MU_RUN_TEST(vectors);
  MU_RUN_TEST(ptr_test);
  MU_RUN_TEST(rule_test);
  MU_RUN_TEST(grammar_test);
  MU_RUN_TEST(lexer);
  MU_RUN_TEST(parser);
  MU_REPORT();
  return 0;
}
