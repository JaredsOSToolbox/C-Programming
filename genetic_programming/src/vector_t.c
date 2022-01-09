#include "../includes/vector_t.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MUTATION 0.01
#define CROSSOVER 0.5

#define BIT_FIELD_SIZ 22
#define BIN_LEN 8

struct vector_t* vector_t_constructor(int base_ten) {
    struct vector_t* vec = (struct vector_t*)malloc(sizeof(struct vector_t));

    vec->associate_number = base_ten;
    vec->position = 0;
    vec->size = BIT_FIELD_SIZ;

    int* arr = (int*)malloc(sizeof(int) * BIT_FIELD_SIZ);
    memset(arr, 0, BIT_FIELD_SIZ);

    vec->data = arr;
    vector_t_update_array(vec, base_ten);

    return vec;
}

void vector_t_destructor(struct vector_t* vec) {
    free(vec->data);
    free(vec);
}

void vector_t_update_array(struct vector_t* vec, int number) {
    for (int i = 0; i < vec->size; ++i) {
        vec->data[i] = !!((number << i) & 0x80);
    }
}

void vector_t_print(FILE* fd, struct vector_t* vec) {
    printf("[vector_t: %s] Bit Field: ", "filler_name");
    for (int i = 0; i < vec->size; ++i) {
        fprintf(fd, "%d ", vec->data[i]);
    }
    printf("\n");
    printf("[vector_t: %s] Base Ten: %d\n", "example",
           vec->associate_number);
}
