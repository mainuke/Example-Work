#include <stdio.h>
#include "unix.h"
#include "driver.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 9 (public09.c)
 *
 * Tests calling rm() on components of a larger filesystem, including
 * removing a nonempty directory.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;

  /* note the first command in the input is mkfs */
  mkfs(&filesystem);
  driver(&filesystem);
/*
  mkdir(&filesystem, "chipmunk");
  touch(&filesystem, "pear");
  mkdir(&filesystem, "platypus");
  touch(&filesystem, "papaya");
  touch(&filesystem, "orange");

  cd(&filesystem, "chipmunk");

  touch(&filesystem, "kiwi");
  mkdir(&filesystem, "papaya");
  mkdir(&filesystem, "pear");
  touch(&filesystem, "orange");

  cd(&filesystem, "..");

  cd(&filesystem, "platypus");
  touch(&filesystem, "apple");
  mkdir(&filesystem, "grape");
  mkdir(&filesystem, "banana");
  touch(&filesystem, "cherry");

  cd(&filesystem, "grape");
  mkdir(&filesystem, "blue");
  touch(&filesystem, "green");
  mkdir(&filesystem, "purple");
  touch(&filesystem, "yellow");
  touch(&filesystem, "white");
  mkdir(&filesystem, "red");

  rm(&filesystem, "red");

  cd(&filesystem, "..");
  rm(&filesystem, "grape");

  cd(&filesystem, "..");
  rm(&filesystem, "chipmunk");

  ls(&filesystem, "");
  printf("\n");
  ls(&filesystem, "platypus");
  printf("\n");
  cd(&filesystem, "platypus");
  ls(&filesystem, "banana");
  printf("\n");
  */
  /* now trash the whole thing */
  rmfs(&filesystem);

  return 0;
}
