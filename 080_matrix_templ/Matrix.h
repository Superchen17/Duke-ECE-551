#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix();                                //default constructor
  Matrix(int r, int c);                    // overloading constructor
  Matrix(const Matrix & rhs);              //copy constructor
  Matrix & operator=(const Matrix & rhs);  //copy assignment operator
  ~Matrix();                               // destructor

  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(0) {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  this->rows.resize(this->numRows);
  for (int i = 0; i < this->numRows; i++) {
    this->rows[i].resize(this->numColumns);
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(rhs.rows) {
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  this->numRows = rhs.numRows;
  this->numColumns = rhs.numColumns;
  this->rows = rhs.rows;

  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return this->numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return this->numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert((index >= 0) && (index < this->numRows));
  return this->rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert((index >= 0) && (index < this->numRows));
  return this->rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if (this->numRows == rhs.numRows && this->numColumns == rhs.numColumns &&
      this->rows == rhs.rows) {
    return true;
  }
  return false;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(this->numRows == rhs.numRows && this->numColumns == rhs.numColumns);

  Matrix<T> out(*this);
  for (int i = 0; i < this->numRows; i++) {
    for (int j = 0; j < this->numColumns; j++) {
      out[i][j] += rhs[i][j];
    }
  }
  return out;
}

template<typename T>
Matrix<T>::~Matrix() {
  this->rows.clear();
  this->numColumns = 0;
  this->numRows = 0;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << "{";
    for (int j = 0; j < rhs.getColumns(); j++) {
      if (j != rhs.getColumns() - 1) {
        s << rhs[i][j] << ", ";
      }
      else {
        s << rhs[i][j] << "}";
      }
    }
    if (i != rhs.getRows() - 1) {
      s << "," << std::endl;
    }
  }
  s << " ]";

  return s;
}
#endif
