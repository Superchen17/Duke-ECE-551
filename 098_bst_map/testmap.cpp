#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, std::string> bst;
  bst.add(10, "number 10");
  bst.add(15, "number 15");
  bst.add(20, "number 20");
  bst.add(6, "number 6");
  bst.add(7, "number 7");
  bst.add(3, "number 3");

  bst.inOrder();
  bst.remove(10);
  bst.inOrder();

  BstMap<int, std::string> bst2;
  bst2.add(20, "number 20");
  bst2.add(6, "number 6");
  bst2.add(7, "number 7");
  bst.inOrder();

  bst = bst2;
  bst.inOrder();

  BstMap<int, std::string> bst3(bst2);
  bst3.inOrder();

  return EXIT_SUCCESS;
}
