#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  assert(f != NULL);

  kvarray_t * kvarr = malloc(sizeof(*kvarr));
  assert(kvarr != NULL);

  kvarr->pairs = malloc(sizeof(*kvarr->pairs));
  assert(kvarr->pairs != NULL);

  kvarr->size = 0;

  char * line = NULL;
  size_t bufferSize = 0;

  while (getline(&line, &bufferSize, f) >= 0) {
    kvpair_t * pair = malloc(sizeof(*pair));
    assert(pair != NULL);

    char * delimiter = strchr(line, '=');
    assert(delimiter != NULL);

    size_t name_length = delimiter - line;
    pair->name = strndup(line, name_length);

    char * end = strchr(delimiter + 1, '\n');
    size_t rank_length = end - delimiter - 1;
    pair->rank = strndup(delimiter + 1, rank_length);

    kvarr->pairs = realloc(kvarr->pairs, (kvarr->size + 1) * sizeof(*kvarr->pairs));
    assert(kvarr->pairs != NULL);

    kvarr->pairs[kvarr->size] = pair;
    pair = NULL;
    kvarr->size++;
  }
  free(line);

  if (fclose(f) != 0) {
    perror("error closing file, exit\n");
    exit(EXIT_FAILURE);
  }

  return kvarr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    free(pairs->pairs[i]->name);
    free(pairs->pairs[i]->rank);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i]->name, pairs->pairs[i]->rank);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    if (strcmp(pairs->pairs[i]->name, key) == 0) {
      return pairs->pairs[i]->rank;
    }
  }
  return NULL;
}
