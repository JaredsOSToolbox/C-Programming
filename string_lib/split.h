#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN true
#define OUT false
#define NUMBER_OF_STRINGS 100
#define MAX_STRING_SIZE 200

char **split(char *string, char delimiter) {
  char **splitted;
  splitted = malloc(NUMBER_OF_STRINGS * sizeof(char *));
  for (int i = 0; i < NUMBER_OF_STRINGS; i++)
    splitted[i] = malloc((MAX_STRING_SIZE + 1) * sizeof(char));
  int operand_counter, j;
  char c;
  operand_counter = 0;
  j = 0;
  bool state = OUT;
  for (size_t i = 0; i < strlen(string); ++i) {
    c = string[i];
    if (c == delimiter) {
      j = 0;
      ++operand_counter;
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      splitted[operand_counter][j++] = c;
    } else {
      splitted[operand_counter][j++] = c;
    }
  }
  return splitted;
}

char *strtokm(char *str, const char *delim) {
  static char *tok;
  static char *next;
  char *m;

  if (delim == NULL) return NULL;

  tok = (str) ? str : next;
  if (tok == NULL) return NULL;

  m = strstr(tok, delim);
  printf("%s\n", m);

  if (m) {
    next = m + strlen(delim);
    *m = '\0';
  } else {
    next = NULL;
  }

  return tok;
}
size_t size_of_string_array(char **split_string) {
  size_t counter = 0;
  while (strlen(split_string[counter]) != 0) {
    ++counter;
  }
  return counter;
}

void print_split_string(char **split_string) {
  size_t size_ = size_of_string_array(split_string);
  for (int i = 0; i < size_; ++i) {
    fprintf(stdout, "%s\n", split_string[i]);
  }
}
