#include <stdio.h>
#include <assert.h>
#include "list.h"

/* CMSC 216, Fall 2019, Project #7
 * Public test 1 (public01.c)
 *
 * Tests calling init() and checking that the list's size is zero
 * afterwards.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  List list;

  init(&list);

  assert(size(&list) == 0);

  printf("All assertions experienced a favorable outcome!\n");

  return 0;
}
