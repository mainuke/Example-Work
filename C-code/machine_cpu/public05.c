#include <stdio.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 5 (public05.c)
 *
 * Tests calling disassemble() with some instructions in the code segment
 * and some data in the data segment of the array.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

#define PROGRAM_SIZE 8
#define DATA_SIZE 4

int main() {
  Word program[PROGRAM_SIZE + DATA_SIZE]= {0x10000052, 0x20000125, 0x40000092,
                                           0x6000009c, 0x700000d0, 0xd0200100,
                                           0x90000080, 0xb0000128, 0x0000aced,
                                           0x0000bead, 0x0000face, 0x0000beef};

  disassemble(program, PROGRAM_SIZE, DATA_SIZE);

  return 0;
}
