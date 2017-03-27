#include "sets.h"


Set* empty_set(){
  Set *set = malloc(sizeof(Set));
  set->size = 0;
  set->nb_elem = 0;
  set->set = NULL;
  return set;
}

void set_add(Set *set, Token *token){
  if (!set_is_member(set, token)){
    if (set->nb_elem == set->size){
      size_t new_size = (set->size == 0 ? 5 : set->size * 2);
      set->set = realloc(set->set, new_size);
      if (!set->set){
	fprintf(stderr, "Cannot allocate memory");
	exit(-1);
      }
      set->size = new_size;
    }
    set->set[set->nb_elem] = token;
    set->nb_elem++;
  }
}

bool set_is_member(const Set *set, const Token *token){
  size_t i;
  for (i = 0 ; i < set->nb_elem ; i++){
    if (set->set[i] == token){
      return true;
    }
  }
  return false;
}

void set_union(Set *set1, const Set *set2){
  size_t i;
  for (i = 0 ; i < set2->nb_elem ; i++){
    set_add(set1, set2->set[i]);
  }
}
