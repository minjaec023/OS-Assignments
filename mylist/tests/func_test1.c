#include <stdio.h>
#include <mylist.h>

int main()
{
  struct mylist l;

  mylist_init(&l);

  for (int i = 0; i < 10; ++i) {
    mylist_insert(&l, NULL, i);
  }

  mylist_print(&l);

  mylist_destroy(&l);

  return 0;
}
