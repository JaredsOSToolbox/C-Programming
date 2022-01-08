#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_WEIGHT 2
#define MAX_LINE_LEN 100000

void buffer_put(char* source, char* destination, int index) {
  for (int i = 0; i < strlen(source); ++i) {
    destination[index++] = source[i];
  }
}

void process_line(FILE* output, char* line, char target, char replacement) {
  int target_counter = 1;
  char c;

  for (int i = 0; i < strlen(line); ++i) {
    c = line[i];
    if (c == target) {
      ++target_counter;
      if ((target_counter % TARGET_WEIGHT) == 0) {
        int n_replacement = target_counter / TARGET_WEIGHT;
        int n_target = target_counter % TARGET_WEIGHT;
        while (n_replacement-- > 0) {
          fputc(replacement, output);
        }
        while (n_target-- > 0) {
          fputc(target, output);
        }
        target_counter = 1;
      }
    } else {
      fputc(c, output);
    }
  }
}

void print_tab_literal(FILE* output, char* line) {
  for (int i = 0; i < strlen(line); ++i) {
    if (line[i] == '\t') {
      fprintf(output, "^I");
    } else {
      fputc(line[i], output);
    }
  }
}

int main(int argc, const char* argv[]) {
  FILE* out = fopen("/tmp/entab_output.txt", "w");
  FILE* in = fopen("inputs/entab_input", "r");

  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, in)) != EOF) {
    process_line(out, line, ' ', '\t');
  }

  if (line != NULL) {
    free(line);
  }
  fclose(in);
  fclose(out);
}
