#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void test(int * array, size_t n, size_t expected) {
  if (maxSeq(array, n) != expected) {
    printf("failed\n");

    for (int i = 0; i < n - 1; i++) {
      printf("%d ", array[i]);
    }

    printf("%d\n", array[n - 1]);
    printf("expect %ld, got %ld\n", maxSeq(array, n), expected);
    exit(EXIT_FAILURE);
  }
}

int main() {
  int case0_0[] = {1};
  int case0_1[] = {0};
  int case0_2[] = {-1};

  int case1_0[] = {1, 1, 1};
  int case1_1[] = {0, 0, 0};
  int case1_2[] = {-1, -1, -1};

  int case2_0[] = {2, 1, 2, 4, 7};
  int case2_1[] = {3, 7, 1, 3, 9, 1, 2, 3};
  int case2_2[] = {-3, -1, 5, 2, -3, 1, 2, 3};
  int case2_3[] = {1, 2, 3, 3, 4, 6, 8, 9, -5};
  int case2_4[] = {1, -5, 2, 4, 7, 5, 6, 8};

  test(case0_0, 1, 1);
  test(case0_1, 1, 1);
  test(case0_2, 1, 1);
  test(case0_2, 0, 0);

  test(case1_0, 3, 1);
  test(case1_1, 3, 1);
  test(case1_2, 3, 1);
  test(case2_0, 5, 4);
  test(case2_1, 8, 3);
  test(case2_2, 8, 4);
  test(case2_3, 9, 5);
  test(case2_4, 8, 4);

  return EXIT_SUCCESS;
}
