#ifndef LEXER_H
#define LEXER_H
#include "definitions.h"

extern char* END_FILE_STR;

typedef struct {
  char *type;
  char *str;
  int action;
} Token;


/*------------------- CHAR RECOGNITION -------------------------*/


bool is_letter(char c);
bool is_digit(char c);


/*------------------- LEX G0 -------------------------*/
Token* lex(char *string, int *index);
Token* gen_token(char *type, char* str);

void scan();
void init_scan(char *input);
Token* scan_token();

#endif //LEXER_H
