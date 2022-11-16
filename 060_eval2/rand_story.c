#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * read file containing the story
 * @param char * fileName: the name of file
 * @param size_t lineCount: number of lines in the file
 * @return char **: array of strings containing parsed file data, 1 line per element
 */
char ** readFile(char * fileName, size_t * lineCount) {
  FILE * f = fopen(fileName, "r");
  if (f == NULL) {
    fprintf(stderr, "error: cannot open file, exit\n");
    exit(EXIT_FAILURE);
  }

  char ** lines = NULL;
  char * curr = NULL;
  size_t linecapp = 0;

  while (getline(&curr, &linecapp, f) >= 0) {
    lines = realloc(lines, (*lineCount + 1) * sizeof(*lines));
    lines[*lineCount] = curr;
    curr = NULL;
    (*lineCount)++;
  }
  free(curr);

  if (fclose(f) != 0) {
    fprintf(stderr, "error: cannot close file, exit\n");
    exit(EXIT_FAILURE);
  }
  return lines;
}

/**
 * free malloced memory of parsed file data
 * @param char ** lines: array of strings containing parsed file data, 1 line per element
 * @param size_t index: number of lines parsed
 */
void free_file(char ** lines, size_t index) {
  for (size_t i = 0; i < index; i++) {
    free(lines[i]);
  }
  free(lines);
}

/**
 * fill an array of str_holder_t structs, each demarcating the start and stop position of a placeholder
 * @param char * line: a line from parsed file
 * @return str_holders_t * : a pointer to a str_holders_t struct, containing all placeholderx boundaries
 */
str_holders_t * fill_holders(char * line) {
  str_holders_t * holders = malloc(sizeof(*holders));
  holders->counter = 0;
  holders->arr = NULL;

  char * lineTemp = line;
  size_t holder_flag = 0;
  char * underscore = strchr(lineTemp, '_');

  while (underscore != NULL) {
    if (holder_flag == 0) {
      holders->arr =
          realloc(holders->arr, (holders->counter + 1) * sizeof(*holders->arr));
      str_holder_t * holder = malloc(sizeof(*holder));
      holder->start = underscore - line;
      holder->end = 0;
      holders->arr[holders->counter] = holder;
      holders->counter++;
      holder = NULL;
      holder_flag = 1;
    }
    else {
      holders->arr[holders->counter - 1]->end = underscore - line;
      holder_flag = 0;
    }

    lineTemp = underscore + 1;
    underscore = strchr(lineTemp, '_');
  }

  if (holder_flag == 1) {
    fprintf(stderr, "error: odd number of underscores, exit\n");
    exit(EXIT_FAILURE);
  }

  return holders;
}

/**
 * converting the a digit placeholder from string to integer
 * @param char * holder: a digit placeholder in string form
 * @return int: placeholder converted to digit
 */
int holder_to_decimal(char * holder) {
  int out = 0;
  for (size_t i = 0; i < strlen(holder); i++) {
    if (isdigit(holder[i])) {
      out = out * 10 + holder[i] - '0';
    }
    else {
      fprintf(stderr, "error: placeholder does not exist, or is not a number, exit\n");
      exit(EXIT_FAILURE);
    }
  }
  return out;
}

/**
 * remove a selected word from a category
 * if there are multiple duplicate words, ONLY remove 1
 * @param catarray_t * categories: pointer to a catarray_t struct
 * @param char * cat_name: category name
 * @param char * cat_word: word to be removed from the category
 */
void remove_word_from_cat(catarray_t * categories, char * cat_name, char * cat_word) {
  int cat_index = get_cat_index_from_arr(categories, cat_name);
  if (cat_index < 0) {
    fprintf(stderr, "error: removing a non-existing word from category, exit\n");
    exit(EXIT_FAILURE);
  }

  category_t * old_cat = &(categories->arr[cat_index]);
  category_t new_cat;
  new_cat.n_words = 0;
  new_cat.name = strdup(cat_name);
  new_cat.words = NULL;

  int replace_flag = 0;
  for (size_t i = 0; i < old_cat->n_words; i++) {
    if (strcmp(old_cat->words[i], cat_word) == 0 && replace_flag == 0) {
      replace_flag = 1;
    }
    else {
      new_cat.words =
          realloc(new_cat.words, (new_cat.n_words + 1) * (sizeof *new_cat.words));
      new_cat.words[new_cat.n_words] = strdup(old_cat->words[i]);
      new_cat.n_words++;
    }
    free(old_cat->words[i]);
  }
  free(old_cat->words);
  free(old_cat->name);
  categories->arr[cat_index] = new_cat;
}

/**
 * find a corresponding word given a category name
 * @param str_holder_t * holder: pointer to a str_holder_t struct, containing boundaries of a placeholder
 * @param char * line: the string containing the placeholder
 * @param catarray_t * categories: pointer to a catarray_t struct
 * @param words_t * used_words: pointer to a words_t struct, containing all used words 
 * @param int deduplicate: substitution deduplication flag
 * @return char * : a replacement word
 */
char * find_holder_value(str_holder_t * holder,
                         char * line,
                         catarray_t * categories,
                         words_t * used_words,
                         int deduplicate) {
  int len_holder_key = holder->end - holder->start - 1;
  char holder_key[len_holder_key + 1];
  memcpy(holder_key, line + holder->start + 1, len_holder_key);
  holder_key[len_holder_key] = '\0';

  // check if no entries in categories
  if (categories == NULL) {
    const char * holder_value = chooseWord(holder_key, NULL);
    char * holder_value_temp = strdup(holder_value);
    return holder_value_temp;
  }
  else {
    // check if any category match the placeholder key
    int cat_index = get_cat_index_from_arr(categories, holder_key);
    if (cat_index != -1) {
      if (categories->arr[cat_index].n_words == 0) {
        fprintf(stderr,
                "error: no more unique word available for category \"%s\", exit\n",
                categories->arr[cat_index].name);
        exit(EXIT_FAILURE);
      }
      const char * holder_value = chooseWord(holder_key, categories);
      char * holder_value_temp = strdup(holder_value);
      add_word_to_words(used_words, holder_value_temp);
      if (deduplicate == 1) {
        remove_word_from_cat(categories, holder_key, holder_value_temp);
      }
      return holder_value_temp;
    }
    // check if the placeholder key is a number
    else {
      int holder_num = holder_to_decimal(holder_key);
      if (holder_num < 1) {
        fprintf(stderr, "error: placeholder rewinder less than 1, exit\n");
        exit(EXIT_FAILURE);
      }
      if ((size_t)holder_num > used_words->counter) {
        fprintf(stderr, "error: placeholder rewinder offset bigger than buffer, exit\n");
        exit(EXIT_FAILURE);
      }
      const char * holder_value = used_words->words[used_words->counter - holder_num];
      char * holder_value_temp = strdup(holder_value);
      add_word_to_words(used_words, holder_value_temp);

      return holder_value_temp;
    }
  }
}

/**
 * replace all placeholders for a single line
 * @param str_holders_t * holders: pointer to a str_holders_t struct, containing boundaries of all placeholders
 * @param char * line: the string containing the placeholder
 * @param catarray_t * categories: pointer to a catarray_t struct
 * @param words_t * used_words: pointer to a words_t struct, containing all used words 
 * @param int deduplicate: substitution deduplication flag
 * @return char * : a line with all its placeholders substituted
 */
char * replace_holders(str_holders_t * holders,
                       char * line,
                       catarray_t * categories,
                       words_t * used_words,
                       int deduplicate) {
  if (holders->counter == 0) {
    char * out = strdup(line);
    return out;
  }

  char * out = NULL;
  int outLen = 0;

  for (size_t j = 0; j < holders->counter; j++) {
    if (j == 0) {
      int len;
      if (holders->arr[j]->start != 0) {
        len = holders->arr[j]->start;
        out = realloc(out, (outLen + len) * sizeof(*out));
        memcpy(out + outLen, line, len);
        outLen += len;
      }

      char * sub =
          find_holder_value(holders->arr[j], line, categories, used_words, deduplicate);
      len = strlen(sub);

      out = realloc(out, (outLen + len) * sizeof(*out));
      memcpy(out + outLen, sub, len);
      free(sub);
      outLen += len;
    }
    else {
      int len = holders->arr[j]->start - holders->arr[j - 1]->end - 1;
      out = realloc(out, (outLen + len) * sizeof(*out));
      memcpy(out + outLen, line + holders->arr[j - 1]->end + 1, len);
      outLen += len;

      char * sub =
          find_holder_value(holders->arr[j], line, categories, used_words, deduplicate);
      len = strlen(sub);

      out = realloc(out, (outLen + len) * sizeof(*out));
      memcpy(out + outLen, sub, len);
      free(sub);
      outLen += len;
    }
    if (j == holders->counter - 1) {
      int len = strlen(line) - holders->arr[j]->end;
      out = realloc(out, (outLen + len) * sizeof(*out));
      memcpy(out + outLen, line + holders->arr[j]->end + 1, len);
      outLen += len;
    }
  }
  return out;
}

/**
 * initialize an empty words_t struct
 * @return words_t * : a pointer to an empty words_t struct
 */
words_t * init_words() {
  words_t * words = malloc(sizeof(*words));
  words->counter = 0;
  words->words = NULL;
  return words;
}

/**
 * add a word to a words_t struct
 * @param words_t * words: a pointer to a words_t struct
 * @param char * word: the new word to be added
 */
void add_word_to_words(words_t * words, char * word) {
  words->words = realloc(words->words, (words->counter + 1) * sizeof(*words->words));
  words->words[words->counter] = strdup(word);
  words->counter++;
}

/**
 * free all malloced space of a words_t struct
 * @param words_t * words: a pointer to a words_t struct
 */
void free_words(words_t * words) {
  for (size_t i = 0; i < words->counter; i++) {
    free(words->words[i]);
  }
  free(words->words);
  free(words);
}

/**
 * free all malloced space of a str_holders_t struct
 * @param str_holders_t * holders: a pointer to a str_holders_t struct
 */
void free_holders(str_holders_t * holders) {
  for (size_t i = 0; i < holders->counter; i++) {
    free(holders->arr[i]);
  }
  free(holders->arr);
  free(holders);
}

/**
 * initialize a empty catarray_t struct
 * @return catarray_t * : pointer to an empty catarray_t struct 
 */
catarray_t * init_catarray() {
  catarray_t * categories = malloc(sizeof(*categories));
  categories->n = 0;
  categories->arr = NULL;
  return categories;
}

/**
 * populate an catarray_t struct with category information
 * @param catarray_t * categories: pointer to a catarray_t struct
 * @param char ** lines: parsed lines containing category information
 * @param size_t index: number of parsed lines
 */
void fill_catarray(catarray_t * categories, char ** lines, size_t index) {
  for (size_t i = 0; i < index; i++) {
    char * colon = strchr(lines[i], ':');
    if (colon == NULL) {
      fprintf(stderr, "error: no delimiter found in line, exit\n");
      exit(EXIT_FAILURE);
    }

    int len_name = colon - lines[i];
    char name[len_name + 1];
    strncpy(name, lines[i], len_name);
    name[len_name] = '\0';

    char * nl = strchr(lines[i], '\n');
    int len_word = nl - colon - 1;
    char word[len_word + 1];
    strncpy(word, colon + 1, len_word);
    word[len_word] = '\0';

    add_to_catarray(categories, name, word);
  }
}

/**
 * get the index of a given category from a catarray_t struct
 * @param catarray_t * categories: pointer to a catarray_t struct
 * @param char * name: name of the category for which to obtain the index
 * @return int: the index of the category inside the catarray_t struct
 */
int get_cat_index_from_arr(catarray_t * categories, char * name) {
  for (size_t i = 0; i < categories->n; i++) {
    if (strcmp(categories->arr[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

/**
 * add a pair of <category_name,word> to a catarray_t struct
 * @param catarray_t * categories: pointer to a catarray_t struct
 * @param char * name: category name wish to be added
 * @param char * word: category word wish to be added
 */
void add_to_catarray(catarray_t * categories, char * name, char * word) {
  int index = get_cat_index_from_arr(categories, name);

  if (index == -1) {
    category_t category;
    category.name = strdup(name);
    category.words = malloc(sizeof(*category.words));
    category.words[0] = strdup(word);
    category.n_words = 1;

    categories->arr =
        realloc(categories->arr, (categories->n + 1) * sizeof(*categories->arr));
    categories->arr[categories->n] = category;
    categories->n++;
  }
  else {
    category_t * category = &(categories->arr[index]);
    category->words =
        realloc(category->words, (category->n_words + 1) * sizeof(*category->words));
    category->words[category->n_words] = strdup(word);
    category->n_words++;
  }
}

/**
 * free all malloced space of a catarray_t struct
 * @param catarray_t * categories: pointer to a catarray_t struct
 */
void free_categories(catarray_t * categories) {
  for (size_t i = 0; i < categories->n; i++) {
    for (size_t j = 0; j < categories->arr[i].n_words; j++) {
      free(categories->arr[i].words[j]);
    }
    free(categories->arr[i].words);
    free(categories->arr[i].name);
  }
  free(categories->arr);
  free(categories);
}
