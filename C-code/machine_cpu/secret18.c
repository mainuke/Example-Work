#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 18 (secret18.c)
 *
 * Tests that relocate() does not relocate immediates that are operands
 * of li instructions.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define INST_SIZE 3
#define DATA_SIZE 0
#define PROGRAM_SIZE (INST_SIZE + DATA_SIZE)

int main() {
  Word program[PROGRAM_SIZE]= {0x10000052, 0xc01000c0, 0xe0000092};
  Word new_program[PROGRAM_SIZE];
  Word expected_new_program[PROGRAM_SIZE]= {0x10000052, 0xc01028c0,
                                            0xe0000092};
  unsigned short result= 0;
  int i;

  assert(relocate(program, INST_SIZE, DATA_SIZE, 20, new_program, &result));
  for (i= 0; i < PROGRAM_SIZE; i++)
    assert(new_program[i] == expected_new_program[i]);

  printf("The assertions were all successful!\n");

  return 0;
}
