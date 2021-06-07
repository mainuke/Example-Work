#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 7 (secret7.c)
 *
 * Tests calling is_valid_instruction() with an immediate in an li
 * instruction that is not divisible by 4 (memory addresses have to be
 * divisible by 4, but not immediates).
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  assert(is_valid_instruction(0xe0000340) == 1);

  assert(!is_valid_instruction(0xb0000028));  /* this one is invalid */

  printf("The assertions were successful!\n");

  return 0;
}
