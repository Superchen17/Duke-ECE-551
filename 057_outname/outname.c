
#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputName = strdup(inputName);

  const char * suffix = ".counts";
  size_t inputLen = strlen(inputName);
  size_t suffixLen = strlen(suffix);

  outputName = realloc(outputName, (inputLen + suffixLen + 1) * sizeof(*outputName));
  strcpy(outputName + inputLen, suffix);

  return outputName;
}
