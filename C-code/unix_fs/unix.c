/*Manuel Iribarren 114751782 CMSC216 0204 Project #9 Thurs, Nov. 7th, 2019

This program simulates a UNIX-like file system, that shares many similarities
with standard UNIX except for the way the commands are called, and other minor
differences. The program simulates the shell commands able to manipulate the
UNIX-like filesystem via the implemented functions: available "commands" include
mkfs, touch, mkdir, cd, ls, pwd, rm, rmfs. The filesystem data structure and all
command executions are stored and accessed via dynamically allocated memory.

This version contains memory freeing capabilities, so if the caller wants to
exit the program with 0 memory leakage they can do so using rm to remove
specific subdirectories and files and rmfs to delete the entire filesystem */
#include "unix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Helper method prototype for pwd function*/
void pwd_help(Unix *filesystem, Unix *last);

/*Acronym for 'make file system', this function creates the underlying file
-system, consisting only of the root / directory.
NOTE: since this is an INITIALIZER function, mkfs MUST be called FIRST
before calling any of the other functions on a Unix filesystem structure*/
void mkfs(Unix *filesystem) {

  filesystem->name= malloc(sizeof(char) * 2);
  if (filesystem->name == NULL)
    return;

  strcpy(filesystem->name, "/");

  filesystem->content= malloc(sizeof(Contents));
  if (filesystem->content == NULL)
    return;

  /*Initializes empty DYNAMICALLY ALLOCATED Contents struct*/
  filesystem->content->files= 0;
  filesystem->content->subdirs= 0;
  filesystem->parent= 0;
}

/*This function creates a file with the argument name if no other file/directory
of the same name exists within the current directory. If there does exist a file
OR directory with the same name as the parameter, the function does nothing.*/
int touch(Unix *filesystem, const char arg[]) {
  Subdirs *dirs;
  Files *file, *new_file, *prev= 0, *next= 0;

  /*Checks arg for error cases*/
  if (!filesystem || !arg || arg == '\0' || !strlen(arg) ||
      (strstr(arg, "/") != NULL && strlen(arg) > 1))
    return 0;

/*Base case: if the arg name isn't one of these, the file can potentially
be created*/
  if (!strcmp(arg, ".") || !strcmp(arg, "..") || !strcmp(arg, "/"))
    return 1;

  file= filesystem->content->files;
  dirs= filesystem->content->subdirs;

  /*Will loop thru existing subdirectories IF THEY EXIST*/
  if (dirs) {
    /*Loops through existing subdirectories to see if any match arg*/
    while (dirs && dirs->curr->name  && strcmp(dirs->curr->name, arg)) {
      dirs= dirs->next;
    }

    /*If there IS an EXISTING subdirectory with the same name as arg*/
    if (dirs) {
      return 1;
    }/*Else there is no existing subdirectory with the matching arg name,
    file creation may proceed*/
  }

  /*Will loop thru existing files IF THEY EXIST*/
  if (file) {
    /*Base case: if arg must REPLACE the head file because it ends up being
    SMALLER than the existing head*/
    if (strcmp(file->name, arg) > 0) {
      next= file;
    } else if(strcmp(file->name, arg) < 0 && !file->next) {
        /*new file must be placed after the sole file in the list */
        prev= file;
      }
      else { /*Otherwise, list of files must be iterated thru to check for
      duplicates and the appropriate insertion point*/

      while (file->next && strcmp(file->name, arg)) {

      /*If arg is to be inserted in between the current file and the next one*/
        if (strcmp(file->name, arg) < 0 && strcmp(file->next->name, arg) > 0) {
          prev= file;
          next= file->next;
          break;
        } else {
          file= file->next;
          prev= file;
        }
      }

      /*If the iteration has not reached the end of the list, then there has
      to be an existing file that already has the same name as arg, no effect*/
        if (!strcmp(file->name, arg))
          return 1;
    }
  }

    /*Allocates memory for the structure that is to point to the file*/
      new_file= malloc(sizeof(Files));
      if (!new_file) /*Checks if memory allocation succeeds*/
        return 0;

    /*Allocates memory for the STRING name of the new file*/
      new_file->name= malloc(sizeof(char) * (strlen(arg) + 1));
      if (!new_file->name) /*Checks if memory allocation succeeds*/
        return 0;

    /*Creates the file*/
      strcpy(new_file->name, arg);

    /*File is then inserted into the appropriate order in the sorted file list*/
      new_file->next= next;

      if (prev)
        prev->next= new_file;
      else /*A new head file is being applied, so the filesystem needs to
            be updated directly*/
        filesystem->content->files= new_file;

  return 1;
}

/*Acronym for 'make directory', this function CREATES a subdirectory of the
argument name WITHIN the current working directory, assuming that the parameter
is not the name of an already existing file or subdirectory AND assuming that
the parameter arg is not '.', '..', '/' or an empty string "\0"*/
int mkdir(Unix *filesystem, const char arg[]) {
  Files *files= 0;
  Subdirs *dirs= 0, *next= 0, *prev= 0, *new_dir= 0, *parent= 0;
  /*Checks parameters for error cases*/
  if (!filesystem || !arg || arg == '\0' || !strlen(arg) ||
      (strstr(arg, "/") && strlen(arg) > 1))
    return 0;

/*Base case: file cannot be created if the argument is one of these*/
  if (!strcmp(arg, ".") || !strcmp(arg, "..") || !strcmp(arg, "/"))
    return 0;

  files= filesystem->content->files;

  dirs= filesystem->content->subdirs;

  if (files) {

    /*Loops thru existing files to see if any match arg*/
    while (files->next && strcmp(files->name, arg))
        files= files->next;

    /*If the iteration has not reached the end of the list, then there has
    to be an existing file that already has the same name as arg, no effect*/
    if (files->next)
      return 1;
  }

  /*Will locate the appropriate position in the subdirs linked list to insert
  the new directory IN INCREASING SORTED ORDER -- IF MATCHING NAME IS FOUND,
  NOTHING IS CHANGED */
  if (dirs && dirs->curr->name) {

    /*If directory to be inserted is LESS than the head directory, the new
    directory must then become the new head*/
    if (strcmp(arg, dirs->curr->name) < 0) {
      prev= 0;
      next= dirs;
    } else {
    /*Loops through existing subdirectories to see if any match arg, Otherwise
    it will mark the appropriate position in the INCREASINGLY sorted list
    of directories where the new directory will point to*/
      while (dirs && dirs->curr->name && strcmp(arg, dirs->curr->name)) {

        /*Will mark insertion point as between two directories that come greater
        and the other before the name of the new directory, otherwise the
        new insertion will take place at the tail*/
        if (strcmp(arg, dirs->curr->name) > 0 && dirs->next &&
            dirs->next->curr->name && strcmp(arg, dirs->next->curr->name) < 0) {
          prev= dirs;
          next= dirs->next;
          break;
        }
        prev= dirs;
        dirs= dirs->next;
      }

      /*If there IS an EXISTING subdirectory with the same name as arg*/
      if (dirs && dirs->curr->name && !strcmp(arg, dirs->curr->name))
        return 1;
    }
  }
/*Creation and insertion of new directory will now commence*/

/*Allocates storage for the specific subdirectory to be created*/
  new_dir= malloc(sizeof(Subdirs));
  if (!new_dir) /*checks if memory allocation succeeds*/
    return 0;

  /*Allocates memory for the actual Unix directory to be created*/
  new_dir->curr= malloc(sizeof(Unix));
  if (!new_dir->curr)
    return 0;

  new_dir->next= 0;

  /*Allocates memory for the name of the new subdirectory*/
  new_dir->curr->name= malloc(sizeof(char) * (strlen(arg) + 1));
  if (!new_dir->curr->name) /*checks if memory allocation succeeds*/
    return 0;

  /*Creates new subdirectory*/
  strcpy(new_dir->curr->name, arg);

  new_dir->curr->content= malloc(sizeof(Contents));
  if (!new_dir->curr->content)/*checks if memory allocation succeeded*/
    return 0;

/*Newly created directory will have its content set to 0 by default*/
  new_dir->curr->content->files= 0;
  new_dir->curr->content->subdirs= 0;

/*Finds DIRECT pointer to the current directory for the new directory to
point to for its parent (ASSUMING THE CURRENT DIRECTORY ISN'T ALREADY ROOT). If
it were to point to filesystem directly, the stack pointer address will be
returned, and its better to refer to the dynamically allocated memory space it
currently occupies (the current directory)*/
  if (filesystem->parent) {
      parent= filesystem->parent->content->subdirs;

      while (parent->curr && strcmp(parent->curr->name, filesystem->name))
        parent= parent->next;

    new_dir->curr->parent= parent->curr;
  } else {

    if (filesystem->content->subdirs
       && filesystem->content->subdirs->curr->parent ) {

      new_dir->curr->parent= filesystem->content->subdirs->curr->parent;
    } else {
      /*If we are currently in the root directory and no other subdirectories
      have been created*/
      new_dir->curr->parent= filesystem;
    }
  }

  /*Inserts new directory in the sorted list*/
  if (prev && prev->curr->name) {
    if (!dirs || !next) { /*new_dir is to be inserted as the new tail*/
      new_dir->next= 0;
    } else
      new_dir->next= next;

    prev->next= new_dir;

  } else {/*New directory is the NEW HEAD so the parent must now point to that*/
    if (filesystem->content->subdirs)
      new_dir->next= filesystem->content->subdirs;
     else
      new_dir->next= 0;

    filesystem->content->subdirs= new_dir;
  }

  return 1;
}

/*Acronym for 'current directory', this function CHANGES the current directory
to that of the arg parameter. If arg is '.', function does nothing because '.'
refers to the current working directory, if arg is '..', the current directory
changes to the parent directory, and if arg is '/', the working directory goes
to the ROOT  directory, regardless of what the current parent directory may be*/

int cd(Unix *filesystem, const char arg[]) {
  Unix *curr,*parent, *new_cd, *new_parent;
  Subdirs *dirs;

  /*Checks parameters for error cases*/
  if (!filesystem || !arg || !strlen(arg)
      || (strstr(arg, "/") && strlen(arg) > 1))
    return 0;

  curr= filesystem;
  parent= curr->parent;
  dirs= filesystem->content->subdirs;

  /*Checks if arg is . (current directory) or .. (parent directory)*/
  if (!strcmp(arg, ".") || !strcmp(arg, "..")) {

    /*Change current directory to parent directory*/
    if (!strcmp(arg, "..") && parent) {

      filesystem->parent= parent->parent;
      filesystem->content= parent->content;
      filesystem->name= parent->name;
    }
  /*Otherwise, nothing happens*/
    return 1;
  }

  /*Checks if the arg is the root '/' directory*/
  if (!strcmp(arg, "/")) {

    while(filesystem->parent && strcmp(filesystem->name, "/"))
      cd(filesystem, "..");
    return 1;
 } else { /*Only other valid case is if arg is a SUBDIRECTORY*/

   /*iterates thru list of SUBdirectories to see if arg matches one*/
   while (dirs && dirs->curr->name && strcmp(dirs->curr->name, arg))
     dirs= dirs->next;


   if (!dirs) {/*No matching subdirectory was found*/
     return 0;

   } else { /*Changes current directory to the subdirectory argument*/
     new_cd= dirs->curr;
     /*Only occurs if this is the first time the program is cding into a subroot
     directory, for which there is no initial dynamic memory allocation*/
     if (!filesystem->parent && filesystem->content->subdirs->curr->parent ==
        filesystem) {

       new_parent= malloc(sizeof(Unix));
       *new_parent= *filesystem;
       new_parent->parent= 0;
       /*Loops thru existing subdirectories to UPDATE their parent pointers
       from the stack pointer to the dynamically allocated root directory*/
       dirs= filesystem->content->subdirs;
       while (dirs) {
         dirs->curr->parent= new_parent;
         dirs= dirs->next;
       }
     } else { /*If there is an already dynamically allocated root node*/
       new_parent= dirs->curr->parent;
    }
     new_cd->parent= new_parent;
     *filesystem= *new_cd;
  }
 }
 return 1;
}

/*Standing for 'list directory contents', this function lists the files and
subdirectories of the current working directory.
The list of files and subdirectories is printed in INCREASING sorted order,
with directory names printed with a proceeding '/' with each entry separated by
a new line. If arg is '..', the function lists the contents of the PARENT
directory, if the arg is '/', the contents of the ROOT directory are listed, and
if the arg is '.' OR AN EMPTY STRING, then the function lists the contents of
the CURRENT directory If the arg is the name of a file existing in the current
directory, the file's name appears on a line by itself. If the arg is the name
of a subdirectory existing in the current directory, then the contents of the
SUBDIRECTORY are printed.*/

int ls(Unix *filesystem, const char arg[]) {
  Unix *curr  ;
  Subdirs *dirs;
  Files *files;

  /*Checks parameters for error cases*/
  if (filesystem == NULL || arg == NULL)
    return 0;

  files= filesystem->content->files;
  dirs= filesystem->content->subdirs;
  curr= filesystem;
/*Root Case: prints contents of the root directory*/
  if (!strcmp(arg, "/")) {

    /*Iterates to the starting root directory*/
    while (curr->parent != 0) {
      curr= curr->parent;
    }

      ls(curr, "");
      return 1;
  }

  /*Parent case: prints contents parent directory*/
  if (!strcmp(arg, "..") && filesystem->parent) {

    ls(filesystem->parent, "");

    return 1;
  }

/*BASE case: list contents of current directory*/
  if ((strlen(arg) == 1 && !strcmp(arg, "."))  || !strlen(arg)) {

    /*Loops thru files and subdirectories and prints them in an increasing
      sorted order*/
    while ((files && files->name)|| (dirs && dirs->curr->name)) {
      /*Compares current file and subdirectory and the pointers increment
      based on whether they are printed*/

      if (files && dirs && dirs->curr->name) {

        /*Current file comes before the current directory*/
        if (strcmp(files->name, dirs->curr->name) < 1) {
          printf("%s\n", files->name);
          files= files->next;
        } else {
          printf("%s/\n", dirs->curr->name);
          dirs= dirs->next;
        }

      } else {
      /*if there are no subdirectories, just files are printed, and vice versa*/
      if (files && !dirs ) {
        printf("%s\n", files->name);
        files= files->next;

      } else if (!files && dirs) {
        printf("%s/\n", dirs->curr->name);
        dirs= dirs->next;
      }
    }

  }
  return 1;

  } else {
/*ONLY OTHER valid case is if arg is the name of an EXISTING file or directory*/

      while ((files && strcmp(files->name, arg)) ||
              (dirs && strcmp(dirs->curr->name, arg))) {

    /*If arg is the name of an existing SUBDIRECTORY, print the contents*/
        if (dirs && dirs->curr->name && !strcmp(dirs->curr->name, arg)) {
          /*Recursively calls ls() to print the contents of the subdirectory*/
          ls(dirs->curr, "");
          return 1;
        }

        /*If arg is the name of an existing FILE, only its name is printed*/
        if (files && !strcmp(files->name, arg)) {
          printf("%s\n", files->name);
          return 1;
        }
        files= (files ? files->next : files);
        dirs= (dirs ? dirs->next: dirs);
    }
  /*Didn't match any existing file or subdirectory*/
  if (!files && !dirs)
    return 0;

  return 1;
  }
}
/*Acronym for 'print working directory', this function prints the current
directory followed by a new line. This function prints the full path*/
void pwd(Unix *filesystem) {
  if (!strcmp(filesystem->name, "/")) {
    printf("/\n");
    return;
  }
  pwd_help(filesystem, filesystem);
}

void pwd_help(Unix *filesystem, Unix *last) {
  Unix *curr= last;

  if (!filesystem)
    return;
  /*If we have reached the root directory, end the recursive calls
  and print the rest of the directories*/
  if (!strcmp(filesystem->name, "/") ) {
    return;
  } else { /*We have not yet reached the root*/
    pwd_help(filesystem->parent, curr);
    if (!strcmp(filesystem->parent->name, "/"))
      printf("/");

    if (!strcmp(filesystem->name, last->name))
      printf("%s\n", filesystem->name);
    else
      printf("%s/", filesystem->name);
  }
}
/*Acronym for "remove filesystem", thos function deallocates ALL dynamically
allocated memory*/
void rmfs(Unix *filesystem) {
  Unix *curr= 0, *parent= 0;
  Contents *content= 0;
  Files *files= 0;
  Subdirs *subdirs= 0;

  if (!filesystem)
    return;

  /*if filesystem has content, then filesystem sanitization will commence*/
  if (filesystem->content) {

    content= filesystem->content;
    files= content->files;
    subdirs= content->subdirs;
    curr= (subdirs ? subdirs->curr->parent : filesystem);
    parent= filesystem->parent;

  /*If there are files in this current file system, they will be deleted first*/
    if (files) {

      while (files && files->name) {
        rm(filesystem, files->name);
        files= NULL;
        files= content->files;
      }
      content->files= NULL;
      files= NULL;
    }
/*If there are subdirectories in the current directory then they and their
contents will also be deleted*/
    if (subdirs) {

      while (subdirs && subdirs->curr->name) {

        rm(curr, subdirs->curr->name);
        subdirs->curr= NULL;
        subdirs= NULL;
        subdirs= content->subdirs;
      }
      free(content->subdirs);
      content->subdirs= NULL;
      subdirs= NULL;
    }

    free(filesystem->content);
    filesystem->content= NULL;
    curr->content= NULL;
    content= NULL;
  }

  /*If current directory has a parent, then the parent's subdir pointer list
  needs to reflect the deletion of the current directory*/
  if (parent) {

    rm(parent, filesystem->name);
    filesystem->name= NULL;
    rmfs(filesystem->parent);
    return;
  }
  /*if current directory is already root, all that is left to do is delete it*/
  if (!parent && curr) {
    if (filesystem->content)
      free(filesystem->content);
      filesystem->content= NULL;

    free(filesystem->name);
    filesystem->name = NULL;
    if (curr != filesystem)
      free(curr);
  }
  curr= NULL;
  filesystem= NULL;

  return;
}
/*This function's effect is to remove a file or directory (denoted by arg)
from the given filesystem by freeing its allocated memory. If the element to be
removed is an immediate SUBDIRECTORY of the filesystem, ALL contents of said
subdirectory will be freed*/
int rm(Unix *filesystem, const char arg[]) {
  Files *files= 0, *prev_f= 0, *next_f= 0;
  Subdirs *dirs= 0, *next_dir= 0, *prev_dir= 0, *delete= 0;

  /*Error cases*/
  if (!filesystem || (filesystem && !filesystem->content) || !strcmp(arg, ".")
      || !strcmp(arg, "..") || strchr(arg, '/') != NULL || strlen(arg) == 0)
    return 0;

  files= filesystem->content->files;
  dirs= filesystem->content->subdirs;

  if (files) {

    /*If what is to be deleted is the HEAD file, then the next file in the list
    must become the new head*/
    if (!strcmp(files->name, arg)) {
      next_f= files->next;
      free(filesystem->content->files->name);
      filesystem->content->files->name= NULL;

      free(filesystem->content->files);
      filesystem->content->files= NULL;
      files= NULL;
      filesystem->content->files= next_f;
      return 1;

    } else {
      /*Loops thru files to see if any correspond with arg*/
      while (files && strcmp(files->name, arg)) {

        if (files->next && !strcmp(files->next->name, arg)) {
          prev_f= files;
          next_f= files->next->next;
        }

        files= files->next;
      }
    }

/*If files isnt 0 by this point, then it must be = to the corresponding file
  to arg marked for deletion*/
    if (files) {

      free(files->name);
      files->name= NULL;
      arg= NULL;
      files->next= NULL;
      free(files);
      files= NULL;

      if (prev_f) {
      /*If prev_f is not 0, then the deleted file was not the head*/
        prev_f->next= NULL;
        prev_f->next= next_f;
      }
      return 1;
    }
  }


  /*Loops through available subdirectories to see if arg refers to any of them*/
  if (dirs) {

    /*If the subdirectory to be deleted is the HEAD directory in the list, the
    next one in the list becomes the new head*/
    if (!strcmp(dirs->curr->name, arg)) {
      delete= dirs;
      next_dir= dirs->next;
    } else {
      /*loops thru the existing subdirs to see if any match arg*/
      while (dirs && strcmp(dirs->curr->name, arg)) {

      /*If the directory marked for deletion in between two nodes in the subdir
        list order*/
        if (dirs->next && !strcmp(dirs->next->curr->name, arg)) {
          prev_dir= dirs;
          next_dir= dirs->next->next;
        }
        dirs= dirs->next;
      }

      if (!delete && dirs) /*If dirs is not 0 and delete is still 0, then the
      subdirectory to be removed is the tail one*/
        delete= dirs;
    }
  }

  if (delete) {
    /*If the directory marked for deletion has OTHER subdirectories/files
    within it, then those must be deleted as well*/
    if (delete->curr->content) {

      /*If there are files to be deleted (IN THE SUBDIRECTORY TO BE DELETED),
      then they must be looped thru and deleted one by one*/
      if (delete->curr->content->files) {

        files= delete->curr->content->files;
        while (files && files->name) {
          rm(delete->curr, files->name);
          files->next= NULL;
          files= NULL;
          files= delete->curr->content->files;
        }
        if (delete->curr->content && delete->curr->content->files){

          delete->curr->content->files->next= NULL;
          delete->curr->content->files= NULL;
        }
        files= NULL;
      }

      delete->curr->content->files= 0;

      if (delete->curr->content->subdirs) {

        /*If there are subdirectories WITHIN THE SUBDIRECTORY
        to be deleted, then they must be looped thru and deleted one by one*/
        dirs= delete->curr->content->subdirs;
        while (dirs && delete->curr && dirs->curr->name) {
          rm(delete->curr, dirs->curr->name);
          dirs->curr= NULL;
          dirs->next= NULL;
          dirs= NULL;
          dirs= delete->curr->content->subdirs;
        }
        dirs= NULL;
      }

      if (delete->curr->content) {
        free(delete->curr->content);
        delete->curr->content= NULL;
      }
    }
/*Finishes freeing the rest of the subdirectory marked for deletion*/
    delete->curr->parent= NULL;
    free(delete->curr->name);
    delete->curr->name= NULL;
    free(delete->curr);
    delete->curr= NULL;
    arg= NULL;

    if (delete) {
      delete->next= NULL;
      free(delete);
      delete= NULL;
    }

    /*Updates the filesystem pointers to reconnect over the freed memory*/
    if (prev_dir) {
      if (prev_dir->next)
        prev_dir->next= NULL;

      prev_dir->next= next_dir;
    } else { /*We must replace the head if prev_dir is 0*/
      filesystem->content->subdirs= next_dir;
    }
    return 1;
  }
  /*If no code is triggered, arg does NOT correspond with ANY existing files OR
  subdirectories in the current directory*/
  return 0;
}
