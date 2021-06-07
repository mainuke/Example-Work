#include <stdio.h>
#include "unix.h"
#include "driver.h"
#include "memory-checking.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 5 (public05.c)
 *
 * Tests calling rmfs() on a larger filesystem with various files and
 * directories, ensuring that memory is released and the heap is valid.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;
/*
  mkfs(&filesystem);

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

  cd(&filesystem, "red");
  pwd(&filesystem);
  printf("\n");
  cd(&filesystem, "..");
  pwd(&filesystem);
  printf("\n");

  ls(&filesystem, "");
  printf("\n");

  cd(&filesystem, "..");
  pwd(&filesystem);
  printf("\n");

  ls(&filesystem, "");
*/
  /*rm(&filesystem, "grape");*/
/*

  cd(&filesystem, "..");
  pwd(&filesystem);
  printf("\n");

  ls(&filesystem, "");
  printf("\n");
  ls(&filesystem, "chipmunk");
*/
/*  rm(&filesystem, "platypus");
  rm(&filesystem, "chipmunk");
  rm(&filesystem, "pear");
  rm(&filesystem, "papaya");
  rm(&filesystem, "orange");
*/

  #if !defined(ENABLE_VALGRIND)
    setup_memory_checking();
  #endif

driver(&filesystem);
  /* note the first command in the

  input is mkfs */

  /* now trash the whole thing */
  rmfs(&filesystem);

  #if !defined(ENABLE_VALGRIND)
    check_heap();
  #endif

  /* if this is the only thing printed the heap must be valid, and there
   * must not have been any memory leaks
   */
  printf("\n\nEverything in the heap looks valid!\n");

  return 0;
}
