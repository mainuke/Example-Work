#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 10 (secret10.c)
 *
 * Tests calling valid_instruction() with incorrect values in fields that
 * are not used by instructions.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  assert(is_valid_instruction(0x0ff00140) == 1);
  assert(is_valid_instruction(0x70000147) == 1);
  assert(is_valid_instruction(0x9f000080) == 1);
  assert(is_valid_instruction(0xc01000cf) == 1);

  assert(!is_valid_instruction(0xb0000028));  /* this one is invalid */

  printf("The assertions were successful!\n");

  return 0;
}
