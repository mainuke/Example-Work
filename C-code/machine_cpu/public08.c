#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 8 (public08.c)
 *
 * Tests calling valid_instruction() with some valid instructions, and
 * with some that have some invalid operands.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(is_valid_instruction(0x00000053));
  assert(is_valid_instruction(0x5000016d));
  assert(is_valid_instruction(0xd0200100));
  assert(is_valid_instruction(0xa00000c0));
  assert(is_valid_instruction(0xb0000128));

  assert(!is_valid_instruction(0xb0000028));
  assert(!is_valid_instruction(0xf0000052));

  printf("The assertions were all successful!\n");

  return 0;
}
