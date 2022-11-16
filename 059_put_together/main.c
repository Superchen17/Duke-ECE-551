#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME

  counts_t * counts = createCounts();
  if (counts == NULL) {
    perror("error creating counts on stack, exit\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("error opening file, exit\n");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    char * line_temp = strdup(line);
    line_temp[strlen(line_temp) - 1] = '\0';
    addCount(counts, lookupValue(kvPairs, line_temp));

    free(line_temp);
  }
  free(line);

  if (fclose(f) != 0) {
    perror("error closing file, exit\n");
    exit(EXIT_FAILURE);
  }

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)

  //count from 2 to argc (call the number you count i)

  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)

  //compute the output file name from argv[i] (call this outName)

  //open the file named by outName (call that f)

  //print the counts from c into the FILE f

  //close f

  //free the memory for outName and c

  //free the memory for kv

  if (argc < 3) {
    perror("error, must have more than 3 args, exit\n");
    return EXIT_FAILURE;
  }

  kvarray_t * kv = readKVs(argv[1]);

  for (int i = 2; i < argc; i++) {
    counts_t * counts = countFile(argv[i], kv);
    char * outFile = computeOutputFileName(argv[i]);

    FILE * f = fopen(outFile, "w");
    if (f == NULL) {
      perror("error opening output file, exit\n");
      return EXIT_FAILURE;
    }

    printCounts(counts, f);

    if (fclose(f) != 0) {
      perror("error closing output file, exit\n");
      return EXIT_FAILURE;
    }

    free(outFile);
    freeCounts(counts);
  }

  freeKVs(kv);

  return EXIT_SUCCESS;
}
