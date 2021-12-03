#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "test.txt"
#define MAX_LINE_LENGTH 5
#define MAX_LINES 12

char** readFile(char fileName[])
{
  int i, j, lines, lineLength;
  FILE *fp; // declare file pointer
  fp = fopen(fileName, "r"); // open file
  lines = MAX_LINES + 1;
  lineLength = MAX_LINE_LENGTH + 2;

  /* Create array and allocate memory */
  char ** file = malloc(lines * sizeof(char*));
  for (i = 0; i < lines; i++)
    file[i] = malloc (lineLength * sizeof(char));

  char line[lineLength];

  /* Prefill with empty characters */
  for (i = 0; i < lines; i++)
  for (j = 0; j < lineLength; j++)
    file[i][j] = '\0';

  for (i = 0; i < lineLength; i++)
    line[i] = '\0';

  /* check for empty file */
  if (fp != NULL)
  {
    i = 0;
    while (fgets(line, sizeof line, fp) != NULL)
    {
      /* read line and check for increases */
      strcpy(file[i], line);
      // printf("Line %d: %s", i, line);
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

void matchEntries(char** file, char** list, int bitCriteria, int index, int arrLength)
{
  int i, j;
  j = 0;
  for (i = 0; i < arrLength; i++)
    if ((file[i][index] - '0') == bitCriteria)
      list[j++] = file[i];
}

int calcOxygenGenRating(char** file, int index, int arrLength)
{
  int i, bit, bitCriteria, length;
  bit = bitCriteria = 0;

  /* Determine bit criteria */
  // printf("[index: %d]\n", index);
  for (i = 0; i < arrLength; i++)
    bit += file[i][index] - '0';
  bitCriteria = bit >= (double)arrLength / 2;

  printf("bit: %d, ", bit);
  printf("bit criteria: %d, ", bitCriteria);

  /* select entries to keep */
  if (bitCriteria)
    length = bit;
  else
    length = arrLength - bit;

  printf("length: %d\n", length);
  
  char *keep[bit];
  matchEntries(file, keep, bitCriteria, index, arrLength);

  /* return if only one entry left */
  if (bit == 1)
    return strtol(keep[0], NULL, 2);
  else if (index + 1 > MAX_LINES)
    return 0;
  else
    return calcOxygenGenRating(keep, ++index, bit);
}

int calcCo2ScrubRating(char** file, int index, int arrLength)
{
  int i, bit, bitCriteria, length;
  bit = bitCriteria = 0;

  /* Determine bit criteria */
  for (i = 0; i < arrLength; i++) {
    // printf("file[i]: %s\n", file[i]);
    bit += file[i][index] - '0';
  }
  bitCriteria = bit < (double)arrLength / 2;

  printf("bit: %d, ", bit);
  printf("bit criteria: %d, ", bitCriteria);

  /* select entries to keep */
  if (bitCriteria)
    length = bit;
  else
    length = arrLength - bit;

  printf("length: %d\n", length);

  char *keep[length];
  matchEntries(file, keep, bitCriteria, index, arrLength);

  /* return if only one entry left */
  if (length == 1)
    return strtol(keep[0], NULL, 2);
  else if (index + 1 > MAX_LINES)
    return 0;
  else
    return calcCo2ScrubRating(keep, ++index, length);
}

int main(void)
{
  char** file = readFile((char *)FILENAME);

  int oxygenGenRating = calcOxygenGenRating(file, 0, MAX_LINES);
  printf("Oxygen generator rating: %d\n", oxygenGenRating);

  int co2ScrubRating = calcCo2ScrubRating(file, 0, MAX_LINES);
  printf("CO2 scrubber rating: %d\n", co2ScrubRating);

  // printf("Final result: %d\n", oxygenGenRating * co2ScrubRating);

  free(file);
  return 1;
}