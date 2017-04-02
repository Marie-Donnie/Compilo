#include "interpreter.h"

void print_p_code(){
  int c0 = 0;
  int code;
  while (c0 < vector_length(p_code)){
    code = p_code_get(c0);
    printf("%d: ", c0);
    switch (code){
    case LDA:
      printf("LDA %d\n", p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case LDC:
      printf("LDC %d\n", p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case ADD:
      printf("ADD\n");
      c0 = c0 + 1;
      break;
    case SUB:
      printf("SUB\n");
      c0 = c0 + 1;
      break;
    case MULT:
      printf("MULT\n");
      c0 = c0 + 1;
      break;
    case DIV:
      printf("DIV\n");
      c0 = c0 + 1;
      break;
    case OR:
      printf("OR\n");
      c0 = c0 + 1;
      break;
    case AND:
      printf("AND\n");
      c0 = c0 + 1;
      break;
    case NOT:
      printf("NOT\n");
      c0 = c0 + 1;
      break;
    case EQ:
      printf("EQ\n");
      c0 = c0 + 1;
      break;
    case LT:
      printf("LT\n");
      c0 = c0 + 1;
      break;
    case GT:
      printf("GT\n");
      c0 = c0 + 1;
      break;
    case LEQ:
      printf("LEQ\n");
      c0 = c0 + 1;
      break;
    case GEQ:
      printf("GEQ\n");
      c0 = c0 + 1;
      break;
    case NEQ:
      printf("NEQ\n");
      c0 = c0 + 1;
      break;
    case JMP:
      printf("JMP %d\n", p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case JIF:
      printf("JIF %d\n", p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case AFF:
      printf("AFF\n");
      c0 = c0 + 1;
      break;
    default:
      printf("%d\n", code);
      c0 = c0 + 1;
    }
  }
}
