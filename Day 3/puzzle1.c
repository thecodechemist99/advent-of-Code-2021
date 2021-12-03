#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "test.txt"
#define MAX_LINE_LENGTH 14 // up to 12 characters plus \n and \0
#define MAX_LINES 12 // up to 1000

char** readFile(char fileName[])
{
  int i, j;
  FILE *fp; // declare file pointer
  fp = fopen(fileName, "r"); // open file

  /* Create array and allocate memory */
  char ** file = malloc(MAX_LINES * sizeof(char*));
  for (i = 0; i < MAX_LINES; i++)
    file[i] = malloc (MAX_LINE_LENGTH * sizeof(char));

  char line[MAX_LINE_LENGTH];

  /* Prefill with empty characters */
  for (i = 0; i < MAX_LINES; i++)
  for (j = 0; j < MAX_LINE_LENGTH; j++)
    file[i][j] = '\0';

  for (i = 0; i < MAX_LINE_LENGTH; i++)
    line[i] = '\0';

  /* check for empty file */
  if (fp != NULL)
  {
    i = 0;
    while (fgets(line, sizeof line, fp) != NULL)
    {
      /* read line and check for increases */
      strcpy(file[i], line);
      printf("Line %d: %s", i, line);
      i++;
    }
    fclose(fp);
  }
  else
  {
    /* Error handling */
    return 0;
  }

  return file;
}

int main (void)
{
  char** file = readFile((char *)FILENAME);
  free(file);
  if (file)
  {
    for (int i = 0; i < MAX_LINES; i++)
      printf("Line %d: %s", i, file[i]);
  }
  else
  {
    /* Error handling */
    return 0;
  }
  return 1;
}