#include "lexer.h"

char* END_FILE_STR = "end_file";


/*------------------- CHAR RECOGNITION -------------------------*/


bool is_letter(char c){
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool is_digit(char c){
  return (c >= '0' && c <= '9');
}


/*------------------- LEX G0 -------------------------*/
Token lex(char *string, int *index){
  Token token;
  token.str = NULL;
  int count = 0;
  char *c = string + *index;
  while ( *(c = string + *index) != '\0'){
    if (*c == ' ' || *c == '\t' || *c == '\n'){
      *index += 1;
      continue;
    }
    else if (*c == '.'){
      *index += 1;
      token.type = POINT;
      return token;
    }
    else if (*c == ','){
      *index += 1;
      token.type = COMMA;
      return token;
    }
    else if (*c == ';'){
      *index += 1;
      token.type = SEMI_COLON;
      return token;
    }
    else if (*c == '-' && *(c+1) == '>'){
      *index += 2;
      token.type = ARROW;
      return token;
    }
    else if (*c  == '+'){
      *index += 1;
      token.type = PLUS;
      return token;
    }
    else if (*c == '['){
      *index += 1;
      token.type = L_BRACKET;
      return token;
    }
    else if (*c == ']'){
      *index += 1;
      token.type = R_BRACKET;
      return token;
    }
    else if (*c == '(' && *(c+1) != '|'){
      *index += 1;
      token.type = L_PAREN;
      return token;
    }
    else if (*c == ')'){
      *index += 1;
      token.type = R_PAREN;
      return token;
    }
    else if (*c == '(' && *(c+1) == '|'){
      *index += 2;
      token.type = L_PAREN_BAR;
      return token;
    }
    else if (*c == '|' && *(c+1) == ')'){
      *index += 2;
      token.type = R_PAREN_BAR;
      return token;
    }
    else if (*c == '\''){
      count = 0;
      *index += 1;
      while (*(string + *index + count) != '\''){
	count++;
      }
      token.str = malloc(sizeof(char)*(count+1)); // +1 for \0
      strncpy(token.str, string + *index, count);
      token.str[count] = '\0';
      token.type = TER;
      *index += count + 1; // +1 for '
      return token;
    }
    else if (is_letter(*c)){
      count = 0;
      do {
	count++;
	c = string + *index + count;
      }
      while (is_letter(*c) || is_digit(*c));
      token.str = malloc(sizeof(char)*(count+1));
      strncpy(token.str, string + *index, count);
      token.str[count] = '\0';
      token.type = IDENT;
      *index += count;
      return token;
    }
  }
  token.type = END_FILE;
  token.str = END_FILE_STR;
  return token;
}

Token* gen_token(TokenType type, char* str){
  Token *t = malloc(sizeof(Token));
  t->type = type;
  t->str = str;
  return t;
}
