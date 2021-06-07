#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 2 (secret02.c)
 *
 * Tests calling disassemble() with instr_num and data_num both being not
 * divisible by 4.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define PROGRAM_SIZE 7
#define DATA_SIZE (PROGRAM_SIZE + 3)

int main() {
  Word program[DATA_SIZE]= {0x10000052, 0x20000125, 0x40000092, 0xb0000128,
                            0x700000d0, 0xd0200100, 0x90000080,
                            0x0000aced, 0x0000bead, 0x0000face};

  assert(disassemble(program, PROGRAM_SIZE, 3) == 1);

  printf("The assertion was successful!\n");

  return 0;
}
