#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <iostream>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;

    Node() : key(0), left(NULL), right(NULL) {}
    Node(const K & _key) : key(_key), left(NULL), right(NULL) {}
  };

  Node * root;

  Node * copyHelper(Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    Node * newNode = new Node(curr->key);
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
      std::cout << "<" << curr->key << ">";
      inOrderHelper(curr->right);
    }
  }

 public:
  BstSet() : root(NULL) {}

  BstSet(const BstSet & rhs) : root(NULL) { this->root = copyHelper(rhs.root); }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destructHelper(this->root);
      this->root = copyHelper(rhs.root);
    }
    return *this;
  }

  virtual ~BstSet<K>() { destructHelper(this->root); }

  virtual void add(const K & key) {
    if (this->root == NULL) {
      this->root = new Node(key);
    }
    else {
      Node ** curr = &this->root;
      while (*curr != NULL) {
        if (key == (*curr)->key) {
          //(*curr)->value = value;
          return;
        }
        else if (key < (*curr)->key) {
          curr = &((*curr)->left);
        }
        else {
          curr = &((*curr)->right);
        }
      }
      *curr = new Node(key);
    }
  }

  virtual bool contains(const K & key) const {
    Node * curr = this->root;
    while (curr != NULL) {
      if (key == curr->key) {
        return true;
      }
      else if (key < curr->key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return false;
  }

  virtual void remove(const K & key) {
    Node ** toRemove = &(this->root);

    while (*toRemove != NULL) {
      if ((*toRemove)->key == key) {
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
          Node * temp = (*toRemove)->left;
          delete *toRemove;
          *toRemove = temp;
          add((*successor)->key);
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
