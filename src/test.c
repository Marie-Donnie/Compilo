#include <stdbool.h>
#include "minunit.h"
#include "sets.h"
#include "vector.h"
#include "lexer.h"
#include "parser.h"

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

  // Equality
  mu_check(set_equal(empty_set(), empty_set()));

  Set *s8 = empty_set();
  set_add(s8, "A");
  set_add(s8, "B");
  Set *s9 = empty_set();
  set_add(s9, "B");
  set_add(s9, "A");
  mu_check(set_equal(s8, s9));
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
  Token *t1 = gen_token(IDENT, "A");
  mu_check(t1->type == IDENT);
  mu_check(!strcmp(t1->str, "A"));

  char *input = "Ident42 ->       +(|'rter'|)(ident)'abc' ['ab'] '' ,;";
  Token *output[] = {
    gen_token(IDENT, "Ident42"),
    gen_token(ARROW, NULL),
    gen_token(PLUS, NULL),
    gen_token(L_PAREN_BAR, NULL),
    gen_token(TER, "rter"),
    gen_token(R_PAREN_BAR, NULL),
    gen_token(L_PAREN, NULL),
    gen_token(IDENT, "ident"),
    gen_token(R_PAREN, NULL),
    gen_token(TER, "abc"),
    gen_token(L_BRACKET, NULL),
    gen_token(TER, "ab"),
    gen_token(R_BRACKET, NULL),
    gen_token(TER, ""),
    gen_token(COMMA, NULL),
    gen_token(SEMI_COLON, NULL),
    gen_token(END_FILE, END_FILE_STR),
  };
  size_t i = 0;
  size_t out_len = sizeof(output) / sizeof(Token*);
  int index = 0;
  Token t;

  do {
    t = lex(input, &index);
    mu_check(i < out_len);
    mu_check(t.type == output[i]->type);
    if (t.str == NULL) {
      mu_check(output[i]->str == NULL);
    }
    else {
      mu_check(output[i]->str != NULL);
      mu_check(!strcmp(t.str, output[i]->str));
    }
    i++;
  } while (t.type != END_FILE);
}

MU_TEST(leaves_test) {
  // a
  Vector *v = leaves(gen_atom("a", 0, TERMINAL), empty_vector());
  // {a}
  mu_check(vector_length(v) == 1);
  mu_check(!strcmp(vector_get(v, 0), "a"));

  // Conc
  v = leaves(gen_conc(gen_atom("a", 0, TERMINAL),
                      gen_atom("b", 0, TERMINAL)), empty_vector());
  // {a, b}
  mu_check(vector_length(v) == 2);
  mu_check(!strcmp(vector_get(v, 0), "a"));
  mu_check(!strcmp(vector_get(v, 1), "b"));
}

MU_TEST(first_test) {
  Vector *G = empty_vector();
  // A -> a
  vector_push(G, gen_rule("A", gen_atom("a", 0, TERMINAL)));
  Set *s = first("A", G);
  // {a}
  Set *check = empty_set();
  check = set_add(check, "a");
  mu_check(set_equal(s, check));

  // B -> b0
  // B -> b1
  G = empty_vector();
  vector_push(G, gen_rule("B", gen_atom("b0", 0, TERMINAL)));
  vector_push(G, gen_rule("B", gen_atom("b1", 0, TERMINAL)));
  s = first("B", G);
  // {b0, b1}
  check = empty_set();
  check = set_add(check, "b0");
  check = set_add(check, "b1");
  mu_check(set_equal(s, check));

  // C -> c0 . c1
  G = empty_vector();
  vector_push(G, gen_rule("C", gen_conc(gen_atom("c0", 0, TERMINAL),
                                        gen_atom("c1", 0, TERMINAL))));
  s = first("C", G);
  // {c0}
  check = empty_set();
  check = set_add(check, "c0");
  mu_check(set_equal(s, check));

  // D -> D0
  // D0 -> d D0
  // D0 -> EPS
  G = empty_vector();
  vector_push(G, gen_rule("D", gen_atom("D0", 0, NON_TERMINAL)));
  vector_push(G, gen_rule("D0", gen_conc(gen_atom("d", 0, TERMINAL),
                                         gen_atom("D0", 0, NON_TERMINAL))));
  vector_push(G, gen_rule("D0", gen_atom(EPS, 0, TERMINAL)));
  s = first("D", G);
  // {d, EPS}
  check = empty_set();
  check = set_add(check, "d");
  check = set_add(check, EPS);
  mu_check(set_equal(s, check));

  // G0
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_S()));
  vector_push(G, gen_rule("N", gen_N()));
  vector_push(G, gen_rule("E", gen_E()));
  vector_push(G, gen_rule("T", gen_T()));
  vector_push(G, gen_rule("F", gen_F()));
  Vector *Gn = normalize_grammar(G);
  s = first("F", Gn);
  // {IDNTER, ELTER, (, [, (|}
  check = empty_set();
  check = set_add(check, "IDNTER");
  check = set_add(check, "ELTER");
  check = set_add(check, "(");
  check = set_add(check, "[");
  check = set_add(check, "(|");
  mu_check(set_equal(s, check));

  s = first("S", Gn);
  // {IDNTER, ;}
  check = empty_set();
  check = set_add(check, "IDNTER");
  check = set_add(check, ";");
  mu_check(set_equal(s, check));

  // first_str

  // S -> ABCd
  // A -> a
  // A -> EPS
  // B -> b
  // B -> EPS
  // C -> c
  // C -> EPS
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_conc(gen_atom("A", 0, NON_TERMINAL),
                                        gen_conc(gen_atom("B", 0, NON_TERMINAL),
                                                 gen_conc(gen_atom("C", 0, NON_TERMINAL),
                                                          gen_atom("d", 0, TERMINAL))))));
  vector_push(G, gen_rule("A", gen_atom("a", 0, TERMINAL)));
  vector_push(G, gen_rule("A", gen_atom(EPS, 0, TERMINAL)));
  vector_push(G, gen_rule("B", gen_atom("b", 0, TERMINAL)));
  vector_push(G, gen_rule("B", gen_atom(EPS, 0, TERMINAL)));
  vector_push(G, gen_rule("C", gen_atom("c", 0, TERMINAL)));
  vector_push(G, gen_rule("C", gen_atom(EPS, 0, TERMINAL)));
  // {A, B, C, d}
  Vector *prod = empty_vector();
  vector_push(prod, "A");
  vector_push(prod, "B");
  vector_push(prod, "C");
  vector_push(prod, "d");
  s = first_str(prod, 0, G);
  // {a,b,c,d}
  check = empty_set();
  check = set_add(check, "a");
  check = set_add(check, "b");
  check = set_add(check, "c");
  check = set_add(check, "d");
  mu_check(set_equal(s, check));

  s = first_str(prod, 1, G);
  // {b,c,d}
  check = empty_set();
  check = set_add(check, "b");
  check = set_add(check, "c");
  check = set_add(check, "d");
  mu_check(set_equal(s, check));

  s = first_str(prod, 3, G);
  // {d}
  check = empty_set();
  check = set_add(check, "d");
  mu_check(set_equal(s, check));

  // S -> AB
  // A -> a
  // A -> EPS
  // B -> b
  // B -> EPS
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_conc(gen_atom("A", 0, NON_TERMINAL),
                                        gen_atom("B", 0, NON_TERMINAL))));
  vector_push(G, gen_rule("A", gen_atom("a", 0, TERMINAL)));
  vector_push(G, gen_rule("A", gen_atom(EPS, 0, TERMINAL)));
  vector_push(G, gen_rule("B", gen_atom("b", 0, TERMINAL)));
  vector_push(G, gen_rule("B", gen_atom(EPS, 0, TERMINAL)));
  // {A, B}
  prod = empty_vector();
  vector_push(prod, "A");
  vector_push(prod, "B");
  s = first_str(prod, 0, G);
  // {a,b,EPS}
  check = empty_set();
  check = set_add(check, "a");
  check = set_add(check, "b");
  check = set_add(check, EPS);
  mu_check(set_equal(s, check));
}

MU_TEST(follow_test) {
  // S -> S0 b
  // S0 -> A S0
  // S0 -> EPS
  // A -> a
  Vector *G = empty_vector();
  vector_push(G, gen_rule("S", gen_conc(gen_atom("S0", 0, NON_TERMINAL),
                                        gen_atom("b", 0, TERMINAL))));
  vector_push(G, gen_rule("S0", gen_conc(gen_atom("A", 0, NON_TERMINAL),
                                         gen_atom("S0", 0, NON_TERMINAL))));
  vector_push(G, gen_rule("S0", gen_atom(EPS, 0, TERMINAL)));
  vector_push(G, gen_rule("A", gen_atom("a", 0, TERMINAL)));
  Set *s = follow("A", G);
  // {a,b}
  Set *check = empty_set();
  check = set_add(check, "a");
  check = set_add(check, "b");
  mu_check(set_equal(s, check));

  s = follow("S0", G);
  // {b}
  check = empty_set();
  check = set_add(check, "b");
  mu_check(set_equal(s, check));

  s = follow("S", G);
  // {$}
  check = empty_set();
  check = set_add(check, END_FILE_STR);
  mu_check(set_equal(s, check));

  // S -> A S0 c
  // S0 -> B S0
  // S0 -> EPS
  // A -> a
  // B -> b
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_conc(gen_atom("A", 0, NON_TERMINAL),
                                        gen_conc(gen_atom("S0", 0, NON_TERMINAL),
                                                 gen_atom("c", 0, TERMINAL)))));
  vector_push(G, gen_rule("S0", gen_conc(gen_atom("B", 0, NON_TERMINAL),
                                         gen_atom("S0", 0, NON_TERMINAL))));
  vector_push(G, gen_rule("S0", gen_atom(EPS, 0, TERMINAL)));
  vector_push(G, gen_rule("A", gen_atom("a", 0, TERMINAL)));
  vector_push(G, gen_rule("B", gen_atom("b", 0, TERMINAL)));
  s = follow("A", G);
  // {b,c}
  check = empty_set();
  check = set_add(check, "b");
  check = set_add(check, "c");
  mu_check(set_equal(s, check));

  s = follow("S0", G);
  // {c}
  check = empty_set();
  check = set_add(check, "c");
  mu_check(set_equal(s, check));

  s = follow("B", G);
  // {b,c}
  check = empty_set();
  check = set_add(check, "b");
  check = set_add(check, "c");
  mu_check(set_equal(s, check));

  // G0
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_S()));
  vector_push(G, gen_rule("N", gen_N()));
  vector_push(G, gen_rule("E", gen_E()));
  vector_push(G, gen_rule("T", gen_T()));
  vector_push(G, gen_rule("F", gen_F()));
  Vector *Gn = normalize_grammar(G);
  s = follow("S", Gn);
  // {$}
  check = empty_set();
  check = set_add(check, END_FILE_STR);
  mu_check(set_equal(s, check));

  s = follow("E", Gn);
  // {,, ), ], |)}
  check = empty_set();
  check = set_add(check, ",");
  check = set_add(check, ")");
  check = set_add(check, "]");
  check = set_add(check, "|)");
  mu_check(set_equal(s, check));
}

MU_TEST(normalize_test) {
  // S -> a
  Vector *G = empty_vector();
  vector_push(G, gen_rule("S", gen_atom("a", 0, TERMINAL)));
  Vector *Gn = normalize_grammar(G);
  // S -> a
  Vector *Gcheck = empty_vector();
  vector_push(Gcheck, gen_rule("S", gen_atom("a", 0, TERMINAL)));
  mu_check(grammar_equal(Gn, Gcheck));

  // S -> a . b
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_conc(gen_atom("a", 0, TERMINAL),
                                        gen_atom("b", 0, TERMINAL))));
  Gn = normalize_grammar(G);
  // S -> a . b
  Gcheck = empty_vector();
  vector_push(Gcheck, gen_rule("S", gen_conc(gen_atom("a", 0, TERMINAL),
                                             gen_atom("b", 0, TERMINAL))));
  mu_check(grammar_equal(Gn, Gcheck));

  // S -> a + b
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_union(gen_atom("a", 0, TERMINAL),
                                         gen_atom("b", 0, TERMINAL))));
  Gn = normalize_grammar(G);
  // S -> S0
  // S0 -> a
  // S0 -> b
  Gcheck = empty_vector();
  vector_push(Gcheck, gen_rule("S", gen_atom("S0", 0, NON_TERMINAL)));
  vector_push(Gcheck, gen_rule("S0", gen_atom("a", 0, TERMINAL)));
  vector_push(Gcheck, gen_rule("S0", gen_atom("b", 0, TERMINAL)));
  mu_check(grammar_equal(Gn, Gcheck));

  // S -> [a]
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_star(gen_atom("a", 0, TERMINAL))));
  Gn = normalize_grammar(G);
  // S -> S0
  // S0 -> a S0
  // S0 -> EPS
  Gcheck = empty_vector();
  vector_push(Gcheck, gen_rule("S", gen_atom("S0", 0, NON_TERMINAL)));
  vector_push(Gcheck, gen_rule("S0", gen_conc(gen_atom("a", 0, TERMINAL),
                                              gen_atom("S0", 0, NON_TERMINAL))));
  vector_push(Gcheck, gen_rule("S0", gen_atom(EPS, 0, TERMINAL)));
  mu_check(grammar_equal(Gn, Gcheck));

  // S -> (|a|)
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_un(gen_atom("a", 0, TERMINAL))));
  Gn = normalize_grammar(G);
  // S -> S0
  // S0 -> a
  // S0 -> EPS
  Gcheck = empty_vector();
  vector_push(Gcheck, gen_rule("S", gen_atom("S0", 0, NON_TERMINAL)));
  vector_push(Gcheck, gen_rule("S0", gen_atom("a", 0, TERMINAL)));
  vector_push(Gcheck, gen_rule("S0", gen_atom(EPS, 0, TERMINAL)));
  mu_check(grammar_equal(Gn, Gcheck));

  // S -> [A B]c
  G = empty_vector();
  vector_push(G, gen_rule("S", gen_conc(gen_star(gen_conc(gen_atom("A", 0, NON_TERMINAL),
                                                          gen_atom("B", 0, NON_TERMINAL))),
                                        gen_atom("c", 0, TERMINAL))));
  Gn = normalize_grammar(G);
  // S -> S0c
  // S0 -> A B S0
  // S0 -> EPS
  Gcheck = empty_vector();
  vector_push(Gcheck, gen_rule("S", gen_conc(gen_atom("S0", 0, NON_TERMINAL),
                                             gen_atom("c", 0, TERMINAL))));
  vector_push(Gcheck, gen_rule("S0", gen_conc(gen_conc(gen_atom("A", 0, NON_TERMINAL),
                                                       gen_atom("B", 0, NON_TERMINAL)),
                                              gen_atom("S0", 0, NON_TERMINAL))));
  vector_push(Gcheck, gen_rule("S0", gen_atom(EPS, 0, TERMINAL)));
  mu_check(grammar_equal(Gn, Gcheck));
}

int main() {
  MU_RUN_TEST(sets);
  MU_RUN_TEST(vectors);
  MU_RUN_TEST(ptr_test);
  MU_RUN_TEST(rule_test);
  MU_RUN_TEST(grammar_test);
  MU_RUN_TEST(lexer);
  MU_RUN_TEST(leaves_test);
  MU_RUN_TEST(first_test);
  MU_RUN_TEST(follow_test);
  MU_RUN_TEST(normalize_test);
  MU_REPORT();
  return 0;
}
