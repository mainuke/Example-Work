#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 6 (secret06.c)
 *
 * Tests calling valid_instruction() with instructions that use R0 and R6
 * but do not try to modify them (this is valid).
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  /* R0 */
  assert(is_valid_instruction(0x00000140) == 1);
  assert(is_valid_instruction(0x10000140) == 1);
  assert(is_valid_instruction(0x20000140) == 1);
  assert(is_valid_instruction(0x30000140) == 1);
  assert(is_valid_instruction(0x40000140) == 1);
  assert(is_valid_instruction(0x50000140) == 1);
  assert(is_valid_instruction(0x60000140) == 1);
  assert(is_valid_instruction(0x70000140) == 1);
  assert(is_valid_instruction(0xb0000140) == 1);

  /* R6 */
  assert(is_valid_instruction(0x00000170) == 1);
  assert(is_valid_instruction(0x10000170) == 1);
  assert(is_valid_instruction(0x20000170) == 1);
  assert(is_valid_instruction(0x30000170) == 1);
  assert(is_valid_instruction(0x40000170) == 1);
  assert(is_valid_instruction(0x50000170) == 1);
  assert(is_valid_instruction(0x60000170) == 1);
  assert(is_valid_instruction(0x70000170) == 1);
  assert(is_valid_instruction(0xb0000170) == 1);

  /* this one is invalid */
  assert(!is_valid_instruction(0xb0000028));

  printf("The assertions were successful!\n");

  return 0;
}
