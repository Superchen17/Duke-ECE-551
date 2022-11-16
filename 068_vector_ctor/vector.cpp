#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
/*
void Vector2D::initVector(double init_x, double init_y) {
  this->x = init_x;
  this->y = init_y;
}
*/

double Vector2D::getMagnitude() const {
  return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D result;
  result.x = this->x + rhs.x;
  result.y = this->y + rhs.y;

  return result;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  this->x += rhs.x;
  this->y += rhs.y;

  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return this->x * rhs.x + this->y * rhs.y;
}

void Vector2D::print() const {
  printf("<%.2f, %.2f>", this->x, this->y);
}
