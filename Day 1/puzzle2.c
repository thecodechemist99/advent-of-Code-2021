#include <stdio.h>
#include <stdlib.h>

#define FILENAME "input.txt"
#define MAX_LINE_LENGTH 6 // up to 4 characters plus \n and \0
#define MAX_LINES 2000 // up to 2000

int sumOfArray (int array[]) {
  int sum;
  sum = 0;
  for (int i = 0; i <= (int)(sizeof &array / sizeof array[0]); i++) {
    sum += array[i];
  }

  return sum;
}

int main (void)
{
  FILE *fp; // declare file pointer
  fp = fopen(FILENAME, "r"); // open file

  int data[MAX_LINES];
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
    /* read lines */
    i = 0;
    while (fgets(line, sizeof line, fp) != NULL)
    {
      data[i] = atoi(line);
      i++;
    }
    fclose(fp);
    
    /* check for increases in sliding windows */
    int lastValue, increased;
    increased = 0;
    for (i = 0; i < MAX_LINES - 2; i++)
    {
      int chunk[] = { data[i], data[i + 1], data[i + 2] };
      if (!i)
      {
        lastValue = sumOfArray(chunk);
      }
      else
      {
        if (sumOfArray(chunk) > lastValue)
          increased++;
        lastValue = sumOfArray(chunk);
      }
      printf("Sum of chunk: %d\n", lastValue);
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