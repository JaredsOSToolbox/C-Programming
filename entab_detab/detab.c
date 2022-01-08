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
    char buffer[MAX_LINE_LEN];
    int buffer_index = 0;

    char replace[TARGET_WEIGHT];
    char space_catch_all[80];
    char c;

    memset(replace, replacement, sizeof(replace));
    memset(buffer, 0, sizeof(buffer));
    for (int i = 0; i < strlen(line); ++i) {
        c = line[i];
        if (c != target) {
            buffer[buffer_index++] = c;
        } else {
            int position = TARGET_WEIGHT - (buffer_index % TARGET_WEIGHT);
            strncpy(space_catch_all, replace, position);
            space_catch_all[position] = '\0';
            buffer_put(space_catch_all, buffer, buffer_index);
            buffer_index += position;
        }
    }
    fprintf(stdout, "size of output: %d bytes\n", buffer_index);
    fprintf(output, "%s", buffer);
}

int main(int argc, const char* argv[]) {
    FILE* out = fopen("/tmp/detab_output.txt", "w");
    FILE* in = fopen("inputs/detab_input", "r");

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, in)) != EOF) {
        process_line(out, line, '\t', ' ');
    }

    if (line != NULL) {
        free(line);
    }
    fclose(in);
    fclose(out);
}
