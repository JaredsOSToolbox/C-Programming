#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_RESERVED_WORDS 15

typedef enum{
  ADD,
  SUB,
  DIV,
  MUL,
  MOD,
  SIN,
  COS,
  TAN,
  ASIN,
  ACOS,
  ATAN,
  FLOOR,
  POW,
  EXP,
  SQRT,
  VAR,
  NUMBER,
  GARBAGE,
  ASSIGN,
  RETRIEVE,
  SWAP,
  CLONE,
  LINEFEED,
  POP,
  PEEK,
  NOP, // no operation code
  PI,
  EXIT 
} operands;

const char* reserved_words[NUMBER_OF_RESERVED_WORDS] ={
  "SIN", "COS", "TAN", "SQRT", "POW", "EXP", "POP", "PI",
  "ASIN", "ACOS", "ATAN", "FLOOR", "CLONE", "SWAP", "PEEK"
};

int operand_code(char* element){
  char first_element = element[0];
  if(first_element == '='){ return ASSIGN; }
  if(first_element == '\n'){ return LINEFEED; }
  if(first_element == '?'){ return RETRIEVE; }
  if(isdigit(first_element)){ return NUMBER; }
  // function operand codes
  else if(strcmp(element, "SIN") == 0){ return SIN; }
  else if(strcmp(element, "COS") == 0){ return COS; }
  else if(strcmp(element, "TAN") == 0){ return TAN; }
  else if(strcmp(element, "POW") == 0){ return POW; }
  else if(strcmp(element, "ASIN") == 0){ return ASIN; }
  else if(strcmp(element, "ACOS") == 0){ return ACOS; }
  else if(strcmp(element, "ATAN") == 0){ return ATAN; }
  else if(strcmp(element, "SQRT") == 0){ return SQRT; }
  else if(strcmp(element, "EXP") == 0){ return EXP; }
  else if(strcmp(element, "FLOOR") == 0){ return FLOOR; }
  // large stack operations 
  else if(strcmp(element, "SWAP") == 0){ return SWAP; }
  else if(strcmp(element, "CLONE") == 0){ return CLONE; }
  else if(strcmp(element, "POP") == 0){ return POP; }
  else if(strcmp(element, "PEEK") == 0){ return PEEK; }

  // variable manipulation
  else if(strcmp(element, "=") == 0){ return ASSIGN; }
  // single operands
  else if(strcmp(element, "+") == 0){ return ADD; }
  else if(strcmp(element, "-") == 0){ return SUB; }
  else if(strcmp(element, "/") == 0){ return DIV; }
  else if(strcmp(element, "*") == 0){ return MUL; }
  else if(strcmp(element, "%") == 0){ return MOD; }
  else if(strcmp(element, "EXIT") == 0){ return EXIT; }

  // constants
  else if(strcmp(element, "PI") == 0){ return PI; }
  return GARBAGE;
}

bool is_var_name_valid_(char* variable_name){
  for(int i = 0; i < NUMBER_OF_RESERVED_WORDS; ++i){
    if(strcmp(variable_name, reserved_words[i]) == 0){ return false; }
  }
  return true;
}
