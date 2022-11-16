#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class indexOutOfBoundException : public std::exception {
 public:
  virtual const char * what() const throw() { return "error: index out of bound\n"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    Node() : data(0), next(NULL), prev(NULL){};
    Node(T d) : data(d), next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };

  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      Node * curr = this->head;
      while (curr != NULL) {
        Node * nextNode = curr->next;
        delete curr;
        curr = nextNode;
      }
      tail = NULL;

      for (int i = 0; i < rhs.getSize(); i++) {
        addBack(rhs[i]);
      }
    }
    return *this;
  }

  ~LinkedList() {
    Node * curr = this->head;
    while (curr != NULL) {
      Node * nextNode = curr->next;
      delete curr;
      curr = nextNode;
    }
    this->head = NULL;
    this->tail = NULL;
  }

  void addFront(const T & item) {
    Node * newNode = new Node(item);
    if (this->head == NULL) {
      this->head = newNode;
      this->tail = newNode;
    }
    else {
      newNode->next = this->head;
      this->head->prev = newNode;
      this->head = newNode;
    }
  }

  void addBack(const T & item) {
    Node * newNode = new Node(item);
    if (this->tail == NULL) {
      this->head = newNode;
      this->tail = newNode;
    }
    else {
      newNode->prev = this->tail;
      this->tail->next = newNode;
      this->tail = newNode;
    }
  }

  bool remove(const T & item) {
    // empty list
    if (this->head == NULL) {
      return false;
    }

    // not found
    int index = this->find(item);
    if (index == -1) {
      return false;
    }

    // first element
    if (index == 0) {
      Node * toRemove = this->head;

      // first and only element
      if (this->head == this->tail) {
        this->tail = NULL;
        this->head = NULL;
      }
      else {
        this->head = this->head->next;
        this->head->prev = NULL;
      }
      delete toRemove;
      return true;
    }

    Node * curr = this->head;
    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }

    // last element
    if (curr == this->tail) {
      Node * toRemove = this->tail;
      this->tail = this->tail->prev;
      this->tail->next = NULL;
      delete toRemove;
      return true;
    }

    // middle element
    Node * toRemove = curr;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete toRemove;
    return true;
  }

  const T & operator[](int index) const {
    try {
      Node * curr = this->head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
    catch (indexOutOfBoundException & e) {
      throw e;
    }
  }

  T & operator[](int index) {
    try {
      Node * curr = this->head;
      for (int i = 0; i < index; i++) {
        curr = curr->next;
      }
      return curr->data;
    }
    catch (indexOutOfBoundException & e) {
      throw e;
    }
  }

  int find(const T & item) const {
    int index = 0;
    Node * curr = this->head;
    while (curr != NULL) {
      if (curr->data == item) {
        return index;
      }
      index++;
      curr = curr->next;
    }

    return -1;
  }

  int getSize() const {
    Node * curr = this->head;
    int count = 0;
    while (curr != NULL) {
      count++;
      curr = curr->next;
    }

    return count;
  }

  friend class Tester;
};

typedef LinkedList<int> IntList;

#endif
