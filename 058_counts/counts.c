#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  assert(counts != NULL);

  counts->string_arr = NULL;
  counts->size = 0;
  counts->unknown = 0;

  return counts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
  }
  else {
    for (size_t i = 0; i < c->size; i++) {
      if (strcmp(name, c->string_arr[i]->string) == 0) {
        c->string_arr[i]->occurance++;
        return;
      }
    }
    c->string_arr = realloc(c->string_arr, (c->size + 1) * sizeof(*c->string_arr));
    assert(c->string_arr != NULL);

    one_count_t * new_tuple = malloc(sizeof(*new_tuple));
    assert(new_tuple != NULL);

    new_tuple->occurance = 1;
    new_tuple->string = strdup(name);

    c->string_arr[c->size] = new_tuple;
    c->size++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  assert(outFile != NULL);

  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %zu\n", c->string_arr[i]->string, c->string_arr[i]->occurance);
  }
  if (c->unknown != 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    free(c->string_arr[i]->string);
    free(c->string_arr[i]);
  }
  free(c->string_arr);
  free(c);
}
