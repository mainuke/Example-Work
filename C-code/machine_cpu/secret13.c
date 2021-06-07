#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 13 (secret13.c)
 *
 * Tests passing NULL into relocate()'s num_changed_instr parameter.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define INST_SIZE 3
#define DATA_SIZE 0
#define PROGRAM_SIZE (INST_SIZE + DATA_SIZE)

int main() {
  /* 0xe0000092 is an li instruction*/
  Word program[PROGRAM_SIZE]= {0x10000052, 0xc01000c0, 0xe0000092};
  Word new_program[PROGRAM_SIZE]= {0, 0, 0};
  Word expected_new_program[PROGRAM_SIZE]= {0, 0, 0};
  int i;

  assert(relocate(program, INST_SIZE, DATA_SIZE, 20, new_program, NULL) == 0);
  for (i= 0; i < PROGRAM_SIZE; i++)
    assert(new_program[i] == expected_new_program[i]);

  printf("The assertions were all successful!\n");

  return 0;
}
