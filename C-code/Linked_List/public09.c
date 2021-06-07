#include <stdio.h>
#include <assert.h>
#include "list.h"

/* CMSC 216, Fall 2019, Project #7
 * Public test 9 (public09.c)
 *
 * Tests trying to delete an element at a nonexistent list position.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main(void) {
  List list;

  init(&list);

  append(&list, 250);
  append(&list, 132);
  append(&list, 216);
  append(&list, 131);
  append(&list, 141);
  append(&list, 330);
  append(&list, 350);
  append(&list, 412);
  append(&list, 351);

  assert(size(&list) == 9);

  delete(&list, 10);

  assert(size(&list) == 9);

  printf("All assertions experienced a favorable outcome!\n");

  return 0;
}
