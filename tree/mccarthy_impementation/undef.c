//
//  hashtable.c
//  hashtable
//
//  Created by William McCarthy on 154//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/file_struct.h"

#define NUMBER_OF_STRINGS 100
#define MAX_STRING_SIZE 200
#define HASHSIZE 101
#define IN true
#define OUT false

//-----------------------------------------------------------
typedef struct hash_node {
    struct hash_node* next;
    const char* name;
    char* defn;
} hash_node;

static hash_node* hashtab[HASHSIZE];

//-----------------------------------------------------------
unsigned hash(const char* s) {
    unsigned hashval = 0;

    for (hashval = 0; *s != '\0'; ++s) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

//-----------------------------------------------------------
hash_node* hash_lookup(const char* s) {
    hash_node* np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }

    return NULL;
}

//-----------------------------------------------------------
hash_node* hash_install(const char* name, const char* defn) {
    if (name == NULL) {
        return NULL;
    }

    hash_node* np;
    unsigned hash_idx;

    if ((np = hash_lookup(name)) == NULL) { /* name not found, need new node */
        np = (hash_node*)malloc(sizeof(hash_node));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hash_idx = hash(name);
        np->next = hashtab[hash_idx];
        hashtab[hash_idx] = np;
    } else {
        free((void*)np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }

    return np;
}

void hash_deletenode(hash_node* p) {
    if (p == NULL) {
        return;
    }
    free((void*)p->name);
    free(p->defn);
    free(p);
}

void hash_clear() {
    printf("\nclearing hash table...   ");
    for (int i = 0; i < HASHSIZE; ++i) {
        hash_node* p = hashtab[i];
        if (i == 72) {
            printf("72\n");
        }
        while (p != NULL) {
            hash_node* q = p;
            p = p->next;
            hash_deletenode(q);
        }
        hashtab[i] = NULL;
    }
    printf("cleared\n");
}

void hash_undef(const char* name) {
    if (name == NULL) {
        return;
    }

    hash_node* np;
    unsigned hash_idx;
    if ((np = hash_lookup(name)) == NULL) {
        return;
    }

    hash_idx = hash(name);
    hash_node* p = np;
    hash_node* prev = np;
    while (p != np) {
        prev = p;
        p = p->next;
    }
    prev->next = p->next;
    hash_deletenode(p);
    if (hashtab[hash_idx]->next == NULL) {
        hashtab[hash_idx] = NULL;
    }
}

const char* yesorno(bool cond) { return cond ? "YES" : "no"; }

void print_defn(const char* s) {
    hash_node* p = hash_lookup(s);
    printf("'%s': ", s);
    printf("%s ", p ? p->defn : "not found");
    printf(" ---> %p\n", p ? p->next : NULL);
}

void hash_print(void) {
    for (int i = 0; i < HASHSIZE; ++i) {
        printf("%3d...\n", i);
        hash_node* np = hashtab[i];
        while (np != NULL) {
            printf("\t");
            print_defn(np->name);
            np = np->next;
        }
    }
}

void test_hash_table() {
    printf(
        "%s\n",
        "// ---------------------- TESTING HASH_TABLE ---------------------");
    hash_install("cat", "animal that likes fish");
    hash_install("dog", "animal that hates cats");
    hash_install("mouse", "animal eaten by cats");
    hash_install("virus", "pain in the neck");

    print_defn("cat");
    print_defn("pig");
    print_defn("dog");
    print_defn("pig");
    print_defn("mouse");
    print_defn("bacteria");
    print_defn("amoeba");
    print_defn("paramecium");
    print_defn("virus");

    hash_print();

    printf("\nredefining cat...\n");
    printf("redefining virus...\n");

    hash_install("cat", "animal that likes fish and mice and birds");
    hash_install("virus", "VERY EXPENSIVE pain in the neck");

    print_defn("cat");
    print_defn("virus");
    hash_print();

    printf("undefining virus...\n");
    hash_undef("virus");
    print_defn("virus");
    hash_print();

    hash_clear();
    hash_print();
    printf(
        "\n%s\n",
        "// ----------------END OF TESTING HASH_TABLE ---------------------");
}

void add_word_defn(const char* name, const char* defn, int* size) {
    if (hash_install(name, defn) != NULL) {
        //    printf("adding %s\n", name);
        ++*size;
    }
}

void hash_test(int argc, const char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./hash filename\n");
        exit(1);
    }

    FILE* fin;
    const char* filename = argv[1];
    if ((fin = fopen(filename, "r")) < 0) {
        fprintf(stderr, "Could not open file: '%s'\n", filename);
        exit(1);
    }

    char buf[BUFSIZ];
    char delims[] = " \n";
    int size = 0;
    memset(buf, 0, sizeof(buf));

    while (fgets(buf, BUFSIZ, fin)) {
        char* p = strtok(buf, delims);
        add_word_defn(p, "some defn", &size);

        while ((p = strtok(NULL, delims)) != NULL) {
            add_word_defn(p, "some defn", &size);
        }
    }
    printf("%d words added...\n", size);
    hash_print();

    hash_clear();
    hash_print();

    fclose(fin);
}

char* strip(char* string) {
    if (string == NULL) {
        return string;
    }
    while (*string != '\0' && isspace(*string) && !isalpha(*string)) {
        *string++;
    }
    return string;
}

char** split(char* string, const char* pattern) {
    // at this rate I need to write my own string processing header because I
    // keep resuing these
    char** split_string;
    split_string = malloc(NUMBER_OF_STRINGS * sizeof(char*));

    char* mutate = strdup(string);
    char* token = strtok(mutate, pattern);
    int i = 0;
    while (token != NULL) {
        split_string[i] = malloc((MAX_STRING_SIZE + 1) * sizeof(char));
        strcat(split_string[i++], strip(token));
        token = strtok(NULL, pattern);
    }
    return split_string;
}

void reading_from_file(const char* path) {
    struct file_* f_a = file_constructor(path, false);
    char *word, *definition;
    for (int i = 0; i < f_a->length; ++i) {
        char** split_string = split(f_a->contents[i], ":");
        word = split_string[0];
        definition = split_string[1];
        /*printf("adding the word: %s\n", word);*/
        hash_install(word, definition);
        print_defn(word);
        /*printf("removing definition: %s\n", definition);*/
        hash_undef(word);
        /*print_defn(word);*/
        printf("==================================\n");
    }
    file_destructor(f_a);
}
//-----------------------------------------------------------
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", *argv);
        return -1;
    }
    *argv++;
    reading_from_file(*argv);
    return 0;
}
