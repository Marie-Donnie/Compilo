#ifndef LEXER_H
#define LEXER_H
#include "definitions.h"

typedef enum {IDENT, ARROW, TER, PLUS, POINT,
	      L_BRACKET, R_BRACKET, L_PAREN, R_PAREN,
	      L_PAREN_BAR, R_PAREN_BAR, COMMA, SEMI_COLON,
	      END_FILE} TokenType;
typedef struct {
  TokenType type;
  char *str;
} Token;


/*------------------- CHAR RECOGNITION -------------------------*/


bool is_letter(char c);
bool is_digit(char c);


/*------------------- LEX G0 -------------------------*/
Token lex(char *string, int *index);


#endif //LEXER_H
