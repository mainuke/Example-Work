#include <stdio.h>
#include <assert.h>
#include "list.h"

/* CMSC 216, Fall 2019, Project #7
 * Public test 4 (public04.c)
 *
 * Tests appending a few elements to a list and printing it.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  List list;

  init(&list);

  append(&list, 2);
  append(&list, 1);
  append(&list, 6);

  print(&list);

  return 0;
}
