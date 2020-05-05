//
// Created by Trần Công Việt An on 5/5/20.
//

#include "geometry.hpp"

namespace Geometry {
  Point::Point(double x, double y) : x(x), y(y) {}

  double Point::distance(Segment &other) {
    Point &a = other.a;
    Point &b = other.b;
    return std::abs((b.x - a.x) * this->x - (b.x - a.x) * this->y + a.y * b.x - a.x * b.y) /
           other.length();
  }

  double Point::distance(const Point &other) {
    return Vector(*this, other).length();
  }

  Point Point::operator+(const Vector &direction) const {
    return {this->x + direction.x, this->y + direction.y};
  }

  Point Point::operator-(const Vector &direction) const {
    return *this + (-direction);
  }

  Point::Point() : x(0), y(0) {}

  std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << "Point (" << p.x << "; " << p.y << ")";
  }

}// namespace Geometry
