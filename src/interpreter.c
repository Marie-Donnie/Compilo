#include "interpreter.h"

Vector *pilex;


void interpret(){
  pilex = empty_vector();
  // reserved variables initialized to zero
  while (spx_start > 0){
    pilex_push(0);
    spx_start--;
  }
  int c0 = 0;
  int code = p_code_get(c0);
  int a, b;
  char buf[MAX_BUF_SIZE];

  while (code != STOP){
    code = p_code_get(c0);
    switch (code){
    case LDA:
    case LDC:
      pilex_push(p_code_get(c0 + 1));
      c0 = c0 + 2;
      break;
    case LDV:
      pilex_push(pilex_get(p_code_get(c0 + 1)));
      c0 = c0 + 2;
      break;
    case ADD:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a + b);
      c0 = c0 + 1;
      break;
    case SUB:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a - b);
      c0 = c0 + 1;
      break;
    case MULT:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a * b);
      c0 = c0 + 1;
      break;
    case DIV:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a / b);
      c0 = c0 + 1;
      break;
    case OR:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a || b);
      c0 = c0 + 1;
      break;
    case AND:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a && b);
      c0 = c0 + 1;
      break;
    case NOT:
      pilex_push(!pilex_pop());
      c0 = c0 + 1;
      break;
    case EQ:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a == b);
      c0 = c0 + 1;
      break;
    case LT:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a < b);
      c0 = c0 + 1;
      break;
    case GT:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a > b);
      c0 = c0 + 1;
      break;
    case LEQ:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a <= b);
      c0 = c0 + 1;
      break;
    case GEQ:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a >= b);
      c0 = c0 + 1;
      break;
    case NEQ:
      b = pilex_pop();
      a = pilex_pop();
      pilex_push(a != b);
      c0 = c0 + 1;
      break;
    case JMP:
      c0 = p_code_get(c0 + 1);
      break;
    case JIF:
      if (pilex_pop()){
	c0 = c0 + 2;
      }
      else{
	c0 = p_code_get(c0 + 1);
      }
      break;
    case AFF:
      b = pilex_pop();
      a = pilex_pop();
      pilex_set(a, b);
      c0 = c0 + 1;
      break;
    case READ:
      read(fileno(stdin), buf, MAX_BUF_SIZE);
      pilex_push(atoi(buf));
      c0 = c0 + 1;
      break;
    case WRITE:
      printf("%d\n", pilex_pop());
      c0 = c0 + 1;
      break;
    case STOP:
      break;
    default:
      printf("Unknown opcode: %d\n", code);
      c0 = c0 + 1;
    }
  }
}



void print_p_code(){
  int c0 = 0;
  int code = p_code_get(c0);
  while (code != STOP){
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
    case LDV:
      printf("LDV %d\n", p_code_get(c0 + 1));
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
    case READ:
      printf("READ\n");
      c0 = c0 + 1;
      break;
    case WRITE:
      printf("WRITE\n");
      c0 = c0 + 1;
      break;
    case STOP:
      printf("STOP\n");
      c0 = c0 + 1;
      break;
    default:
      printf("Unknown opcode: %d\n", code);
      c0 = c0 + 1;
    }
  }
}


void pilex_push(int code){
  vector_push(pilex, gen_code(code));

}

void pilex_set(int index, int code){
    pilex->elts[index] = gen_code(code);
}

int pilex_pop(){
  Code *c = vector_pop(pilex);
  return c->val;
}

int pilex_get(int index){
  Code *c = vector_get(pilex, index);
  return c->val;
}

void print_pilex(){
  printf("<");
  for (int i = 0 ; i < vector_length(pilex) ; i++){
    printf("%d, ", pilex_get(i));
  }
  printf(">\n");
}
