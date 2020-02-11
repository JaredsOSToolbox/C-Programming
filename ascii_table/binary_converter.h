#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BINARY_LEN 8
#define LABEL_COUNT 34
#define IN true
#define OUT false

// seq -s, 0 32
// cause I'm lazy 

int indexes[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,127,257};
char* labels[] = {"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "TAB", "LF", "VT", "FF", "CR", 
                  "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", 
                  "FS", "GS", "RS", "US", "SPACE", "DEL", "TL"};

// TL <- too long, not conventional ASCII

char* convert_int_array(int array[]){
  char* pointer = (char*)malloc(BINARY_LEN+1*sizeof(char));

  for(int i = 0; i < BINARY_LEN; ++i){
    if(array[i] == 1){ pointer[i] = '1'; }
    else{ pointer[i] = '0'; }
  }
  return pointer;
}

char* look_up(int index, int indexes[], char* labels[]){
  bool state = IN;
  for(int i = 0; i < LABEL_COUNT; ++i){
    if(indexes[i] == index){ 
      fprintf(stdout, "breaking with i: %d -----> index: %d\n", i, index);
      index = i;
      state = OUT;
      break; 
    }
  }
  if(state == IN){ index = LABEL_COUNT; }
  int size = strlen(labels[index]);
  char* pointer = (char*)malloc(size+1*sizeof(char));
  strcpy(pointer, labels[index]);
  return pointer;
}

void conversion(int array[], int base, FILE* output){
  int weight = 0;
  int len = BINARY_LEN;

  while(len-- > 0){
    weight+=array[(BINARY_LEN-1) - len]*(int)pow(2, len);
  }

  char* converted_array = convert_int_array(array);
  bool parity = (weight % 2 == 0);
  char* printable_char = (char*)malloc(1024*sizeof(char));
  char c = (char)weight;
  if(!isprint(c)){
    if(weight > 127){ weight = 257; }
    char* index = look_up(weight, indexes, labels);
    if(index != NULL){
      strcpy(printable_char, index);
      free(index);
    }
    else{
      fprintf(stderr, "Memory error!\n");
      free(converted_array);
      free(printable_char);
      exit(1);
    }
  }
  else{
    printable_char[0] = c ;
  }
  fprintf(output, "%s\t%s\t%d\t\t%s\n", converted_array, printable_char, weight, parity ? "even" : "odd");
  free(converted_array);
  free(printable_char);
}


void print_level(FILE* output, char c, size_t level){
  for(int i = 0;i < level; ++i){ fputc(c, output); }
  fputc('\n', output);
}

void process_file(FILE* input, FILE* output){
  char c;
  bool state = OUT;

  int array[BINARY_LEN];
  int i = 0;
  memset(array, 0, sizeof(array)/sizeof(int));
  const char* header = "Orig\t\tAscii\tBase-10\t\tParity";
  fprintf(output, "%s\n", header);
  print_level(output, '=', strlen(header)+18);

  while((c = fgetc(input)) != EOF){
    if(isspace(c)){
      state = IN;
      conversion(array, 2, output);
      i = 0;
      memset(array, 0, sizeof(array)/sizeof(int));
    }
    else{
     array[i++] = atoi(&c);
    }
  }
}
