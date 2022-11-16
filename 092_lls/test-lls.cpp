#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.h"

class Tester {
 public:
  void test1() {
    IntList il;
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
  }

  void test2To9() {
    IntList il;
    il.addFront(1);  // 1
    assert(il.head->data == 1 && il.tail->data == 1);
    assert(il.head->prev == NULL && il.tail->next == NULL);

    il.addBack(10);  // 1, 10
    assert(il.head->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == 1);
    assert(il.head->next->data == 10);
    assert(il.head->next->next == NULL);
    assert(il.tail->data == 10);
    assert(il.tail->prev->data == 1);
    assert(il.tail->prev->prev == NULL);

    il.addFront(3);  // 3, 1, 10
    assert(il.head->prev == NULL && il.tail->next == NULL);
    assert(il.head->data == 3);
    assert(il.head->next->data == 1);
    assert(il.head->next->next->data == 10);
    assert(il.head->next->next->next == NULL);
    assert(il.tail->data == 10);
    assert(il.tail->prev->data == 1);
    assert(il.tail->prev->prev->data == 3);
    assert(il.tail->prev->prev->prev == NULL);

    IntList il2;
    il2.addBack(10);  // 1
    assert(il2.head->data == 10 && il2.tail->data == 10);
    assert(il2.head->prev == NULL && il2.tail->next == NULL);

    il2.addFront(1);  // 1, 10
    assert(il2.head->prev == NULL && il2.tail->next == NULL);
    assert(il2.head->data == 1);
    assert(il2.head->next->data == 10);
    assert(il2.head->next->next == NULL);
    assert(il2.tail->data == 10);
    assert(il2.tail->prev->data == 1);
    assert(il2.tail->prev->prev == NULL);
  }

  void test10To16() {
    IntList il1;
    assert(il1.head == NULL && il1.tail == NULL);

    il1.addBack(1);
    il1.addBack(2);
    il1.addBack(3);

    IntList il2(il1);  // 1, 2, 3
    assert(il2.head->prev == NULL && il2.tail->next == NULL);
    assert(il2.head->data == 1);
    assert(il2.head->next->data == 2);
    assert(il2.head->next->next->data == 3);
    assert(il2.head->next->next->next == NULL);
    assert(il2.tail->data == 3);
    assert(il2.tail->prev->data == 2);
    assert(il2.tail->prev->prev->data == 1);
    assert(il2.tail->prev->prev->prev == NULL);

    IntList il3;
    il3.addBack(50);
    il3 = il1;
    assert(il3.head->prev == NULL && il3.tail->next == NULL);
    assert(il3.head->data == 1);
    assert(il3.head->next->data == 2);
    assert(il3.head->next->next->data == 3);
    assert(il3.head->next->next->next == NULL);
    assert(il3.tail->data == 3);
    assert(il3.tail->prev->data == 2);
    assert(il3.tail->prev->prev->data == 1);
    assert(il3.tail->prev->prev->prev == NULL);
  }

  void test17To26() {
    IntList il1;  // []

    bool r = il1.remove(1);
    assert(r == false && il1.getSize() == 0);

    il1.addBack(1);
    il1.addBack(2);
    il1.addBack(3);
    il1.addBack(4);
    il1.addBack(5);  // 1, 2, 3, 4, 5

    r = il1.remove(3);  // 1, 2, 4, 5
    assert(r == true && il1.getSize() == 4);
    assert(il1.head->prev == NULL && il1.tail->next == NULL);
    assert(il1.head->data == 1);
    assert(il1.head->next->data == 2);
    assert(il1.head->next->next->data == 4);
    assert(il1.head->next->next->next->data == 5);
    assert(il1.head->next->next->next->next == NULL);
    assert(il1.tail->data == 5);
    assert(il1.tail->prev->data == 4);
    assert(il1.tail->prev->prev->data == 2);
    assert(il1.tail->prev->prev->prev->data == 1);
    assert(il1.tail->prev->prev->prev->prev == NULL);

    r = il1.remove(3);  // 1, 2, 4, 5
    assert(r == false && il1.getSize() == 4);
    assert(il1.head->prev == NULL && il1.tail->next == NULL);
    assert(il1.head->data == 1);
    assert(il1.head->next->data == 2);
    assert(il1.head->next->next->data == 4);
    assert(il1.head->next->next->next->data == 5);
    assert(il1.head->next->next->next->next == NULL);
    assert(il1.tail->data == 5);
    assert(il1.tail->prev->data == 4);
    assert(il1.tail->prev->prev->data == 2);
    assert(il1.tail->prev->prev->prev->data == 1);
    assert(il1.tail->prev->prev->prev->prev == NULL);

    r = il1.remove(5);  // 1, 2, 4
    assert(r == true && il1.getSize() == 3);
    assert(il1.head->prev == NULL && il1.tail->next == NULL);
    assert(il1.head->data == 1);
    assert(il1.head->next->data == 2);
    assert(il1.head->next->next->data == 4);
    assert(il1.head->next->next->next == NULL);
    assert(il1.tail->data == 4);
    assert(il1.tail->prev->data == 2);
    assert(il1.tail->prev->prev->data == 1);
    assert(il1.tail->prev->prev->prev == NULL);

    r = il1.remove(1);  // 2, 4
    assert(r == true && il1.getSize() == 2);
    assert(il1.head->prev == NULL && il1.tail->next == NULL);
    assert(il1.head->data == 2);
    assert(il1.head->next->data == 4);
    assert(il1.head->next->next == NULL);
    assert(il1.tail->data == 4);
    assert(il1.tail->prev->data == 2);
    assert(il1.tail->prev->prev == NULL);

    r = il1.remove(2);
    r = il1.remove(4);  // []
    assert(r == true && il1.getSize() == 0);
    assert(il1.head == NULL && il1.tail == NULL);
  }
};

int main(void) {
  Tester t;
  t.test1();
  t.test2To9();
  t.test10To16();
  t.test17To26();
  return EXIT_SUCCESS;
}
