#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define ARRSIZE 10

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "incorrect number of params\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "error opening file\n");
    return EXIT_FAILURE;
  }

  int matrix[ARRSIZE][ARRSIZE] = {0};
  char line[ARRSIZE + 2];
  int lineCounter = 0;

  while (fgets(line, ARRSIZE + 2, f)) {
    if (lineCounter > ARRSIZE - 1) {
      fprintf(stderr, "too many lines in file\n");
      return EXIT_FAILURE;
    }

    if (line[10] != '\n') {
      fprintf(stderr, "line contains wrong number of chars\n");
      return EXIT_FAILURE;
    }

    for (int i = 0; i < ARRSIZE; i++) {
      if (line[i] == '\n') {
        fprintf(stderr, "line contains wrong number of chars\n");
        return EXIT_FAILURE;
      }
      matrix[i][ARRSIZE - 1 - lineCounter] = line[i];
    }

    lineCounter++;
  }

  if (lineCounter < ARRSIZE) {
    fprintf(stderr, "too few lines in file\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < ARRSIZE; i++) {
    for (int j = 0; j < ARRSIZE; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }
    fprintf(stdout, "\n");
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "error closing file\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
