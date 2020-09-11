#include <stdio.h>
#include <mylist.h>

int main()
{
  struct mylist l;

  mylist_init(&l);

  for (int i = 0; i < 10; ++i) {
    struct mylist_node* head = mylist_get_head(&l);
    mylist_insert(&l, head, i);
  }

  mylist_print(&l);

  mylist_destroy(&l);

  return 0;
}
