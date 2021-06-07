#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 15 (secret15.c)
 *
 * Tests calling relocate() with a value of offset that would cause an
 * instruction to have an invalid memory address when relocated.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define INST_SIZE 2
#define DATA_SIZE 1
#define PROGRAM_SIZE (INST_SIZE + DATA_SIZE)

int main() {
  Word program[PROGRAM_SIZE]= {0x10000052, 0xc01000c0, 0xe0000092};
  Word new_program[PROGRAM_SIZE] = {0};
  unsigned short result= 0;

  assert(relocate(program, INST_SIZE, DATA_SIZE, -10000000, new_program,
                  &result) == 0);
  assert(result == 0);

  assert(relocate(program, INST_SIZE, DATA_SIZE, 10000000, new_program,
                  &result) == 0);
  assert(result == 0);

  printf("The assertions were all successful!\n");

  return 0;
}
