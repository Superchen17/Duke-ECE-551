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
  words_t * used_words = init_words();

  for (size_t i = 0; i < index; i++) {
    str_holders_t * holders = fill_holders(lines[i]);
    char * out = replace_holders(holders, lines[i], NULL, used_words, 0);
    printf("%s", out);

    free(out);
    free_holders(holders);
  }

  free_words(used_words);
  free_file(lines, index);

  return EXIT_SUCCESS;
}
