#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class PosFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 1; }
};

class NegFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -1; }
};

class LinearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  unsigned maxOp = 1;
  if (high > low) {
    maxOp = log2(high - low) + 1;
  }

  CountedIntFn * cif = new CountedIntFn(maxOp, f, mesg);
  int ans = binarySearchForZero(cif, low, high);
  delete cif;

  if (expected_ans != ans) {
    std::cerr << mesg << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  SinFunction * sinF = new SinFunction();
  PosFunction * posF = new PosFunction();
  NegFunction * negF = new NegFunction();
  LinearFunction * linF = new LinearFunction();

  check(sinF, 0, 150000, 52359, "error running SinFunction");
  check(posF, 1, 10, 1, "error running posF 1");
  check(posF, -10, -1, -10, "error running posF 2");
  check(posF, -10, 10, -10, "error, running posF 3");
  check(negF, 1, 10, 9, "error running negF 1");
  check(negF, -10, -1, -2, "error running negF 2");
  check(negF, -10, 10, 9, "error, running negF 3");
  check(linF, 1, 10, 1, "error running linF 1");
  check(linF, -10, -1, -2, "error running linF 2");
  check(linF, -10, 10, 0, "error, running linF 3");
  check(linF, -1, 10, 0, "error, running linF 4");

  delete sinF;
  delete posF;
  delete negF;
  delete linF;

  return EXIT_SUCCESS;
}
