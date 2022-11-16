#include "circle.hpp"

#include <cmath>

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = this->center.distanceFrom(otherCircle.center);
  double r1 = this->radius;
  double r2 = otherCircle.radius;

  if (d >= r1 + r2) {
    return 0;
  }

  if (d <= std::abs(r1 - r2)) {
    double r_small = r1 < r2 ? r1 : r2;
    return M_PI * r_small * r_small;
  }

  double ang_beta = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
  double ang_alpha = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));

  double area = ang_alpha * r1 * r1 + ang_beta * r2 * r2 - r1 * d * sin(ang_alpha);
  return area;
}
