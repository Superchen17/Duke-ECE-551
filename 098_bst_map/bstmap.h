#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;

    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(const K & _key, const V & _value) :
        key(_key),
        value(_value),
        left(NULL),
        right(NULL) {}
  };

  Node * root;

  Node * copyHelper(Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    Node * newNode = new Node(curr->key, curr->value);
    newNode->left = copyHelper(curr->left);
    newNode->right = copyHelper(curr->right);
    return newNode;
  }

  Node ** lookupNode(const K & key) {
    Node * curr = this->root;
    while (curr != NULL) {
      if (key == curr->key) {
        return &curr;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return NULL;
  }

  void destructHelper(Node * _root) {
    if (_root != NULL) {
      destructHelper(_root->left);
      destructHelper(_root->right);
      delete _root;
    }
  }

  void inOrderHelper(Node * curr) {
    if (curr != NULL) {
      inOrderHelper(curr->left);
      std::cout << "<" << curr->key << "," << curr->value << ">";
      inOrderHelper(curr->right);
    }
  }

 public:
  BstMap() : root(NULL) {}

  BstMap(const BstMap & rhs) : root(NULL) { this->root = copyHelper(rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destructHelper(this->root);
      this->root = copyHelper(rhs.root);
    }
    return *this;
  }

  virtual ~BstMap<K, V>() { destructHelper(this->root); }

  virtual void add(const K & key, const V & value) {
    if (this->root == NULL) {
      this->root = new Node(key, value);
    }
    else {
      Node ** curr = &this->root;
      while (*curr != NULL) {
        if (key == (*curr)->key) {
          (*curr)->value = value;
          return;
        }
        else if (key < (*curr)->key) {
          curr = &((*curr)->left);
        }
        else {
          curr = &((*curr)->right);
        }
      }
      *curr = new Node(key, value);
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = this->root;
    while (curr != NULL) {
      if (key == curr->key) {
        return curr->value;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    throw std::invalid_argument("exception: key not found\n");
  }

  virtual void remove(const K & key) {
    Node ** toRemove = &(this->root);

    while (*toRemove != NULL) {
      if ((*toRemove)->key == key) {
        /*
        // both children empty
        if ((*toRemove)->left == NULL && (*toRemove)->right == NULL) {
          delete *toRemove;
        }
	*/
        // has left children
        if ((*toRemove)->right == NULL) {
          Node * successor = (*toRemove)->left;
          delete *toRemove;
          *toRemove = successor;
        }
        // has right children
        else if ((*toRemove)->left == NULL) {
          Node * successor = (*toRemove)->right;
          delete *toRemove;
          *toRemove = successor;
        }
        // has both children
        else {
          Node ** successor = toRemove;
          toRemove = &((*toRemove)->left);
          while ((*toRemove)->right != NULL) {
            toRemove = &((*toRemove)->right);
          }
          (*successor)->key = (*toRemove)->key;
          const V value = (*toRemove)->value;
          Node * temp = (*toRemove)->left;
          delete *toRemove;
          *toRemove = temp;
          add((*successor)->key, value);
        }
      }
      else if (key < (*toRemove)->key) {
        toRemove = &(*toRemove)->left;
      }
      else {
        toRemove = &(*toRemove)->right;
      }
    }
  }

  void inOrder() {
    inOrderHelper(this->root);
    std::cout << std::endl;
  }
};

#endif
