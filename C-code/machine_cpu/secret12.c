#include <stdio.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 12 (secret12.c)
 *
 * Tests that print_instruction() doesn't print leading zeros for immediate
 * values.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

int main() {
  print_instruction(0xe0000040);
  printf("\n");

  print_instruction(0xe00008c0);
  printf("\n");

  return 0;
}
