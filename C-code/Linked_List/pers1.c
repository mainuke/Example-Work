#include <stdio.h>
#include <assert.h>
#include "list.h"

/*CMSC216 Project #7 PERSONALLY WRITTEN TESTS
 */

int main(void) {
  List list;
  int i=0;
  init(&list);

  append(&list, 216);
  append(&list, 132);
  append(&list, 250);
  append(&list, 131);
  append(&list, 351);
  delete(&list, 4); /*tests deletion of tail node*/
  assert(size(&list) == 4);
  assert(find(&list, 351) == -1);
  append(&list, 141);
  append(&list, 330);
  append(&list, 350);
  append(&list, 412);
  prepend(&list, 351);
  delete(&list, 0); /*Tests deletion of head node*/
  assert(size(&list) == 8 );
  assert(find(&list, 351) == -1);
  print(&list);

  for (i = 0; i < 9; i++) {
    delete(&list, 8-i);
    print(&list);
  }
  print(&list);
  printf("\nAll assertions experienced a favorable outcome!\n");

  return 0;
}
