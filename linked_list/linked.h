#include <stdio.h>
#include <stdbool.h>

typedef struct node node;
struct node{
  int data;
  node* next;
};

typedef struct linked_list linked_list;
struct linked_list{
  node* head;
  node* tail;
  size_t size;
};

linked_list* linked_list_create(void);
node* node_create(int data, node* n);
void linked_list_addfront(linked_list* list, int data);
void linked_list_addfront_node(linked_list* list, node* n);

void linked_list_addback(linked_list* list, int data);
void linked_list_addback_node(linked_list* list, node* n);

int linked_list_front(linked_list* list);
int linked_list_back(linked_list* list);

void linked_list_popfront(linked_list* list);
void linked_list_popback(linked_list* list);

bool linked_list_isempty(linked_list* list);
size_t linked_list_size(linked_list* list);
void linked_list_clear(linked_list* list);

void linked_list_print(linked_list* list);
