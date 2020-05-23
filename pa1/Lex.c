#include <stdbool.h> // might not need this
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#define MAX_LEN 160

int main(int argc, char * argv[])
{
    int n;
    int count = 0;

    FILE* in;
    FILE* out;

    char line[MAX_LEN];
    //char tokenlist[MAX_LEN];
    //char* token;


    if(argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   // basic null checks
   if(in == NULL)
    {
      printf("Can't open file %s for reading\n", argv[1]);
      exit(1);
    }

   // basic null checks
   if(out == NULL)
    {
      printf("Can't open file %s for writing\n", argv[2]);
      exit(1);
    }

   //counts number of lines in the input file
   while(fgets(line, MAX_LEN, in) !=NULL)
    {
      count++;
    }

   //holds all of the lines of file
   char Word[count - 1][MAX_LEN];
   n = -1;

   //back to top of file
   rewind(in);


   //copies inputs of file into Word array
   while(fgets(line, MAX_LEN, in) != NULL)
    {
      strcpy(Word[++n], line);
    }

   //fclose(in);

   List L = newList();
   append(L, 0);

    for(int j = 1; j < count; j++)
    {
        char* temp = Word[j];
        int i = j - 1;
        moveBack(L);

       while(i >= 0 && strcmp(temp, Word[get(L)]) <= 0)
       {
           i--;
           movePrev(L);
           //char *temp = Word[i];
       }
           if(index(L) >= 0)
           {
               insertAfter(L, j);
           }

           else
           {
               prepend(L, j);
           }
       }

    moveFront(L);

    while(index(L) >= 0)
    {
        fprintf(out, "%s\n", Word[get(L)]);

        moveNext(L);
    }

    freeList(&L);
    fclose(in);
    fclose(out);

    return(0);


//    while(fgets(line, MAX_LEN, in) != NULL)
//    {
//        count++;
//        n = 0;
//        token = strtok(line, " \n");
//        tokenlist[0] = '\0';
//
//        while(token != NULL)
//        {
//            strcat(tokenlist, "   ");
//            strcat(tokenlist, token);
//            strcat(tokenlist, "\n");
//            n++;
//            token = strtok(NULL, " \n");
//        }
//
//        fprintf(out, "line %d contain %d token%s: \n", count, n, n==1?"":"s");
//        fprintf(out, "%s\n", tokenlist);
//    }
//
//    fclose(in);
//    fclose(out);
//
//    return (0);

}

