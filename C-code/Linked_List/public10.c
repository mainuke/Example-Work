#include <stdio.h>
#include <assert.h>
#include "list.h"

/* CMSC 216, Fall 2019, Project #7
 * Public test 10 (public10.c)
 *
 * Tests passing NULL into append(), which should just have no effect.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  List list;

  init(&list);

  append(&list, 216);
  append(&list, 132);
  append(&list, 250);
  append(&list, 131);
  append(NULL, 123456789);
  append(&list, 141);
  append(&list, 330);
  append(&list, 350);
  append(&list, 412);
  append(&list, 351);

  assert(size(&list) == 9);

  print(&list);

  printf("\nAll assertions experienced a favorable outcome!\n");

  return 0;
}
