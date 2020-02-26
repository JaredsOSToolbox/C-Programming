#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "parser.h" // get the operand codes
#include "hash_table.h" // store the variable values (python dictionary equivalent)
#include "split.h" // split the string into string of strings (python string.split() function)
#include "stack.h" // pushing, popping, peeking on the stack
#include "rpn_calculator.h" // all the math functionality of this program. Please refer to this header and parser.h to implement more math functions

// all code here and in local imports written by Jared Dyreson, California State University Fullerton (889546529)

int main(int argc, const char* argv[]){
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int operand_code_value_, previous_operand_code_value_;
  char* pointer;
  double value_;
  struct hash_table* map = new_hash_table();
  bool break_condition = false;
  double* cloned_stack = NULL;

  while ((read = getline(&line, &len, stdin)) != EOF && !break_condition) {
    char** chunk = split(line);
    size_t size_ = size_of_string_array(chunk);
    // if we did not ingest anything, it is a new line
    if(size_ == 0){ 
      // if we did an assignment, there will be nothing on the stack
      // then we need to send a no operation code to the calculator function (pass equivalent in python)
      if(previous_operand_code_value_ != ASSIGN){ rpn_calc(LINEFEED); }
      else{ rpn_calc(NOP); }
    }
    for(int i = 0; i < size_; ++i){
     operand_code_value_ = operand_code(chunk[i]);
     switch(operand_code_value_){
       case NUMBER:
        push(strtod(chunk[i], &pointer));
        break;
       case GARBAGE:
        fprintf(stderr, "got garbage value from operand of value: %s\n", chunk[i]);
        clear_stack();
        break;
       case ASSIGN:
        // we want to remove the first element in the buffer, then move pointer along
        memmove(chunk[i], chunk[i]+1, strlen(chunk[i]));
        if(is_var_name_valid_(chunk[i])){
          value_ = pop();
          insert(map, chunk[i], value_);
          fprintf(stdout, "inserted key: %s with value of: %g\n", chunk[i], value_);
          break;
        }
        break;
       case RETRIEVE:
        memmove(chunk[i], chunk[i]+1, strlen(chunk[i]));
        push(get_key(map, chunk[i]));
        fprintf(stdout, "retrieved key: %s with value of: %g\n", chunk[i], peek());
        break;
       case CLONE:
        cloned_stack = duplicate_stack();
        fprintf(stdout, "cloned the stack!\n");
        break;
       case EXIT:
        break_condition = true;
        break;
       default: 
        rpn_calc(operand_code_value_);
        break;
     }
    }
    free(chunk);
    previous_operand_code_value_ = operand_code_value_;
  }
  // we need to free the memory we allocated throughout the lifetime of the program
  if(line != NULL){ free(line); }
  else if(cloned_stack != NULL){ free(cloned_stack); }
  destructor_(map);
  return 0;
}
