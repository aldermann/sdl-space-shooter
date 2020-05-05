//
// Created by Trần Công Việt An on 5/5/20.
//

#include "geometry.hpp"

namespace Geometry {
  Vector::Vector(double x, double y) : x(x), y(y) {}

  Vector::Vector(Point a) : x(a.x), y(a.y) {}

  Vector::Vector(Point a, Point b) : Vector(b.x - a.x, b.y - a.y) {}

  Vector::Vector() : x(0), y(0) {}


  Vector Vector::operator-() const {
    return {-x, -y};
  }

  Vector Vector::operator+(const Vector &other) const {
    return {this->x + other.x, this->y + other.y};
  }

  Vector Vector::operator-(const Vector &other) const {
    return *this + (-other);
  }

  Vector Vector::operator*(const double &scale) const {
    return {this->x * scale, this->y * scale};
  }

  Vector Vector::operator/(const double &scale) const {
    return {this->x / scale, this->y / scale};
  }

  double Vector::X(const Vector &other) const {
    return this->x * other.y - this->y * other.x;
  }

  double Vector::operator*(const Vector &other) const {
    return this->x * other.x + this->y * other.y;
  }

  Vector Vector::perpendicular() const {
    return {this->y, -this->x};
  }

  double Vector::length() const {
    return sqrt(x * x + y * y);
  }

  std::ostream &operator<<(std::ostream &os, const Vector &v) {
    return os << "Vector (" << v.x << "; " << v.y << ")";
  }

  Vector Vector::normalized() const {
    return *this / this->length();
  }
}// namespace Geometry
