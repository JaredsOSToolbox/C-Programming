#include <stdio.h>

#define STACK_SIZE 100
int stack_pointer_ = 0;
static double stack[STACK_SIZE];

void push(double value){
  if(stack_pointer_ == STACK_SIZE){
    fprintf(stderr, "cannot push to stack, it is full!\n");
    return;
  }
  stack[stack_pointer_++] = value;
}

double peek(){
  if(stack_pointer_ == 0){
    fprintf(stderr, "cannot peek value, stack is empty!\n");
    return 0.0;
  }
  return stack[stack_pointer_-1];
}

double peek_n(int position){
  if((stack_pointer_ - position) > 0){
    fprintf(stderr, "cannot peek that far!\n");
  }
  return stack[stack_pointer_-position];
}

double pop(){
  if(stack_pointer_ == 0){
    fprintf(stderr, "cannot pop value, stack is empty!\n");
    return 0.0;
  }
  return stack[--stack_pointer_];
}

void clear_stack(){
  while(--stack_pointer_ > 0){
    pop();
  }
}

double* duplicate_stack(){
  double* duplicated_stack = (double*) malloc(STACK_SIZE * sizeof(double));
  for(int i = 0; i < STACK_SIZE; ++i){
    duplicated_stack[i] = stack[i];
  }
  return duplicated_stack;
}
