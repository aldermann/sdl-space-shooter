//
// Created by Trần Công Việt An on 2/5/20.
//

#include "geometry.hpp"

namespace Geometry {
  // Segment
  Segment::Segment(Point a, Point b) : a(a), b(b) {}

  Segment::Segment(double x1, double y1, double x2, double y2) : a(Point(x1, y1)), b(Point(x2, y2)) {}

  double Segment::length() {
    return a.distance(b);
  }

  // Circle
  Circle::Circle(const double radius) : radius(radius) {}
  Circle::Circle(const Point origin, const double radius) : origin(origin), radius(radius) {}
  Circle Circle::operator+(const Vector &direction) const {
    return Circle(origin + direction, this->radius);
  }
}// namespace Geometry