#include <stdio.h>
#include <assert.h>
#include "list.h"

/* CMSC 216, Fall 2019, Project #7
 * Public test 3 (public03.c)
 *
 * Tests appending a few elements to a list and checking its size.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  List list;

  init(&list);

  prepend(&list, 2);
  prepend(&list, 1);
  prepend(&list, 6);

  assert(size(&list) == 3);

  printf("All assertions experienced a favorable outcome!\n");

  return 0;
}
