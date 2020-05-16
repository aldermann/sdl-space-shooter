//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once
#include <cmath>
#include <ostream>
#include <vector>

namespace Geometry {
  class Segment;
  class Vector;
  class Point {
  public:
    double x{}, y{};
    Point(double x, double y);
    Point();
    Point(const Point &p);
    Point &operator=(const Point &);
    double distance(const Point &other);
    double distance(Segment &seg) const;
    friend std::ostream &operator<<(std::ostream &os, const Point &p);

    Point operator+(const Vector &direction) const;
    Point operator-(const Vector &direction) const;
    Point relativeTo(const Point &other) const;
    Point withOrigin(const Point &other) const;
    double projectionValue(const Vector &vector) const;
    Point projection(const Segment &segment) const;
  };

  class Vector {
  public:
    double x, y;

    Vector(const Vector &v);
    explicit Vector(const Point &a);
    explicit Vector(const Segment &s);
    Vector();
    Vector(double, double);
    Vector(const Point &a, const Point &b);

    Vector &operator=(const Vector &other);
    Vector operator+(const Vector &other) const;
    Vector operator-() const;
    Vector operator-(const Vector &other) const;
    Vector operator*(const double &scale) const;
    friend Vector operator*(const double &scale, const Vector &v);
    Vector operator/(const double &scale) const;
    double operator*(const Vector &other) const;
    static double dotProduct(const Vector &a, const Vector &b);
    static double crossProduct(const Vector &a, const Vector &b);

    double length() const;
    Vector perpendicular() const;
    Vector projection(const Vector &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    Vector normalized() const;
    Vector addLength(const double &r) const;
  };

  class Segment {
  public:
    Point a, b;
    Segment(const Point &a, const Point &b);
    Segment(double x1, double y1, double x2, double y2);
    double length();
  };

  class Shape {
  public:
    Point center;
    explicit Shape(const Point &center);
    Shape();
  };

  class Circle : public Shape {
  public:
    double radius;
    Circle(const Point &center, double radius);
    explicit Circle(double radius);
    Circle translatedBy(const Vector &direction) const;
  };

  class Rectangle : public Shape {
  public:
    Rectangle(const Point &center, double w, double h, double angle);
    Vector w, h;
    Rectangle(const Point &center, const Vector &w, const Vector &h);
    explicit Rectangle(const Vector &w, const Vector &h);
    Rectangle translatedBy(const Vector &direction) const;
    bool contain(const Point &p) const;
    std::vector<Point> getCorners() const;
  };

}// namespace Geometry
