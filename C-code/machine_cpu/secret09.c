#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 9 (secret09.c)
 *
 * Tests calling valid_instruction() with an immediate in an li instruction
 * that is larger than the largest possible memory address.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  assert(is_valid_instruction(0xeffff340) == 1);

  assert(!is_valid_instruction(0xb0000028));  /* this one is invalid */

  printf("The assertion was successful!\n");

  return 0;
}
