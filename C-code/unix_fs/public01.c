#include <stdio.h>
#include "unix.h"
#include "driver.h"

/* CMSC 216, Fall 2019, Project #9
 * Public test 1 (public01.c)
 *
 * Tests that the revised form of the \texttt{pwd()} function prints the
 * full pathname of the current directory.  Note that this test uses the
 * driver.
 *
 * (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

int main() {
  Unix filesystem;
/*
  mkfs(&filesystem);
  mkdir(&filesystem, "kangaroo");
  touch(&filesystem, "pear");

  touch(&filesystem, "papaya");
  mkdir(&filesystem, "platypus");
  touch(&filesystem, "orange");
  ls(&filesystem, "");

  cd(&filesystem, "kangaroo");
  pwd(&filesystem);

  touch(&filesystem, "kiwi");
  mkdir(&filesystem, "papaya");
  mkdir(&filesystem, "pear");
  touch(&filesystem, "orange");
  ls(&filesystem, "");

  cd(&filesystem, "pear");
  pwd(&filesystem);

  cd(&filesystem, "..");
  pwd(&filesystem);
  ls(&filesystem, "");

  cd(&filesystem, "..");
  pwd(&filesystem);
  ls(&filesystem, "");


  cd(&filesystem, "platypus");
  pwd(&filesystem);

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
  cd(&filesystem, "..");
  pwd(&filesystem);
  cd(&filesystem, "..");



  /-*/
  driver(&filesystem);


  return 0;
}
