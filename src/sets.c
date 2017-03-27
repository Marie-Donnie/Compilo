#include "sets.h"


Set* empty_set(){
  Set *set = malloc(sizeof(Set));
  set->size = 0;
  set->set = NULL;
  return set;
}

const Set* set_add(const Set *set, const void *e){
  if (!set_is_member(set, e)){
    Set *ret_set = empty_set();
    ret_set->set = check_malloc((set->size+1)*sizeof(e));
    ret_set->size = set->size + 1;
    memcpy(ret_set->set, set->set, (set->size)*sizeof(e));
    ret_set->set[set->size] = e;
    return ret_set;
  }
  return set;
}

bool set_is_member(const Set *set, const void *e){
  size_t i;
  for (i = 0 ; i < set->size ; i++){
    if (set->set[i] == e){
      return true;
    }
  }
  return false;
}

const Set* set_union(const Set *set1, const Set *set2){
  Set *ret_set = empty_set();
  ret_set->set = check_malloc((set1->size + set2->size)*sizeof(void*));
  ret_set->size = set1->size + set2->size;
  memcpy(ret_set->set, set1->set, set1->size*sizeof(void*));
  memcpy((ret_set->set + set1->size), set2->set, set2->size*sizeof(void*));
  return ret_set;
}

const Set* set_remove(const Set *set, const void *e){
  size_t i, j;
  if (set_is_member(set, e)){
    Set *ret_set = empty_set();
    ret_set->set = check_malloc((set->size-1)*sizeof(e));
    ret_set->size = set->size - 1;
    for (i = 0, j = 0 ; i < set->size ; i++){
      if (set->set[i] != e){
	ret_set->set[j] = set->set[i];
	j++;
      }
    }
    return ret_set;
  }
  return set;
}
