#include <stdio.h>
#include <assert.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 8 (public08.c)
 *
 * Tests calling rm() to try to remove nonexistent files and directories.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  touch(&filesystem, "chipmunk");
  touch(&filesystem, "platypus");
  touch(&filesystem, "numbat");
  mkdir(&filesystem, "quokka");
  mkdir(&filesystem, "koala");

  ls(&filesystem, ".");
  printf("\n");

  assert(rm(&filesystem, "frog") == 0);
  assert(rm(&filesystem, "emu") == 0);

  ls(&filesystem, ".");

  return 0;
}
