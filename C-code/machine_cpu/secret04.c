#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 4 (secret04.c)
 *
 * Tests trying to call disassemble() with the value of instr_num and
 * data_num both being less than the number of memory words, but their sum
 * is larger than the number of memory words, which is invalid.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define PROGRAM_SIZE 8
#define DATA_SIZE (PROGRAM_SIZE + 4)

int main() {
  Word program[DATA_SIZE]= {0x10000052, 0x20000125, 0x40000092, 0x6000009c,
                            0x700000d0, 0xd0200100, 0x90000080, 0xb0000128,
                            0x0000aced, 0x0000bead, 0x0000face, 0x0000beef};
  assert(!disassemble(program, NUM_WORDS - 4, 8));
  assert(!disassemble(program, 8, NUM_WORDS - 4));

  printf("The assertions were successful!\n");

  return 0;
}
