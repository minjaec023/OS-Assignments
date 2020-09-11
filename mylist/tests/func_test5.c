#include <stdio.h>
#include <mylist.h>

int main()
{
  struct mylist l;

  mylist_init(&l);

  for (int i = 0; i < 10; ++i) {
    mylist_insert(&l, NULL, i);
  }

  struct mylist_node* target = mylist_find(&l, 8);

  if (target != NULL) {
    mylist_insert(&l, target, 90);
  }

  mylist_print(&l);

  mylist_destroy(&l);

  return 0;
}
