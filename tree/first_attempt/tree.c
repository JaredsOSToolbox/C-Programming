#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "file_struct.h"

//--- Structures --- //

typedef struct tnode tnode;
struct tnode{
  const char* word;
  int count;
  tnode* left;
  tnode* right;
};

typedef struct tree tree;
struct tree{
  tnode* root;
  size_t size;
};

//--- Function prototypes --- //
int getword(const char*, int);
tnode* tnode_create(const char* word);
tree* tree_create(void);
void tree_print(tree*);
void tree_printnode(tree* t, tnode* p);
tnode* tree_add(tree*, const char*);
tnode* tree_addnode(tree*, tnode*, const char*);
size_t tree_size(tree*);

bool tree_empty(tree*);
size_t tree_size(tree* t);


//-- Function definitions -- //

tnode* tnode_create(const char* word){
  tnode* t = (tnode *)malloc(sizeof(tnode));
  t->word = strdup(word);
  t->count = 1;
  t->left = t->right = NULL;
  return t;
}

tree* tree_create(void){
  tree* t  = (tree *)malloc(sizeof(tree));
  t->root = NULL;
  t->size = 0;
  return t;
}

tnode* tree_addnode(tree* t, tnode* p, const char* w){
  int condition;
  if(p == NULL){ 
    p = tnode_create(w); 
    t->root = p;
  } else if ((condition = strcmp(w, p->word)) == 0){ p->count++; }
  else if(condition < 0){ p->left = tree_addnode(t, p->left, w); }
  else{
    p->right = tree_addnode(t, p->right, w);
  }
  ++t->size;
  return p;
}

tnode* tree_add(tree* t, const char* w){
  return tree_addnode(t, t->root, w);
}

bool tree_empty(tree* t){ return (t->size == 0) ? true: false; }
size_t tree_size(tree* t){ return t->size; }

void tree_printnode(tree* t, tnode* p){
  if(p == NULL){ printf("returning\n"); return; }
  tree_printnode(t, p->left);
  printf("%s -- %d (%p, %p)\n", p->word, p->count, p->left, p->right);
  tree_printnode(t, p->right);
}
void tree_print(tree* t){ tree_printnode(t, t->root); }


void tree_test(){
  printf("//=========== TESTING TREE =====================///\n\n");
  tree* t = tree_create();
  struct file_* f_a = file_constructor("input");
  for(int i = 0; i < f_a->length; ++i){
    char* mutate = strdup(f_a->contents[i]);
    char* token = strtok(mutate, " ");
    while(token != NULL){
      tree_add(t, token);
      token = strtok(NULL, " ");
    }
  }
  printf("Tree size: %zu\n", tree_size(t));
  printf("Tree empty: %s\n", (tree_empty(t)) ? "true" : "false");
  assert(tree_empty(t) == false);
  /*printf("Tree size: %zu\n", tree_size(t));*/
  /*assert(tree_size(t) == 16);*/
  
  tree_print(t);
  if(t->root == NULL){ printf("the root is null"); }
  printf("\nALL ASSERTIONS PASSED!\n");
  free(t);
  file_destructor(f_a);

  printf("//=========== END TESTING TREE =====================///\n");
}


int main(int argc, const char* argv[]){
  tree_test();
  return 0;
}
