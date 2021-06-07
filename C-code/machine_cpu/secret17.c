#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 17 (secret17.c)
 *
 * Tests calling relocate() with instr_num and data_num both being not
 * divisible by 4.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define INST_SIZE 2
#define DATA_SIZE 1
#define PROGRAM_SIZE (INST_SIZE + DATA_SIZE)

int main() {
  Word program[PROGRAM_SIZE]= {0x10000052, 0xc01000c0, 0xe0000092};
  Word new_program[PROGRAM_SIZE];
  Word expected_new_program[PROGRAM_SIZE]= {0x10000052, 0xc01028c0,
                                            0xe0000092};
  unsigned short result= 0;
  int i;

  assert(relocate(program, INST_SIZE, DATA_SIZE, 20, new_program,
                  &result) == 1);
  for (i= 0; i < PROGRAM_SIZE; i++)
    assert(new_program[i] == expected_new_program[i]);

  assert(result == 1);

  printf("The assertions were all successful!\n");

  return 0;
}
