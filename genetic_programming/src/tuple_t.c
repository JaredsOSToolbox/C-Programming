#include "../includes/tuple_t.h"
#include <stdio.h>
#include <stdlib.h>

struct tuple_t* tuple_t_constructor(int x, int y) {
    struct tuple_t* t = (struct tuple_t*)malloc(sizeof(struct tuple_t));

    t->x = x;
    t->y = y;

    return t;
}

void tuple_t_destructor(struct tuple_t* t){
    free(t);
}


void tuple_t_print(struct tuple_t* t){
    printf("[tuple_t (%s) LOWER]: %llu\n", "filler_name", t->x);
    printf("[tuple_t (%s) UPPER]: %llu\n", "filler_name", t->y);
}
