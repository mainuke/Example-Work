#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 11 (secret11.c)
 *
 * Tests the return value of print_instruction().
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  /* valid ones */
  assert(print_instruction(0x00000053) == 1);
  printf("\n");

  assert(print_instruction(0x10000052) == 1);
  printf("\n");

  assert(print_instruction(0x20000125) == 1);
  printf("\n");

  assert(print_instruction(0x300000cb) == 1);
  printf("\n");

  assert(print_instruction(0x40000092) == 1);
  printf("\n");

  assert(print_instruction(0x5000016d) == 1);
  printf("\n");

  assert(print_instruction(0x6000009c) == 1);
  printf("\n");

  assert(print_instruction(0x700000d0) == 1);
  printf("\n");

  assert(print_instruction(0x80080080) == 1);
  printf("\n");

  assert(print_instruction(0xc01000c0) == 1);
  printf("\n");

  assert(print_instruction(0xd0200100) == 1);
  printf("\n");

  assert(print_instruction(0xe05e8940) == 1);
  printf("\n");

  /* invalid ones */
  assert(!print_instruction(0xb0000028));
  assert(!print_instruction(0xf0000052));
  assert(!print_instruction(0xc0029a8));

  printf("The assertions were all successful!\n");

  return 0;
}
