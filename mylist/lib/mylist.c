#include <stdlib.h>

#include "mylist.h"

void mylist_init(struct mylist* l)
{
  // TODO: Fill it

 l -> head = NULL;
}

void mylist_destroy(struct mylist* l)
{
  // TODO: Fill it
  while(l->head)
    mylist_remove(l, l->head);
}

void mylist_insert(
    struct mylist* l,
    struct mylist_node* before, int data)
{
  // TODO: Fill it
  struct mylist_node* node;
  node = malloc(sizeof(struct mylist_node));
  node -> data = data;

  if(before == NULL){
    node -> next = l -> head;
    l -> head = node;
  }
  else{
    node -> next = before -> next;
    before -> next = node;
  }
}

void mylist_remove(
    struct mylist* l,
    struct mylist_node* target)
{
  // TODO: Fill it
  struct mylist_node *temp, *prev;
  temp = l -> head;
  if(target == l -> head){
    l -> head = temp -> next;
    free(target);
  }
  else{
    while(temp != target){
      prev = temp;
      temp = temp -> next;
    }
    prev -> next = temp -> next;
    free(temp);
  }
}

struct mylist_node* mylist_find(struct mylist* l, int target)
{
  // TODO: Fill it
  struct mylist_node *temp;
  temp = l ->head;
  while(temp){  
    if(temp -> data == target){
      return temp;
    }
    temp = temp -> next;
  }
  return NULL; // If not found
}

struct mylist_node* mylist_get_head(struct mylist* l)
{
  // TODO: Fill it
  if(l->head) return l->head;
  return NULL;
}

void mylist_print(const struct mylist* l)
{
   // HINT: Define structs referring comments
  struct mylist_node* pointer;
  
  for (pointer = l->head;
      pointer != NULL;
      pointer = pointer->next) {
    printf("%d\n", pointer->data);
  }
}
