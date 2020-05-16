//
//  tree.c
//  tree
//
//  Created by William McCarthy on 134//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tree.h"
#include "utils.h"
#include "file_struct.h"
#include "dlist.h"

static bool FIRST_N = false;
static int N_CHARS = 6;

//-------------------------------------------------
tnode* tnode_create(const char* word) {
  tnode* p = (tnode*)malloc(sizeof(tnode));
  p->bucket = dlist_create();
  p->word = strdup(word);    // copy of word allocated on heap
  p->count = 1;
  p->left = NULL;
  p->right = NULL;
  p->read = false;
  
  return p;
}

void tnode_delete(tnode* p) {
  free((void*)p->word);
  dlist_clear(p->bucket, false);
  free(p->bucket);
  free(p);
}

tree* tree_create(void) {
  tree* p = (tree*)malloc(sizeof(tree));
  p->root = NULL;
  p->size = 0;
  
  return p;
}

static void tree_deletenodes(tree* t, tnode* p) {
  if (p == NULL) { return; }
  tree_deletenodes(t, p->left);
  tree_deletenodes(t, p->right);
  tnode_delete(p);
  t->size--;
}

void tree_clear(tree* t) {
  tree_delete(t);
  t->root = NULL;
  t->size = 0;
}

void tree_delete(tree* t) { 
  tree_deletenodes(t, t->root); 
}

bool tree_empty(tree* t) { return t->size == 0; }
size_t tree_size(tree* t) { return t->size; }

static tnode* tree_addnode(tree* t, tnode** p, const char* word, size_t size, int ln) {
  int compare;
  
  if (*p == NULL) {
    *p = tnode_create(word);
    dlist_pushback((*p)->bucket, ln);
  } else if ((compare = strncmp(word, (*p)->word, size)) == 0) {
    (*p)->count++;
    dlist_pushback((*p)->bucket, ln);
  } else if (compare < 0) { 
    tree_addnode(t, &(*p)->left, word, size, ln);
  } else {
    tree_addnode(t, &(*p)->right, word, size, ln);
  }
  return *p;
}

tnode* tree_add(tree* t, const char* word, size_t size, int ln) {
  tnode* p = tree_addnode(t, &(t->root), word, size, ln);
  t->size++;

  return p;
}

void tnode_repr(tnode* n){
  printf("word: %s\t", n->word);
  dlist_print(n->bucket, "printing contents");
  printf("count: %d\n", n->count);
}

void tnode_repr_n(tnode* n){
  static char prev[100];
  static bool firsttime = true;
  if(firsttime){
    memset(prev, 0, sizeof(prev));
    strcpy(prev, n->word);
  }
  int compare = strncmp(prev, n->word, N_CHARS);
  if(compare != 0){
    printf("\n");
  }
  strcpy(prev, n->word);
  printf("%s ", n->word);
  firsttime  = false;
}

// ================ PRINT FUNCTIONS ================================= //

static void tree_printme(tree* t, tnode* p) {
  printf("%s", p->word);
  if (p->count > 1) { 
    printf(" -- %d\n", p->count); 
    printf("WORD: %s\n", p->word);
    dlist_print(p->bucket, "");
  }
  printf("\n");
}

void treeprint(struct tnode *p){
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

static void tree_printnodes(tree* t, tnode* p) {
  if (p == NULL) { return; }
  
  tree_printnodes(t, p->left);
  (FIRST_N) ? tnode_repr_n(p) : tnode_repr(p);
  tree_printnodes(t, p->right);
}

static void tree_printnodes_preorder(tree* t, tnode* p) {
  if (p == NULL) { return; }
  
  tree_printme(t, p);
  tree_printnodes(t, p->left);
  tree_printnodes(t, p->right);
}

static void tree_printnodes_postorder(tree* t, tnode* p){
  if (p == NULL) { return; }
  
  tree_printnodes(t, p->left);
  tree_printnodes(t, p->right);
  tree_printme(t, p);
}

void tree_print(tree* t) {    // INORDER-printing
  if(t->root == NULL){ printf("the root is null!\n"); }
  tree_printnodes(t, t->root);
  printf("\n");
}

void tree_print_preorder(tree* t) {
  tree_printnodes_preorder(t, t->root);
}

void tree_print_postorder(tree* t){
  tree_printnodes_postorder(t, t->root);
}

void treefreq_print(tree* tf[], int n){
  for(int i = n; i >= 1; --i){
    tree* t = tf[i];
    if(t != NULL  && t->root != NULL){
      treeprint(t->root);
    }
  }
}

// ============= END PRINT FUNCTIONS ================================ //
//

static tnode* treefreq_addnode(tree* t, tnode** pp, tnode* p){
  int compare;
  if(*pp == NULL){
    *pp = tnode_create(p->word);
    (*pp)->count = p->count;
    (*pp)->bucket = NULL;
    (*pp)->left = NULL;
    (*pp)->right = NULL;
  }
  else if((compare = strcmp(p->word, (*pp)->word)) < 0){
    treefreq_addnode(t, &(*pp)->left, p);
  }
  else if(compare > 0){
    treefreq_addnode(t, &(*pp)->right, p);
  }
  return *pp;
}
void treefreq_node_fromtree(tree*  tf[], tnode* other){
  if(other == NULL){ return; }

  treefreq_node_fromtree(tf, other->left);
  int index = other->count;
  tree** t = &tf[index];
  if(*t == NULL && index != 0){
    *t = tree_create();
  }
  treefreq_addnode(*t, &(*t)->root, other);
  treefreq_node_fromtree(tf, other->right);
}
void treefreq_fromtree(tree* tf[], tree* other){
  treefreq_node_fromtree(tf, other->root);
}

// ================== TESTING FUNCTIONS ========================================= //

void tree_test(struct file_*, size_t);
