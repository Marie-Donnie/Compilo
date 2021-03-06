#include <stdbool.h>
#include <string.h>
#include "minunit.h"
#include "vector.h"
#include "lexer_G0.h"
#include "parser_G0.h"
#include "lexer_GPL.h"
#include "parser_GPL.h"
#include "interpreter.h"


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

MU_TEST(lexer_g0) {
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

MU_TEST(parser_g0){
  gen_forest();
  Rule *S = vector_get(A, 0);

  init_stack();
  init_scan("S -> 'a',;");
  scan();
  Rule *r1 = gen_rule("S", gen_atom("a", 0, TERMINAL));
  mu_check(parse(S->body));
  mu_check(rule_equal(vector_get(A, 5), r1));

  gen_forest();
  init_stack();
  init_scan("S -> 'a#1',;");
  scan();
  r1 = gen_rule("S", gen_atom("a", 1, TERMINAL));
  mu_check(parse(S->body));
  mu_check(rule_equal(vector_get(A, 5), r1));

  gen_forest();
  init_stack();
  init_scan("S0 -> ['animal'] . 'bateau' ,;");
  scan();
  r1 = gen_rule("S0", gen_conc(gen_star(gen_atom("animal", 0, TERMINAL)),
                               gen_atom("bateau", 0, TERMINAL)));
  mu_check(parse(S->body));
  mu_check(rule_equal(vector_get(A, 5), r1));

  gen_forest();
  init_stack();
  init_scan("S0 -> ['a'] . 'b' + S1, \n S1 -> S1,;");
  scan();
  mu_check(parse(S->body));
  r1 = gen_rule("S0", gen_union(gen_conc(gen_star(gen_atom("a", 0, TERMINAL)),
                                         gen_atom("b", 0, TERMINAL)),
                                gen_atom("S1", 0, NON_TERMINAL)));
  Rule *r2 = gen_rule("S1", gen_atom("S1", 0, NON_TERMINAL));
  mu_check(rule_equal(vector_get(A, 5), r1));
  mu_check(rule_equal(vector_get(A, 6), r2));

  gen_forest();
  init_stack();
  init_scan("S");
  scan();
  mu_check(!parse(S->body));
}

MU_TEST(lexer_gpl) {
  char *input = "var a;\n b := 1092;\n if (while && else) - a < > = C";
  Token *output[] = {
    gen_token("var", "var"),
    gen_token("ident", "a"),
    gen_token(";", ";"),
    gen_token("ident", "b"),
    gen_token(":=", ":="),
    gen_token("number", "1092"),
    gen_token(";", ";"),
    gen_token("if", "if"),
    gen_token("(", "("),
    gen_token("while", "while"),
    gen_token("&&", "&&"),
    gen_token("else", "else"),
    gen_token(")", ")"),
    gen_token("-", "-"),
    gen_token("ident", "a"),
    gen_token("<", "<"),
    gen_token(">", ">"),
    gen_token("=", "="),
    gen_token("ident", "C"),
    gen_token(END_FILE_STR, END_FILE_STR),
  };
  size_t i = 0;
  size_t out_len = sizeof(output) / sizeof(Token*);
  int index = 0;
  Token *t;

  do {
    t = lex_GPL(input, &index);
    mu_check(i < out_len);
    mu_check(!strcmp(t->type, output[i]->type));
    mu_check(!strcmp(t->str, output[i]->str));
    i++;
  } while (t->type != END_FILE_STR);
}

MU_TEST(parser_gpl) {
  gen_forest();
  vector_push(A, gen_rule("PGM", gen_star(gen_conc(gen_atom("var", 0, TERMINAL),
                                                   gen_conc(gen_atom("ident", 1, TERMINAL),
                                                            gen_atom(";", 0, TERMINAL))))));
  init_scan("var a; var b;");
  init_stack();
  init_parse();
  scan_GPL();
  Rule *S = vector_get(A, 5);
  mu_check(parse_GPL(S->body));
  mu_check(spx_start == 2);
}

MU_TEST(interpreter) {
  // 1 + 42
  spx_start = 0;
  p_code = empty_vector();
  p_code_push(LDC);
  p_code_push(1);
  p_code_push(LDC);
  p_code_push(42);
  p_code_push(ADD);
  p_code_push(STOP);
  interpret();
  mu_check(pilex_get(0) == 43);

  // a := 42; 1
  spx_start = 1;
  p_code = empty_vector();
  p_code_push(LDA);
  p_code_push(0);
  p_code_push(LDC);
  p_code_push(42);
  p_code_push(AFF);
  p_code_push(LDC);
  p_code_push(1);
  p_code_push(STOP);
  interpret();
  mu_check(pilex_get(0) == 42);
  mu_check(pilex_get(1) == 1);

  // a := 10; b := 1;
  spx_start = 2;
  p_code = empty_vector();
  p_code_push(LDA);
  p_code_push(0);
  p_code_push(LDC);
  p_code_push(10);
  p_code_push(AFF);
  p_code_push(LDA);
  p_code_push(1);
  p_code_push(LDC);
  p_code_push(1);
  p_code_push(AFF);
  // if a > 0 then b := b * 2; a := a - 1;
  p_code_push(LDV);
  p_code_push(0);
  p_code_push(JIF);
  p_code_push(32);
  p_code_push(LDA);
  p_code_push(1);
  p_code_push(LDV);
  p_code_push(1);
  p_code_push(LDC);
  p_code_push(2);
  p_code_push(MULT);
  p_code_push(AFF);
  p_code_push(LDA);
  p_code_push(0);
  p_code_push(LDV);
  p_code_push(0);
  p_code_push(LDC);
  p_code_push(1);
  p_code_push(SUB);
  p_code_push(AFF);
  p_code_push(JMP);
  p_code_push(10);
  p_code_push(STOP);
  interpret();
  mu_check(pilex_get(0) == 0);
  mu_check(pilex_get(1) == 1024);
}

int main() {
  MU_RUN_TEST(vectors);
  MU_RUN_TEST(ptr_test);
  MU_RUN_TEST(rule_test);
  MU_RUN_TEST(grammar_test);
  MU_RUN_TEST(lexer_g0);
  MU_RUN_TEST(parser_g0);
  MU_RUN_TEST(lexer_gpl);
  MU_RUN_TEST(parser_gpl);
  MU_RUN_TEST(interpreter);
  MU_REPORT();
  return 0;
}
