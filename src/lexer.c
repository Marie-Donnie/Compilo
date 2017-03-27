#include "scanner.h"

FILE *file;



int char_count(char *file_name){
  FILE *file;
  char c;
  int count = 0;
  file = fopen(file_name, "r");
  while ((c=fgetc(file))!=EOF){
    count++;
  }
  fclose(file);
  return count;
}


void eat_space(){}

/*------------------- CHAR RECOGNITION -------------------------*/

bool might_be_double(char c){
  return (c == '<' || c == '=' || c == '!' || c == '>' || c == '|'
	  || c == '&' || c == '+' || c == '-');
}

Token lex(char *string, int *index){
  Token token;
  token.str = NULL;
  int state = 0;
  int count = 0;
  char *c = string + *index;
  while ( *(c = string + *index) != '\0'){
    switch(state){
    case 0:
      if (*c == ' ' || *c == '\t' || *c == '\n'){
	*index += 1;
	continue; // to while
      }
      else if (*c == '.'){
	*index += 1;
	token.type = POINT;
	return token;
      }
      else if (*c == ','){
	*index += 1;
	token.type = C;
	return token;
      }
      else if (*c == ';'){
      	*index += 1;
	token.type = SC;
	return token;
      }
      else if (*c == '-' && *(c+1) == '>'){
	*index += 2;
	token.type = ARROW;
	return token;
      }
      else if (*c == '['){
	*index += 1;
	token.type = LB;
	return token;
      }
      else if (*c == ']'){
	*index += 1;
	token.type = RB;
	return token;
      }
      else if (*c == '\''){
	count = 0;
	*index += 1;
	while (*(string + *index + count) != '\''){
	  count++;
	}
	token.str = malloc(sizeof(char)*(count+1));
	strncpy(token.str, string + *index, count);
	token.str[count] = '\0';
	token.type = TER;
	*index += count + 1;
	return token;
      }
      break;
    case 1:
      break;
    }
  }
  token.type = EF;
  return token;
}


/*------------------- SCAN -------------------------*/

/* Lexical_unit* scan(char* chaine){ */

/*   /\* Terminal si " " ou entier, NT tout le reste qui n'est pas blanc *\/ */
/*   /\* On accepte pas un nom de variable type 1toto, mais toto1 oui *\/ */
/*   /\* Construit trois listes différentes pour blancs (nouvelle page, espace, retour chariot, etc.), unité lexicale (tout ce qui n'est pas un blanc), et les opérateurs *\/ */

/*   return NULL; */
/* } */
