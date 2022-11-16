#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  std::ifstream f;
  f.open(fname, std::fstream::in);
  if (!f.is_open()) {
    std::cerr << "error: cannot open file, exit" << std::endl;
    exit(EXIT_FAILURE);
  }

  uint64_t * freqArr = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    freqArr[i] = 0;
  }

  int c = 0;
  while ((c = f.get()) != EOF) {
    freqArr[c]++;
  }
  f.close();

  freqArr[256]++;
  return freqArr;
}
