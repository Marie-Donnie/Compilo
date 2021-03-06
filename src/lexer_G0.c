#include "lexer_G0.h"

char* END_FILE_STR = "end_file";


/*------------------- CHAR RECOGNITION -------------------------*/


bool is_letter(char c){
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool is_digit(char c){
  return (c >= '0' && c <= '9');
}


/*------------------- LEX G0 -------------------------*/
Token* lex(char *string, int *index){
  char *str;
  int count = 0;
  char *c = string + *index;
  while ( *(c = string + *index) != '\0'){
    if (*c == ' ' || *c == '\t' || *c == '\n'){
      *index += 1;
      continue;
    }
    else if (*c == '.'){
      *index += 1;
      return gen_token(".", ".");
    }
    else if (*c == ','){
      *index += 1;
      return gen_token(",", ",");
    }
    else if (*c == ';'){
      *index += 1;
      return gen_token(";", ";");
    }
    else if (*c == '-' && *(c+1) == '>'){
      *index += 2;
      return gen_token("->", "->");
    }
    else if (*c  == '+'){
      *index += 1;
      return gen_token("+", "+");
    }
    else if (*c == '['){
      *index += 1;
      return gen_token("[", "[");
    }
    else if (*c == ']'){
      *index += 1;
      return gen_token("]", "]");
    }
    else if (*c == '(' && *(c+1) != '|'){
      *index += 1;
      return gen_token("(", "(");
    }
    else if (*c == ')'){
      *index += 1;
      return gen_token(")", ")");
    }
    else if (*c == '(' && *(c+1) == '|'){
      *index += 2;
      return gen_token("(|", "(|");
    }
    else if (*c == '|' && *(c+1) == ')'){
      *index += 2;
      return gen_token("|)", "|)");
    }
    else if (*c == '\''){
      count = 0;
      *index += 1;
      while (*(string + *index + count) != '\''){
	count++;
      }
      str = strndup(string + *index, count);
      *index += count + 1; // +1 for '
      return gen_token("ELTER", str);
    }
    else if (is_letter(*c)){
      count = 0;
      do {
	count++;
	c = string + *index + count;
      }
      while (is_letter(*c) || is_digit(*c) || (*c=='#'));
      str = strndup(string + *index, count);
      *index += count;
      return gen_token("IDNTER", str);
    }
  }
  return gen_token(END_FILE_STR, END_FILE_STR);
}

void scan(){
  scan_state.token = lex(scan_state.buffer, &scan_state.index);
}

void init_scan(char *input){
  scan_state.index = 0;
  scan_state.buffer = input;
}

Token *scan_token(){
  return scan_state.token;
}


Token* gen_token(char *type, char* str){
  Token *t = check_malloc(sizeof(Token));
  char *s = index(str, '#');
  if (s != NULL){
    t->str = strndup(str, s - str);
    t->action = atoi(s+1);
  }
  else {
    t->str = str;
    t->action = 0;
  }
  t->type = type;
  return t;
}
