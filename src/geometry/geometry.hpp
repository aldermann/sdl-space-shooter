//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once
#include <cmath>
#include <ostream>

namespace Geometry {
  class Point;

  class Vector {
  public:
    double x, y;
    explicit Vector(Point a);
    Vector();
    Vector(double, double);
    Vector(Point a, Point b);
    Vector operator+(const Vector &other) const;
    Vector operator-() const;
    Vector operator-(const Vector &other) const;
    Vector operator*(const double &scale) const;
    Vector operator/(const double &scale) const;
    double operator*(const Vector &other) const;
    double X(const Vector &other) const;
    double length() const;
    Vector perpendicular() const;
    friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    Vector normalized() const;
  };

  class Segment;
  class Point {
  public:
    double x, y;
    Point(double x, double y);
    Point();
    double distance(const Point &other);
    double distance(Segment &seg);
    friend std::ostream &operator<<(std::ostream &os, const Point &p);

    Point operator+(const Vector &direction) const;
    Point operator-(const Vector &direction) const;
  };

  class Segment {
  public:
    Point a, b;
    Segment(Point a, Point b);
    Segment(double x1, double y1, double x2, double y2);
    double length();
  };

  class Shape {};

  class Circle : public Shape {
  public:
    Point origin;
    double radius;
    Circle(const Point origin, const double radius);
    Circle(const double radius);
    Circle operator+(const Vector &direction) const;
  };
}// namespace Geometry
