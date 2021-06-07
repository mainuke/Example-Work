#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 7 (public07.c)
 *
 * Tests using rm() to remove some directories.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  mkdir(&filesystem, "chipmunk");
  mkdir(&filesystem, "platypus");
  mkdir(&filesystem, "numbat");
  mkdir(&filesystem, "quokka");
  mkdir(&filesystem, "koala");

  ls(&filesystem, ".");
  printf("\n");

  rm(&filesystem, "koala");
  rm(&filesystem, "numbat");

  ls(&filesystem, ".");

  return 0;
}
