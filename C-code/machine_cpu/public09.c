#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 9 (public09.c)
 *
 * Tests calling valid_instruction() with some valid instructions, and
 * with one that has another error.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  assert(is_valid_instruction(0x00000124));
  assert(is_valid_instruction(0x10000124));
  assert(is_valid_instruction(0x30000124));
  assert(is_valid_instruction(0x40000124));
  assert(is_valid_instruction(0x60000124));

  assert(!is_valid_instruction(0xc0029a8));

  printf("The assertions were all successful!\n");

  return 0;
}
