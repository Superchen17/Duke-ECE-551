#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main(void) {
  BstSet<int> bst;
  bst.add(10);
  bst.add(15);
  bst.add(20);
  bst.add(6);
  bst.add(7);
  bst.add(3);

  bst.inOrder();
  bst.remove(10);
  bst.inOrder();

  BstSet<int> bst2;
  bst2.add(20);
  bst2.add(6);
  bst2.add(7);
  bst.inOrder();

  bst = bst2;
  bst.inOrder();

  BstSet<int> bst3(bst2);
  bst3.inOrder();

  return EXIT_SUCCESS;
}
