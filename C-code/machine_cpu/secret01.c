#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 1 (secret01.c)
 *
 * Tests trying to call disassemble() with a zero-sized code segment, which
 * is invalid.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define PROGRAM_SIZE 0
#define DATA_SIZE (PROGRAM_SIZE + 4)

int main() {
  Word program[DATA_SIZE]= {0x0000aced, 0x0000bead, 0x0000face, 0x0000beef};

  assert(!disassemble(program, PROGRAM_SIZE, DATA_SIZE));

  printf("The assertion was successful!\n");

  return 0;
}
