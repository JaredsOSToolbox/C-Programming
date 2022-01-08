#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    char* line;
    size_t len = 0;
    ssize_t read;
    int line_number_ = 1;

    while ((read = getline(&line, &len, stdin)) != EOF) {
        size_t size_ = strlen(line);
        if (size_ > 0) {
            for (int j = size_; j >= 0; --j) {
                char c = line[j];
                if (c != '\n' && c != '\0') {
                    printf("%c", line[j]);
                }
            }
            printf("\n\0");
        }
    }
    return 0;
}
