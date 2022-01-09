// Written by Jared Dyreson
// California State University Fullerton, 2020

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_STRINGS 100
#define MAX_STRING_SIZE 200

void our_strcpy(char *source, char *destination) {
    int i;
    for (i = 0; i < strlen(source); ++i) {
        destination[i] = source[i];
    }
}

int cstring_cmp(const void *a, const void *b) {
    /*https://cboard.cprogramming.com/c-programming/148152-using-qsort-string-array.html*/
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <lyric input file> <sorted output file>\n",
                argv[0]);
        exit(1);
    }

    char **allocated_buffer;
    char **place_holder = allocated_buffer;
    allocated_buffer = malloc(NUMBER_OF_STRINGS * sizeof(char *));

    for (int i = 0; i < NUMBER_OF_STRINGS; i++) {
        allocated_buffer[i] = malloc((MAX_STRING_SIZE + 1) * sizeof(char));
    }

    char *line;
    size_t len = 0;
    ssize_t read;
    int line_number_ = 0;

    FILE *file_in = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if ((file_in == NULL) || (output_file == NULL)) {
        fprintf(stderr, "Could not open file, cowardly refusing!\n");
        fclose(file_in);
        fclose(output_file);
        exit(1);
    }

    while ((read = getline(&line, &len, file_in)) != EOF) {
        our_strcpy(line, allocated_buffer[line_number_]);
        ++line_number_;
    }

    // https://stackoverflow.com/questions/14993282/qsort-did-not-sort-the-array-of-string
    // call to qsort confusing in the book, used this one

    qsort(allocated_buffer, line_number_, sizeof(char *), cstring_cmp);

    for (int i = 0; i < line_number_; ++i) {
        fprintf(output_file, "[%d]: %s", i, allocated_buffer[i]);
    }

    for (int i = 0; i < NUMBER_OF_STRINGS; ++i) {
        free(allocated_buffer[i]);
    }

    free(allocated_buffer);
    fclose(file_in);
    fclose(output_file);

    return 0;
}

