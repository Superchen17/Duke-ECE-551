#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "error: wrong number of args, expecting 1, exit\n");
    return EXIT_FAILURE;
  }

  size_t index = 0;
  char ** lines = readFile(argv[1], &index);

  catarray_t * categories = init_catarray();
  fill_catarray(categories, lines, index);
  printWords(categories);

  free_categories(categories);
  free_file(lines, index);

  return EXIT_SUCCESS;
}
