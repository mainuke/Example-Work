#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "safe-fork.h"
#include "split.h"

int main(int argc, char *argv[]) {
  char *target_prgrm= NULL, temp, input[999], **stdin_args= NULL, /**next= NULL,*/*cmds[]= {"make", "gcc","echo", "ls", "cp", "mv", "rm", "touch", NULL};
  int i= 0, readc= 0, count= 0, i_present= 0, prog_present= 0, status= 0, index= 1; /*1 By default since argv[0] is just going to be arg.x*/
  pid_t child;

  /*while(i < argc) {
    printf("%s\n", argv[i]);
    i++;
  }*/
  /*Checks for - i, to see if program is to be run in standard or line-at-a-time mode. Starting index will be 2 if -i is present bc that will start at the THIRD argument -- the 1st one being xargs.x and the 2nd being -i*/
  if (argc >= 2 && !strcmp(argv[1], "-i")) {
    i_present= 1;
    index = 2;
  }


  /*checks if there is a valid target program*/
  while(cmds[i] && (index < argc) && strcmp(argv[index], cmds[i]))
    i++;
/*IF no appropriate command is found in the argument following -i, and it is NOT
a FLAG, then exit status must be 1*/
  if (cmds[i] != NULL && (index < argc))
    prog_present= 1;
   if (cmds[i] == NULL && argv[index][0] != '-') {
    exit(1);
  }


  /*Checks if there is a target program in the consecutive argument after the -i or the xargs.x invocation. if not, then by default /bin/echo is run -- which just prints its arguments as the target program instead*/

  if (prog_present == 0) {
    target_prgrm= malloc(sizeof(char) * strlen("/bin/echo"));
    strcpy(target_prgrm, "/bin/echo");

  } else { /*then we have found a valid target*/
    target_prgrm= malloc(sizeof(char) *strlen(argv[index]));
    strcpy(target_prgrm, argv[index]);
  }

/*Depending on whether or not program is to be run in standard or line-at-a-time mode, the specified target program will be forked either 1 time or n line # of times*/


/*If running in STANDARD mode, target-program is to be executed once -- with the arguments being the included cmd arguments in the CLI invocation AND ALL OF THE LINES of the stdinput of args.x itself*/


/*If -i is present, then. If so, then there are only arguments and the default /bin/echo is to be run. If there is a target program, then that is run*/
  if (!i_present) {/*Standard mode*/
      i= 0;
      /*reads target program into the input first*/
      while (target_prgrm[i] != '\0') {
        input[i]= target_prgrm[i];
        i++;
      }
      input[i]= ' ';

      i++;
      /*If there are additional flags after the target invocation in argv, those
      also must be added*/
     if (index < argc) {

      while (index < argc && argv[index][0] == '-'  && strlen(argv[index]) <=5) {


          count=0;
          while (count < strlen(argv[index]) && argv[index][count] != '\0') {
            input[i + count]= argv[index][count];
            count++;
          }
          i++;


        index++;
      }
      input[i]= ' ';
      i++;
    }
        input[i]= temp;
        i++;

        while (scanf("%c", &input[i]) && input[i] != EOF) {

          if (input[i] == '\n') {
            input[i]=' ';
          }
          i++;
        }
        input[i]= '\0';


      child= safe_fork();

      if (child) { /*Parent*/
        waitpid(child, &status, 0);
        if (!WIFEXITED(status)) /*nonzero exit status means exit the program*/
          exit(1);
      } else { /*child*/
      stdin_args= split(input);

        if (execvp(target_prgrm, stdin_args)) {
          perror("Compile command execvp error");
          exit(1);
        }
        exit(0);
    }
      /*frees split stdin args*/
      i= 1;
      while (stdin_args && stdin_args[i]) {
        free(stdin_args[i]);
        stdin_args[i]= NULL;
        i++;
      }
      stdin_args= NULL;

  } else {/*Line-at-a-time mode*/
    /*If running in LINE-AT-A-TIME mode, target-program is executed ONCE FOR EACH LINE OF ITS OWN STDINPUT. Each time the target-program is run, the arguments will consist of the CLI arguments AND THE WORDS OF THE x LINE OF THE STDINPUT*/
      i= 0;
        /*Execute target program on each line until EOF*/
    while((readc = read(STDIN_FILENO, &temp, sizeof(char))) > 0) {
      index= (argc >= 2 ? 2 : 1);

      i= 0;
      /*First, current line of input is read into line input buffer*/

      /*reads target program into the input first*/
      while (target_prgrm[i] != '\0') {
        input[i]= target_prgrm[i];
        i++;
      }
      input[i]= ' ';
      i++;
      /*If there are additional flags after the target invocation in argv, those
      also must be added*/
     if (index < argc) {

      while (index < argc && argv[index][0] == '-'  && strlen(argv[index]) <=5) {


          count=0;
          while (count < strlen(argv[index]) && argv[index][count] != '\0') {
            input[i + count]= argv[index][count];
            count++;
          }
          i++;


        index++;
      }
      input[i]= ' ';
      i++;
    }
        input[i]= temp;
        i++;

      /*reads the rest of the line into buffer*/
      while ((readc= read(STDIN_FILENO, &(input[i]), sizeof(char))) > 0 &&
              input[i] != '\n' && input[i] != '\0') {
        i++;
      }

      /*executes line of arguments in child process*/
      child= safe_fork();
      if (child) {
        waitpid(child, &status, 0);
        if (!WIFEXITED(status)) /*nonzero exit status means exit the program*/
          exit(1);
      } else {/*child*/
      stdin_args= split(input);

        /*ERROR CHECKING FOR FORK*/
        if (execvp(target_prgrm, stdin_args)) {
          perror("Compile command execvp error");
          exit(1);
        }
        exit(0);
      }
      /*frees split stdin args*/
      i= 0;
/*
      while (stdin_args && stdin_args[i]) {
        free(stdin_args[i]);
        stdin_args[i]= NULL;
        i++;
      }
      /-*Resets input*/
      i= 0;
      while (input[i] != '\0') {
        input[i]= '\0';
        i++;
      }
      i=0;
      stdin_args= NULL;

    }
  }
  free(target_prgrm);
  target_prgrm= NULL;

  /*First dynamically allocates a 2D string array, with each entry storing a single line in the STDINPUT to be split during EACH instance of the program execution*/

return (status ? 1 : 0);
}
