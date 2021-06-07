#include <stdio.h>
#include "unix.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 2 (public02.c)
 *
 * Tests using touch() and mkdir() to attempt to create files and
 * directories with the same names in the same directory, which should both
 * have no effect.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  mkfs(&filesystem);

  mkdir(&filesystem, "wombat");
  mkdir(&filesystem, "koala");
  touch(&filesystem, "chipmunk");
  touch(&filesystem, "quokka");
  ls(&filesystem, "");

  touch(&filesystem, "koala");
  mkdir(&filesystem, "koala");
  touch(&filesystem, "chipmunk");
  mkdir(&filesystem, "chipmunk");
  ls(&filesystem, "");

  return 0;
}
