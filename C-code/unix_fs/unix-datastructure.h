/*Manuel Iribarren 114751782 CMSC216 0204 Project #9 Thursday, November 7th, 2019

Defines the structure of the dynamically allocated UNIX-like file system to be
simulated. The structure is implemented using a dynamically allocated linked
data structure, with dynamically allocated pointer structures used to store the
contents of the directory*/
#if !defined(UNIXDATASTRUCTURE_H)
#define UNIXDATASTRUCTURE_H
typedef struct unix {
  /*Stores name of the current directory*/
  char *name;
  /*Points to another struct containing the files and subdirectories*/
  struct contents *content;
  /*Pointer to the directory preceding the current one*/
  struct unix *parent;
}Unix;
/**Parent of root directory will always be NULL**/

/*Dynamically allocated recurisive structure that refers to the
contents of the directory*/
typedef struct contents {
/*Pointer to dynamically allocated struct that refers to all the files in
a directory*/
  struct files *files;
  /*Dynamically allocated recursively linked unix struct that stores the
  SUBdirectories*/
  struct subdirs *subdirs;
}Contents;

  /*Dynamically allocated recursively linked data structure that stores the
  files in a directory*/
typedef struct files {
/*Current file in subdirectory*/
  char *name;
/*Pointer to the next file, tail file's next pointer will point to 0*/
  struct files *next;
}Files;

/*Dynamically allocated recursively linked data structure designed to point
to the unix-type subdirectories contained within a directory**/
typedef struct subdirs {
  /*Currently pointed dynamically allocated subdirectory*/
  struct unix *curr;
  /*Pointer to the NEXT subdirectory, in an increasingly sorted order, with
  the tail subdirectory having a next pointer of 0 or NULL */
  struct subdirs *next;
}Subdirs;
#endif
