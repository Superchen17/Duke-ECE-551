#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t maxLen = 1;
  size_t index = 0;
  size_t currPos = 0;

  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }

  while (currPos < n - 1) {
    if (array[currPos] < array[currPos + 1]) {
      currPos++;
    }
    else {
      if (currPos - index + 1 > maxLen) {
        maxLen = currPos - index + 1;
      }
      index++;
      currPos = index;
    }
  }

  if (currPos - index + 1 > maxLen) {
    maxLen = currPos - index + 1;
  }
  return maxLen;
}
