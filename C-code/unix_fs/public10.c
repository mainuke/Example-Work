#include <stdio.h>
#include "unix.h"
#include "driver.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 10 (public10.c)
 *
 * Tests calling rm() to remove everything in a filesystem.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  /* note the first command in the input is mkfs */
  driver(&filesystem);

  /* now trash the whole thing */
  rmfs(&filesystem);

  return 0;
}
