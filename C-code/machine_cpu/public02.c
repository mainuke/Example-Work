#include <stdio.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 2 (public02.c)
 *
 * Tests calling print_instruction() with instructions that use memory
 * addresses.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  print_instruction(0x80080080);
  printf("\n");

  print_instruction(0xc01000c0);
  printf("\n");

  print_instruction(0xd0200100);
  printf("\n");

  print_instruction(0xe05e8940);
  printf("\n");

  return 0;
}
