//
// Created by Trần Công Việt An on 5/5/20.
//

#include <cmath>

#include "geometry.hpp"

namespace Geometry {
  Point::Point(double x, double y) : x(x), y(y) {}

  Point::Point() : Point(0, 0) {}

  Point::Point(const Point &other) = default;

  Point &Point::operator=(const Point &other) = default;

  double Point::distance(Segment &other) const {
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

  std::ostream &operator<<(std::ostream &os, const Point &p) {
    return os << "Point (" << p.x << "; " << p.y << ")";
  }

  Point Point::withOrigin(const Point &other) const {
    return *this + Vector(other);
  }

  Point Point::relativeTo(const Point &other) const {
    return *this - Vector(other);
  }

  double Point::projectionValue(const Vector &vector) const {
    return Vector(*this) * vector.normalized();
  }

  Point Point::projection(const Segment &s) const {
    Vector v1(s.a, *this);
    Vector vs(s);
    Vector vProj = v1.projection(vs);
    return s.a + vProj;
  }


}// namespace Geometry
