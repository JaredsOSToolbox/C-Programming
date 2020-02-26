#include <stdio.h>

void rpn_calc(int operand_code){
  double operand_one, operand_two;
  switch(operand_code){
    case LINEFEED: 
      if(stack_pointer_ != 0){ fprintf(stdout, "\t%.8g\n", peek()); }
      break;
    case POP:
      // force a pop operation
      fprintf(stdout, "\t%.8g\n", pop()); 
      break;
    case PEEK:
      fprintf(stdout, "\t%.8g\n", peek()); 
      break;
    case ADD:
      push(pop() + pop());
      break;
    case SUB:
      push(-(pop() - pop()));
      break;
    case MUL:
      push(pop() * pop());
      break;
    case DIV:
      operand_two = pop();
      if(operand_two == 0.0){
        fprintf(stderr, "divide by zero exception thrown, cowardly refusing!\n");
        break;
      }
      push(pop() / operand_two);
      break;
    case MOD:
      operand_two = pop();
      push(fmod(pop(), operand_two));
      break;
    case SIN:
      push(sin(pop()));
      break;
    case COS:
      push(cos(pop()));
      break;
    case TAN:
      push(tan(pop()));
      break;
    case ASIN:
      push(asin(pop()));
      break;
    case ACOS:
      push(acos(pop()));
      break;
    case ATAN:
      push(atan(pop()));
      break;
    case FLOOR:
      push(floor(pop()));
      break;
    case EXP:
      push(exp(pop()));
      break;
    case POW:
      operand_two = pop();
      push(pow(pop(), operand_two));
      break;
    case SQRT:
      push(pow(pop(), 0.5));
      break;
    case SWAP:
      fprintf(stdout, "peeking 1st: %g and 2nd: %g\n", peek_n(1), peek_n(2));
      operand_one = pop();
      operand_two = pop();
      push(operand_one);
      push(operand_two);
      break;
    case NOP: break;
    case PI:
      push(M_PI);
      break;
    default:
      fprintf(stderr, "got an error with op_code %d\n", operand_code);
      break;
  }
  //if(operand_code != POP){
    //fprintf(stdout, "\t%.8g\n", pop());
  //}
}
