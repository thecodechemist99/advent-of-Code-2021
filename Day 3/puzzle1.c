#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "test.txt"
#define MAX_LINE_LENGTH 7 // up to 12 characters plus \n and \0
#define MAX_LINES 13 // up to 1000 + 1

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
    char gammaRate[MAX_LINE_LENGTH - 1], epsilonRate[MAX_LINE_LENGTH - 1];

    /* Determine gamma rate */
    int i, j, bit;
    for (i = 0; i < MAX_LINE_LENGTH - 2; i++) {
      bit = 0;
      for (j = 0; j < MAX_LINES; j++) {
        if (file[j][i] - '0' >= 0)
        bit += file[j][i] - '0';
      }
      gammaRate[i] = round((double)bit / MAX_LINES) + '0';
    }
    printf("Gamma rate: %s", gammaRate);
  }
  else
  {
    /* Error handling */
    return 0;
  }
  return 1;
}