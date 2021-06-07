#include <stdio.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 1 (public01.c)
 *
 * Tests calling print_instruction() with arithmetic and logical
 * instructions.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  print_instruction(0x00000053);
  printf("\n");

  print_instruction(0x10000052);
  printf("\n");

  print_instruction(0x20000125);
  printf("\n");

  print_instruction(0x300000cb);
  printf("\n");

  print_instruction(0x40000092);
  printf("\n");

  print_instruction(0x5000016d);
  printf("\n");

  print_instruction(0x6000009c);
  printf("\n");

  print_instruction(0x700000d0);
  printf("\n");

  return 0;
}
