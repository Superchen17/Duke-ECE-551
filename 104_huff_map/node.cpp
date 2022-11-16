#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  if (this->sym != NO_SYM) {
    assert(this->left == NULL);
    assert(this->right == NULL);
    theMap[this->sym] = b;
  }
  else {
    assert(this->left != NULL);
    assert(this->right != NULL);
    this->left->buildMap(b.plusZero(), theMap);
    this->right->buildMap(b.plusOne(), theMap);
  }
}
