#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  //if (x == 0 && y == 0) {
  //  exit(EXIT_FAILURE);
  //}

  unsigned actual = power(x, y);
  if (actual != expected_ans) {
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(2, 3, 8);
  run_check(2, 0, 1);
  run_check(1, 1, 1);
  run_check(1, 2, 1);
  run_check(0, 2, 0);
  run_check(123, 3, 1860867);
  run_check(1234, 3, 1879080904);
  run_check(2, 25, 33554432);
  run_check(2, 31, 2147483648);
  run_check(0, 0, 1);

  return EXIT_SUCCESS;
}
