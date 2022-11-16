#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "error: wrong number of args, expecting 3 or 4, exit\n");
    return EXIT_FAILURE;
  }

  size_t indexStory = 0;
  size_t indexCat = 0;

  int deduplicate = 0;
  if (argc == 4) {
    if (strcmp(argv[1], "-n") == 0) {
      deduplicate = 1;
    }
    else {
      fprintf(stderr, "error: unknown optional flag, exit\n");
      return EXIT_FAILURE;
    }
  }

  char ** linesCat = readFile(argc == 3 ? argv[1] : argv[2], &indexCat);
  char ** linesStory = readFile(argc == 3 ? argv[2] : argv[3], &indexStory);

  catarray_t * categories = init_catarray();
  fill_catarray(categories, linesCat, indexCat);
  words_t * used_words = init_words();

  for (size_t i = 0; i < indexStory; i++) {
    str_holders_t * holders = fill_holders(linesStory[i]);
    char * out =
        replace_holders(holders, linesStory[i], categories, used_words, deduplicate);
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
