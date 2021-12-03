#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME "input.txt"
#define MAX_LINE_LENGTH 12
#define MAX_LINES 1000
#define BINARY_REFERENCE 0b111111111111 // as many 1s as MAX_LINE_LENGTH

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

unsigned int calcGamma(char** file)
{
  int i, j, bit;
  char gammaRate[MAX_LINE_LENGTH];
  if (file)
  {
    /* Determine gamma rate */
    for (i = 0; i < MAX_LINE_LENGTH; i++) {
      bit = 0;
      for (j = 0; j < MAX_LINES; j++) {
        if (file[j][i] - '0' >= 0)
        bit += file[j][i] - '0';
      }
      gammaRate[i] = round((double)bit / MAX_LINES) + '0';
    }
    printf("Gamma rate (binary): %s\n", gammaRate);
  }
  else
  {
    /* Error handling */
    return 0;
  }
  return strtol(gammaRate, NULL, 2);
}

char* intToBinary(int integer) {
  // based on answer by @chux at https://codereview.stackexchange.com/questions/255036/represent-integer-as-binary-in-c  
  int i;
  char *binary = malloc(MAX_LINE_LENGTH * sizeof(char));

  for (i = MAX_LINE_LENGTH; --i >= 0; ) {
    binary[i] = '0' + (integer & 1);
    integer /= 2;
  }

  return binary;
}

unsigned int calcEpsilon(unsigned int gammaRate)
{
  int epsilonRate = gammaRate ^ BINARY_REFERENCE;
  printf("Gamma rate (binary): %s\n", intToBinary(epsilonRate));
  return epsilonRate;
}

int main(void)
{
  char** file = readFile((char *)FILENAME);

  unsigned int gammaRate = calcGamma(file);
  printf("Gamma rate integer: %d\n", gammaRate);

  unsigned int epsilonRate = calcEpsilon(gammaRate);
  printf("Epsilon rate integer: %d\n", epsilonRate);

  printf("Final result: %d\n", gammaRate * epsilonRate);

  free(file);
  return 1;
}