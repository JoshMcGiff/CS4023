#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int main(int argc, char* argv[])
{
  int flipping = (strcmp(argv[1], "-f") == 0);
  char c;
  FILE *from;
  FILE *to;

  from = fopen(argv[2], "r");
  if (from == NULL)
  {
    perror("Error with first arg");
    exit(1);
  }
   to = fopen(argv[3], "w");
  if (to == NULL)
  {
    perror("Error with second arg");
    exit(1);
  }

  /* file exists, so start reading */
  while ((c = getc(from)) != EOF)
        if (flipping) // same as: if (flipping == 1)
            putc(flipChar(c), to);
        else
            putc(c, to);


  fclose(from);
  fclose(to);

  exit(0);
}
