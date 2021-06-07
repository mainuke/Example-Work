#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#define LINE_SZ 256

/*Manuel Iribarren Project #13 CMSC216 Sunday, December 8th, 2019
This program expands upon the invocation of the word count command wc by
implementing multi-threading capabilities. Except for the fact it is using
multi-threaded code, it functions identically to the wc.c program that implments
the wc command standardly
*/
  /**This Data structure holds the relevant file info to this program for
  each file argument**/
 typedef struct {
   char *filename; /*Name of file/filedescriptor*/
   int chars, lines, words; /*Info corresponding to file*/
 }Data;


static void *count(void *filename);

/*Counts the number of characters, lines, and words in a file*/
static void *count(void *filename) {
   char ch, next_ch;
   int lines= 0, chars= 0, words= 0;
   FILE *fp;
   Data *file_info;
   file_info= malloc(sizeof(Data));
   fp= fopen((char*)filename, "r");

   if (fp != NULL){
     file_info->filename= (char*)filename;
     /* read each file one character at a time, until EOF */
     ch= fgetc(fp);
     while (!feof(fp)) {
       next_ch= fgetc(fp);  /* look ahead and get the next character */
       ungetc(next_ch, fp);  /* unread the next character */

       /* update the counts as needed every time a character is read */

       /* a newline means the line count increases */
       if (ch == '\n')
         lines++;

       /* if the current character is not whitespace but the next character
          is, or if the current character is not whitespace and it is the
          last character in the input, the word count increases */
       if (!isspace(ch) && (isspace(next_ch) || feof(fp)))
         words++;

       /* increase character count*/
       chars++;

       ch= fgetc(fp);
     }

     fclose(fp);
   }
   /*Stores file totals in the structure to be returned to the caller*/
   file_info->chars= chars;
   file_info->lines= lines;
   file_info->words= words;
   return file_info;
}
 /* Counts the number of words, lines, and characters in the files whose
  * names are given as command-line arguments.  If there are no command-line
  * arguments then the line, word, and character counts will just be 0.
  * Mimics the effects of the UNIX "wc" utility, although does not have
  * exactly the same behavior in all cases.
  */

 int main(int argc, char *argv[]) {
   int i, total_lines= 0, total_words= 0, total_chars= 0;
   pthread_t tids[LINE_SZ];
   void *filename, **file_info;


   if (argc > 1) {
     /*Allocates sufficient memory in struct to store file info for each
     file argument*/
     file_info= calloc(argc - 1, sizeof(Data*));

     for (i= 0; i < argc-1; i++) {

         /*copies filename*/
         filename= malloc((strlen(argv[i + 1]) + 1) * sizeof(char));
         strcpy((char*)filename, argv[i + 1]);

         /*creates one thread for each file name to be opened*/
         if (pthread_create(&tids[i], NULL, count, filename) != 0)
           fprintf(stderr, "error: Cannot create thread # %d\n", i);

        /*Updates corresponding array entry with current file information*/
        pthread_join(tids[i], &(file_info[i]));

        /* add the totals for the current file into the accumulating totals
        for all files */
        total_lines += ((Data*)file_info[i])->lines;
        total_words += ((Data*)file_info[i])->words;
        total_chars += ((Data*)file_info[i])->chars;

      /*Frees dynamically allocated memory*/
        free(filename);
        free(file_info[i]);

       }

       free(file_info);
     }
    printf("%4d %4d %4d\n", total_lines, total_words, total_chars);
   return 0;
 }
