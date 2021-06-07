#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 6 (public06.c)
 *
 * Tests calling rm() to remove some files.
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
  touch(&filesystem, "quokka");
  touch(&filesystem, "koala");

  ls(&filesystem, ".");
  printf("\n");

  rm(&filesystem, "koala");
  rm(&filesystem, "numbat");

  ls(&filesystem, ".");

  return 0;
}
