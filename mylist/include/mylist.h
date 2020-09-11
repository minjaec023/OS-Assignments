#ifndef MYLIST_H_
#define MYLIST_H_

struct mylist_node {
  // TODO: Fill it
  struct mylist_node *next;
  int data;
};

struct mylist {
  // TODO: Fill it
  struct mylist_node *head;
  struct mylist_node *tail;
  struct mylist_node *crt;
  struct mylist_node *next;
  int data;
};

void mylist_init(struct mylist* l);
void mylist_destroy(struct mylist* l);

void mylist_insert(
    struct mylist* l,
    struct mylist_node* before, int data);

void mylist_remove(
    struct mylist* l,
    struct mylist_node* target);

struct mylist_node* mylist_find(struct mylist* l, int target);

struct mylist_node* mylist_get_head(struct mylist* l);

void mylist_print(const struct mylist* l);

#endif // MYLIST_H_
