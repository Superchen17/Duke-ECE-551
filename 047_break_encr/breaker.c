#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_LEN 26
#define ASCII_OFFSET 97

void get_frequency(FILE * f, int * freqArr) {
  int c;

  //* check file open status
  if (f == NULL) {
    fprintf(stderr, "unable to open file, exit now\n");
    //perror("unable to open file, exit now\n");
    exit(EXIT_FAILURE);
  }

  //* create frequency table
  while ((c = fgetc(f)) != EOF) {
    if (!isalpha(c)) {
      continue;
    }

    c = tolower(c);
    freqArr[c - ASCII_OFFSET]++;
  }
}

int get_letter_e(int * freqArr) {
  int index = 0;
  int max = 0;

  for (int i = 0; i < ALPHABET_LEN; i++) {
    if (freqArr[i] > max) {
      max = freqArr[i];
      index = i;
    }
  }

  return index;
}

int get_key(int plain, int encrypt) {
  return encrypt - plain >= 0 ? encrypt - plain : encrypt - plain + ALPHABET_LEN;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "program requires 2 arguments to run, get %d\n", argc);
    //perror("incorrect number of arguments, exit now\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("cannot open file");
    return EXIT_FAILURE;
  }

  int freqArr[ALPHABET_LEN] = {0};
  get_frequency(f, freqArr);

  if (fclose(f) != 0) {
    perror("cannot close file");
    return EXIT_FAILURE;
  }

  int index = get_letter_e(freqArr);
  int key = get_key('e', index + ASCII_OFFSET);
  printf("%d\n", key);

  return EXIT_SUCCESS;
}
