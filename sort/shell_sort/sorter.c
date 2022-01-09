#include <stdio.h>
#include <time.h>

#include "shell_sort.h"

int main(int argc, const char* argv[]) {
    int hello[] = {22, 21, 12, 0, 23, 56, 1};
    clock_t s, e;
    double cpu_time_;
    s = clock();
    shell_sort_(hello, 7);
    e = clock();
    cpu_time_ = ((double)(e - s)) / CLOCKS_PER_SEC;
    fprintf(stdout, "Sorted in %f seconds\n", cpu_time_);
    for (int i = 0; i < 7; ++i) {
        fprintf(stdout, "%d\n", hello[i]);
    }
    return 0;
}
