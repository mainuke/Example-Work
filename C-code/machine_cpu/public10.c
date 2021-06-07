#include <stdio.h>
#include <assert.h>
#include "machine.h"

/* CMSC 216, Fall 2019, Project #3
 * Public test 10 (public10.c)
 *
 * Tests calling relocate() with a simple program with three instructions,
 * one of which has to be relocated.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

#define PROGRAM_SIZE 3
#define DATA_SIZE 0

int main() {
  Word program[PROGRAM_SIZE]= {0x10000052, 0xc01000c0, 0x40000092};
  Word new_program[PROGRAM_SIZE];
  Word expected_new_program[PROGRAM_SIZE]= {0x10000052, 0xc01028c0,
                                            0x40000092};
  unsigned short result= 0;
  int i;

  /* move the addresses in the program 20 bytes ahead */
  assert(relocate(program, PROGRAM_SIZE, DATA_SIZE, 20, new_program, &result));
  /* check the results against the expected results declared above */
  for (i= 0; i < PROGRAM_SIZE; i++)
    assert(new_program[i] == expected_new_program[i]);

  printf("The assertions were all successful!\n");

  return 0;
}
