#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 8 (secret08.c)
 *
 * Tests calling is_valid_instruction() with instructions that try to modify
 * R0 and R6, and some data in the data segment of the array.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  /* modify R6 */
  assert(is_valid_instruction(0x00000180) == 0);
  assert(is_valid_instruction(0x10000180) == 0);
  assert(is_valid_instruction(0x20000180) == 0);
  assert(is_valid_instruction(0x30000180) == 0);
  assert(is_valid_instruction(0x40000180) == 0);
  assert(is_valid_instruction(0x50000180) == 0);
  assert(is_valid_instruction(0x60000180) == 0);
  assert(is_valid_instruction(0x70000180) == 0);
  assert(is_valid_instruction(0xb0000180) == 0);
  assert(is_valid_instruction(0xc0100180) == 0);
  assert(is_valid_instruction(0xe0000180) == 0);

  /* modify R0 */
  assert(is_valid_instruction(0x00000000) == 0);
  assert(is_valid_instruction(0x10000000) == 0);
  assert(is_valid_instruction(0x20000000) == 0);
  assert(is_valid_instruction(0x30000000) == 0);
  assert(is_valid_instruction(0x40000000) == 0);
  assert(is_valid_instruction(0x50000000) == 0);
  assert(is_valid_instruction(0x60000000) == 0);
  assert(is_valid_instruction(0x70000000) == 0);
  assert(is_valid_instruction(0xb0000000) == 0);
  assert(is_valid_instruction(0xc0100000) == 0);
  assert(is_valid_instruction(0xe0000000) == 0);

  /* modify R2 */
  assert(is_valid_instruction(0x00000080) == 1);
  assert(is_valid_instruction(0x10000080) == 1);
  assert(is_valid_instruction(0x20000080) == 1);
  assert(is_valid_instruction(0x30000080) == 1);
  assert(is_valid_instruction(0x40000080) == 1);
  assert(is_valid_instruction(0x50000080) == 1);
  assert(is_valid_instruction(0x60000080) == 1);
  assert(is_valid_instruction(0x70000080) == 1);
  assert(is_valid_instruction(0xb0000080) == 1);
  assert(is_valid_instruction(0xc0100080) == 1);
  assert(is_valid_instruction(0xe0000080) == 1);

  printf("The assertions were successful!\n");

  return 0;
}
