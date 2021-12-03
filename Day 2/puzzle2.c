#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"
#define MAX_LINE_LENGTH 11 // up to 9 characters plus \n and \0
#define MAX_LINES 1000 // up to 1000

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
    int xPos, depth, aim;
    i = xPos = depth = aim = 0;
    while (fgets(line, sizeof line, fp) != NULL)
    {
      /* read line and check for increases */
      printf("Line %d: %s", i, line);
      if (strstr(line, "forward"))
      {
        xPos += atoi(&line[8]);
        depth += aim * atoi(&line[8]);
      }
      else if (strstr(line, "up"))
        aim -= atoi(&line[3]);
      else if (strstr(line, "down"))
        aim += atoi(&line[5]);
      i++;
    }
    fclose(fp);
    printf("\nThe final position is %d (%d * %d).", xPos * depth, xPos, depth);
  }
  else
  {
    /* Error handling */
    return -1;
  }

  return 1;
}