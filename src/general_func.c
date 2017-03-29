#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

long char_count(FILE *file){
  long index = ftell(file);
  long count;
  fseek(file, 0, SEEK_END);
  count = ftell(file);
  fseek(file, index, SEEK_SET);
  return count;
}

char* read_file(char *path){
  FILE *file;
  char *buffer;
  long buffer_size;
  file = fopen(path, "r");
  buffer_size = char_count(file);
  buffer = malloc(buffer_size*sizeof(char));
  fread(buffer, sizeof(char), buffer_size, file);
  fclose(file);
  return buffer;
}

void* check_malloc(size_t size){
  void* ret = malloc(size);
  if (!ret){
    fprintf(stderr, "Cannot allocate memory");
    exit(-1);
  }
  return ret;
}

void* check_realloc(void* p, size_t size){
  void* ret = realloc(p, size);
  if (!ret){
    fprintf(stderr, "Cannot allocate memory");
    exit(-1);
  }
  return ret;
}

void fail(char *msg){
  fprintf(stderr, "%s\n", msg);
  exit(1);
}


void eat_space(){}

bool might_be_double(char c){
  return (c == '<' || c == '=' || c == '!' || c == '>' || c == '|'
	  || c == '&' || c == '+' || c == '-');
}

/*------------------- SCAN -------------------------*/

/* void scan(char* chaine){ */

/*   /\* Terminal si " " ou entier, NT tout le reste qui n'est pas blanc *\/ */
/*   /\* On accepte pas un nom de variable type 1toto, mais toto1 oui *\/ */
/*   /\* Construit trois listes différentes pour blancs (nouvelle page, espace, retour chariot, etc.), unité lexicale (tout ce qui n'est pas un blanc), et les opérateurs *\/ */

/*   return NULL; */
/* } */
