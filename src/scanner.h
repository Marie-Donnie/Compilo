#include "definitions.h"

typedef enum {ID, ARROW, TER, PLUS, POINT, LB, RB, LP, RP, LPB, RPB, C, SC, EF} TokenType;
typedef struct {
  TokenType type;
  char *str;
} Token;


/*------------------- GENERIC -------------------------*/

int char_count(char *file_name);


void eat_space();

/*------------------- CHAR RECOGNITION -------------------------*/

bool might_be_double(char c);
bool is_double(char c, char cc);

void lexical_unit_gen(Token token);

Token scanner(char *string, int *index);


/*------------------- SCAN -------------------------*/
Lexical_unit* scan(char* chaine);
