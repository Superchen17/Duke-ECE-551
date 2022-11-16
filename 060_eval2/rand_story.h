#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

//*---------- structs ----------*//
// string placeholder, record start and end indices
struct _str_holder_t {
  int start;
  int end;
};
typedef struct _str_holder_t str_holder_t;

// array of placeholders
struct _str_holders_t {
  str_holder_t ** arr;
  size_t counter;
};
typedef struct _str_holders_t str_holders_t;

// array of used words
struct _words_t {
  char ** words;
  size_t counter;
};
typedef struct _words_t words_t;

//*---------- functions ----------*//
char ** readFile(char * fileName, size_t * lineCount);
void free_file(char ** lines, size_t index);

str_holders_t * fill_holders(char * lines);
char * replace_holders(str_holders_t * holders,
                       char * line,
                       catarray_t * categories,
                       words_t * used_words,
                       int deduplicate);
int holder_to_decimal(char * holder);
void remove_word_from_cat(catarray_t * categories, char * cat_name, char * cat_word);
char * find_holder_value(str_holder_t * holder,
                         char * line,
                         catarray_t * categories,
                         words_t * used_words,
                         int deduplicate);
words_t * init_words();
void add_word_to_words(words_t * used_words, char * word);
void free_words(words_t * words);
void free_holders(str_holders_t * holders);

catarray_t * init_catarray();
void fill_catarray(catarray_t * categories, char ** lines, size_t index);
int get_cat_index_from_arr(catarray_t * categories, char * name);
void add_to_catarray(catarray_t * categories, char * name, char * word);
void free_categories(catarray_t * categories);

#endif
