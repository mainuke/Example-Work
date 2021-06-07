#include <stdio.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 3 (public03.c)
 *
 * Tests calling print_instruction() with the remaining instruction types.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  print_instruction(0x90000080);
  printf("\n");

  print_instruction(0xa00000c0);
  printf("\n");

  print_instruction(0xb0000128);
  printf("\n");

  return 0;
}
