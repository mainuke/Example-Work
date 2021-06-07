#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Secret test 14 (secret14.c)
 *
 * Tests that relocate() does not change the value of the variable that
 * num_changed_instr points to if its parameters are invalid.
 *
 * (c) Yiling Qiao and Larry Herman, 2019.  You are allowed to
 * use this code yourself, but not to provide it to anyone else.
 */

#define INI_RESULT 79
#define INST_SIZE 3
#define DATA_SIZE 0
#define PROGRAM_SIZE (INST_SIZE + DATA_SIZE)

int main() {
  /* 0xe0000092 is an li instruction */
  Word program[PROGRAM_SIZE]= {0x10000052, 0xc01000c0, 0xe0000092};
  Word new_program[PROGRAM_SIZE];
  unsigned short result = INI_RESULT;

  /* NULL program */
  assert(relocate(NULL, INST_SIZE, DATA_SIZE, 20, new_program,
                  &result) == 0);
  assert(INI_RESULT == result);

  /* invalid INST_SIZE */
  assert(relocate(program, 99999999, DATA_SIZE, 20, new_program,
                  &result) == 0);
  assert(INI_RESULT == result);

  printf("The assertions were all successful!\n");

  return 0;
}
