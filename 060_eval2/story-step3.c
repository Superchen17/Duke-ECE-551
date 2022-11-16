#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "error: wrong number of args, expecting 2 or more, exit\n");
    return EXIT_FAILURE;
  }

  size_t indexStory = 0;
  size_t indexCat = 0;

  char ** linesCat = readFile(argv[1], &indexCat);
  char ** linesStory = readFile(argv[2], &indexStory);

  catarray_t * categories = init_catarray();
  fill_catarray(categories, linesCat, indexCat);
  words_t * used_words = init_words();

  for (size_t i = 0; i < indexStory; i++) {
    str_holders_t * holders = fill_holders(linesStory[i]);
    char * out = replace_holders(holders, linesStory[i], categories, used_words, 0);
    printf("%s", out);

    free(out);
    free_holders(holders);
  }

  free_categories(categories);
  free_file(linesStory, indexStory);
  free_file(linesCat, indexCat);
  free_words(used_words);
  return EXIT_SUCCESS;
}
