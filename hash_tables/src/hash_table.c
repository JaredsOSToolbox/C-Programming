#include "../includes/hash_table.h"

#include <stdio.h>
#include <stdlib.h>

void test_hash_node() {
    hash_node* n = hash_node_constructor("Jared");
    hash_node_repr(n);
    printf("\n");
}

void test_hash_node_list() {
    hash_node_list* list = hash_node_list_constructor();
    for (int i = 0; i < 10; ++i) {
        hash_node_list_addfront(list, "Jared");
    }
    hash_node_list_print(list);
    hash_node_list_destructor(list);
}

void test_hash_table() {
    printf("//----------------- TESTING HASH TABLE -----------\n");
    struct hash_table* map = new_hash_table();
    insert(map, "Cheese", "something that is made of cheese");
    insert(map, "Cat", "animal that likes fish");
    insert(map, "Dog", "animal that hates cats");
    insert(map, "virus", "pain in my ass");

    get_key(map, "Cheese");
    get_key(map, "Cat");
    get_key(map, "Dog");
    get_key(map, "virus");

    get_key(map, "pig");
    get_key(map, "dog");
    get_key(map, "mouse");

    hash_table_destructor(map);

    printf("//----------------- END TESTING HASH TABLE -----------\n");
}

int main() {
    test_hash_table();
    /*test_hash_node_list();*/
    return 0;
}
