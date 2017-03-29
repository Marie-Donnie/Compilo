#include <stdbool.h>
#include "minunit.h"
#include "sets.h"
#include "vector.h"

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

int main() {
  MU_RUN_TEST(sets);
  MU_RUN_TEST(vectors);
  MU_REPORT();
  return 0;
}
