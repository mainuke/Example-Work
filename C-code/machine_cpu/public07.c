#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 7 (public07.c)
 *
 * Tests calling disassemble() with a zero-sized code segment, which is
 * invalid.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(disassemble(NULL, 1, 2) == 0);

  printf("The assertion was successful!\n");

  return 0;
}
