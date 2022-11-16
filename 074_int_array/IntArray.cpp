#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < this->numElements; i++) {
    this->data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] this->data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] this->data;
    this->numElements = rhs.numElements;
    this->data = temp;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < this->numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < this->numElements);
  return data[index];
}

int IntArray::size() const {
  return this->numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements) {
    return false;
  }
  for (int i = 0; i < this->numElements; i++) {
    if (this->data[i] != rhs.data[i]) {
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements) {
    return true;
  }
  for (int i = 0; i < this->numElements; i++) {
    if (this->data[i] != rhs.data[i]) {
      return true;
    }
  }
  return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if (rhs.size() == 0) {
    s << "{}";
    return s;
  }

  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  s << rhs[rhs.size() - 1];
  s << "}";

  return s;
}
