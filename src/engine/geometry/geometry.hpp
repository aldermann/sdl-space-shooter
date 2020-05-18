//
// Created by Trần Công Việt An on 17/5/20.
//

#pragma once

#include <ostream>
#include <vector>

namespace Geometry {
  class Point;
  class Vector;
  class Shape;
  class Segment;
  class Rectangle;
  class Circle;


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
    [[nodiscard]] Point relativeTo(const Point &other) const;
    [[nodiscard]] Point withOrigin(const Point &other) const;
    [[nodiscard]] double projectionValue(const Vector &vector) const;
    [[nodiscard]] Point projection(const Segment &segment) const;
  };

  class Vector {
  public:
    double x{}, y{};

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

    [[nodiscard]] double length() const;
    [[nodiscard]] Vector perpendicular() const;
    [[nodiscard]] Vector projection(const Vector &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    [[nodiscard]] Vector normalized() const;
    [[nodiscard]] Vector addLength(const double &r) const;
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
    [[nodiscard]] Circle translatedBy(const Vector &direction) const;
  };

  class Rectangle : public Shape {
  public:
    Rectangle(const Point &center, double w, double h, double angle);
    Vector w, h;
    Rectangle(const Point &center, const Vector &w, const Vector &h);
    explicit Rectangle(const Vector &w, const Vector &h);
    [[nodiscard]] Rectangle translatedBy(const Vector &direction) const;
    [[nodiscard]] bool contain(const Point &p) const;
    [[nodiscard]] std::vector<Point> getCorners() const;
  };
}// namespace Geometry
