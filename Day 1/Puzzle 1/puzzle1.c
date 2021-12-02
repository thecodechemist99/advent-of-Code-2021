#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"
#define MAX_LINE_LENGTH 6 // up to 4 characters plus \n and \0
#define MAX_LINES 2000 // up to 2000

int main (void)
{
  FILE *fp; // declare file pointer
  fp = fopen(FILENAME, "r"); // open file

  char line[MAX_LINE_LENGTH];

  int i;
  /* Prefill with empty characters */
  for (i = 0; i < MAX_LINE_LENGTH; i++)
  {
    line[i] = '\0';
  }

  /* check for empty file */
  if (fp != NULL)
  {
    int lastValue, increased;
    i = increased = 0;
    while (fgets(line, sizeof line, fp) != NULL)
    {
      /* read line and check for increases */
      printf("Line %d: %s", i, line);
      if (!i)
        lastValue = atoi(line);
      else
      {
        if (atoi(line) > lastValue)
          increased++;
        lastValue = atoi(line);
      }
      i++;
    }
    fclose(fp);
    printf("The number of increases is %d.", increased);
  }
  else
  {
    /* Error handling */
    return -1;
  }

  return 1;
}