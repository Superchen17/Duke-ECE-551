#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) {
  this->numRows = r;
  this->numColumns = c;

  this->rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    this->rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  this->numRows = rhs.numRows;
  this->numColumns = rhs.numColumns;
  this->rows = new IntArray *[this->numRows];

  for (int i = 0; i < this->numRows; i++) {
    this->rows[i] = new IntArray(rhs[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < this->numRows; i++) {
    delete this->rows[i];
  }
  delete[] this->rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs[i]);
    }

    for (int i = 0; i < this->numRows; i++) {
      delete this->rows[i];
    }
    delete[] this->rows;

    this->numColumns = rhs.numColumns;
    this->numRows = rhs.numRows;
    this->rows = temp;
  }

  return *this;
}
int IntMatrix::getRows() const {
  return this->numRows;
}
int IntMatrix::getColumns() const {
  return this->numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < this->numRows);
  return *(this->rows[index]);
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < this->numRows);
  return *(this->rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (this->numColumns != rhs.numColumns || this->numRows != rhs.numRows) {
    return false;
  }

  for (int i = 0; i < this->numRows; i++) {
    if (*this->rows[i] != *rhs.rows[i]) {
      return false;
    }
  }

  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(this->numColumns == rhs.numColumns && this->numRows == rhs.numRows);

  IntMatrix temp(*this);
  for (int i = 0; i < this->numRows; i++) {
    for (int j = 0; j < this->numColumns; j++) {
      temp[i][j] += rhs[i][j];
    }
  }
  return temp;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";
    return s;
  }

  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }

  s << rhs[rhs.getRows() - 1] << " ]";
  return s;
}
