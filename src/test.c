#include <stdbool.h>
#include "minunit.h"
#include "sets.h"
#include "vector.h"
#include "lexer.h"

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

int main() {
  MU_RUN_TEST(sets);
  MU_RUN_TEST(vectors);
  MU_RUN_TEST(lexer);
  MU_REPORT();
  return 0;
}
