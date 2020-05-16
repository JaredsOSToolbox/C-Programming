//
//  tree.h
//  tree
//
//  Created by William McCarthy on 134//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//
#include <stdbool.h>
#include "file_struct.h"
#include "dlist.h"
#ifndef tree_h
#define tree_h

//-------------------------------------------------
typedef struct tnode tnode;
struct tnode {
  const char* word;
  bool read;
  int count;
  dlist* bucket;
  tnode* left;
  tnode* right;
};


typedef struct tree tree;
struct tree {
  tnode* root;
  size_t size;
};


//-------------------------------------------------
tnode* tnode_create(const char* word);
tree* tree_create(void);

void tree_delete(tree* t);
void tree_clear(tree* t);

bool tree_empty(tree* t);
size_t tree_size(tree* t);

tnode* tree_add(tree* t, const char* word, size_t size, int ln);

void tree_print(tree* t);    // INORDER-printing
void tree_print_inorder(tree*);
bool is_valid(char*);

void tree_print_preorder(tree* t);
void tree_print_postorder(tree* t);

void tree_test(struct file_*, size_t);

#endif /* tree_h */
