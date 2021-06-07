#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 5 (secret05.c)
 *
 * Tests calling disassemble() with a program containing some valid
 * instructions prior to an invalid one.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define PROGRAM_SIZE 8
#define DATA_SIZE (PROGRAM_SIZE + 4)

int main() {
  /* 0xb0000028 is invalid, which is a case in public08.c */
  Word program[DATA_SIZE]= {0x10000052, 0x20000125, 0x40000092, 0xb0000028,
                            0x700000d0, 0xd0200100, 0x90000080, 0xb0000128,
                            0x0000aced, 0x0000bead, 0x0000face, 0x0000beef};

  assert(disassemble(program, PROGRAM_SIZE, 4) == 0);

  printf("The assertion was successful!\n");

  return 0;
}
