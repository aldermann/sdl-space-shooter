//
// Created by Trần Công Việt An on 5/5/20.
//

#include <cmath>

#include "geometry.hpp"

namespace Geometry {
  Vector::Vector(double x, double y) : x(x), y(y) {}

  Vector::Vector(const Point &a) : x(a.x), y(a.y) {}

  Vector::Vector(const Point &a, const Point &b) : Vector(b.x - a.x, b.y - a.y) {}

  Vector::Vector(const Segment &s) : Vector(s.a, s.b) {}

  Vector::Vector(const Vector &v) : Vector(v.x, v.y) {}

  Vector::Vector() : x(0), y(0) {}

  Vector &Vector::operator=(const Vector &other) = default;

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

  Vector operator*(const double &scale, const Vector &v) {
    return v * scale;
  }

  Vector Vector::operator/(const double &scale) const {
    return {this->x / scale, this->y / scale};
  }

  double Vector::crossProduct(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
  }

  double Vector::operator*(const Vector &other) const {
    return dotProduct(*this, other);
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

  double Vector::dotProduct(const Vector &a, const Vector &b) {
    return a.x * b.x + a.y * b.y;
  }

  double Vector::angle(const Vector &a, const Vector &b) {
    return acos(dotProduct(a, b) / (a.length() * b.length()));
  }

  Vector Vector::projection(const Vector &other) const {
    const Vector otherProjection = other.normalized();
    return (*this) * otherProjection * otherProjection;
  }

  Vector Vector::addLength(const double &r) const {
    double len = length();
    return ((*this) / len) * (len + r);
  }


}// namespace Geometry
