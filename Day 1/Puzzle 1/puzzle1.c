#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 5
#define MAX_LINES 2000

char *parseFile (const char fileName[])
{
  FILE *fp; // declare file pointer
  fp = fopen(fileName, "r"); // open file

  char (*file)[MAX_LINES] = malloc(sizeof(char[MAX_LINE_LENGTH][MAX_LINES]));
  char line[MAX_LINE_LENGTH];

  /* allocate file array */

  int i, j;
  /* Prefill with empty characters */
  for (i = 0; i < MAX_LINES; i++)
  {
    for (j = 0; j < MAX_LINE_LENGTH; j++)
    {
      file[i][j] = '\0';
    }
  }

  for (i = 0; i < MAX_LINE_LENGTH; i++)
  {
    line[i] = '\0';
  }

  /* check for empty file */
  if (fp != NULL)
  {
    i = 0;
    while (fgets(line, sizeof line, fp) != NULL)
    {
      /* read line */
      strcpy(*file, line);
      printf("Line %d: %s\n", i, line);
      i++;
    }
    fclose(fp);
  }
  else
  {
    /* Error handling */
    return NULL;
  }

  return *file;
}

int main (void)
{
  const char *file = parseFile("input.txt");

  if (file != NULL)
  {
    int i, lastValue, increased;
    increased = 0;

    /* check for increases */
    for (i = 0; i < MAX_LINES; i++)
    {
      if (!i)
        lastValue = atoi(&file[i]);
      else
      {
        if (atoi(&file[i]) > lastValue)
          increased++;
        lastValue = atoi(&file[i]);
      }
    }

    printf("The number of increases is %d.", increased);
  }
  else
  {
    /* Error Handling */
  }

  // free(&file);
}