#include "lexer_GPL.h"


Token* lex_GPL(char *string, int *index){
  char *str;
  int count = 0;
  char *c = string + *index;
  while ( *(c = string + *index) != '\0'){
    if (*c == ' ' || *c == '\t' || *c == '\n'){
      *index += 1;
      continue;
    }
    else if (*c == ':' && *(c+1) == '='){
      *index += 2;
      return gen_token(":=", ":=");
    }
    else if (*c == ';'){
      *index += 1;
      return gen_token(";", ";");
    }
    else if (*c  == '+'){
      *index += 1;
      return gen_token("+", "+");
    }
    else if (*c == '-'){
      *index += 1;
      return gen_token("-", "-");
    }
    else if (*c == '*'){
      *index += 1;
      return gen_token("*", "*");
    }
    else if (*c == '/'){
      *index += 1;
      return gen_token("/", "/");
    }
    else if (*c == '|' && *(c+1) == '|'){
      *index += 2;
      return gen_token("||", "||");
    }
    else if (*c == '&' && *(c+1) == '&'){
      *index += 2;
      return gen_token("&&", "&&");
    }
    else if (*c == '!' && *(c+1) == '='){
      *index += 2;
      return gen_token("!=", "!=");
    }
    else if (*c == '!'){
      *index += 1;
      return gen_token("!", "!");
    }
    else if (*c == '<' && *(c+1) == '='){
      *index += 2;
      return gen_token("<=", "<=");
    }
    else if (*c == '>' && *(c+1) == '='){
      *index += 2;
      return gen_token(">=", ">=");
    }
    else if (*c == '<'){
      *index += 1;
      return gen_token("<", "<");
    }
    else if (*c == '>'){
      *index += 1;
      return gen_token(">", ">");
    }
    else if (*c == '='){
      *index += 1;
      return gen_token("=", "=");
    }
    else if (is_letter(*c)){
      count = 0;
      do {
	count++;
	c = string + *index + count;
      } while (is_letter(*c) || is_digit(*c) || (*c=='#'));
      //TODO strdup
      str = malloc(sizeof(char)*(count+1));
      strncpy(str, string + *index, count);
      str[count] = '\0';
      *index += count;
      if (!strcmp(str, "var")){
	return gen_token("var", "var");
      }
      else if (!strcmp(str, "true")){
	return gen_token("true", "true");
      }
      else if (!strcmp(str, "false")){
	return gen_token("false", "false");
      }
      else if (!strcmp(str, "if")){
	return gen_token("if", "if");
      }
      else if (!strcmp(str, "then")){
	return gen_token("then", "then");
      }
      else if (!strcmp(str, "else")){
	return gen_token("else", "else");
      }
      else if (!strcmp(str, "while")){
	return gen_token("while", "while");
      }
      else if (!strcmp(str, "do")){
	return gen_token("do", "do");
      }
      return gen_token("ident", str);
    }
    else if (is_digit(*c)){
      count = 0;
      do {
	count++;
	c = string + *index + count;
      } while (is_digit(*c) || (*c=='#'));
      //TODO strdup
      str = malloc(sizeof(char)*(count+1));
      strncpy(str, string + *index, count);
      str[count] = '\0';
      *index += count;
      return gen_token("number", str);
    }
  }
  return gen_token(END_FILE_STR, END_FILE_STR);
}



void scan_GPL(){
  scan_state.token = lex_GPL(scan_state.buffer, &scan_state.index);
}
