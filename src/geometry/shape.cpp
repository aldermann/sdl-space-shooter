//
// Created by Trần Công Việt An on 2/5/20.
//

#include <iostream>
#include "geometry.hpp"
#include "utils/error/error.hpp"
#include "utils/number/number.hpp"
#include "utils/utils.hpp"

namespace Geometry {
  // Segment
  Segment::Segment(const Point& a, const Point& b) : a(a), b(b) {}

  Segment::Segment(double x1, double y1, double x2, double y2) : a(x1, y1), b(x2, y2) {}

  double Segment::length() {
    return a.distance(b);
  }


  Shape::Shape(const Point& center) : center(center) {}
  Shape::Shape() : center(0, 0) {}

  // Circle
  Circle::Circle(const double radius) : Shape(), radius(radius) {}
  Circle::Circle(const Point& center, const double radius) : Shape(center), radius(radius) {}
  Circle Circle::translatedBy(const Vector& direction) const {
    return {center + direction, this->radius};
  }

  Rectangle::Rectangle(const Point& center, const Vector& _w, const Vector& _h) : Shape(center) {
    if (!doubleEqual(_w * _h, 0.0)) {
      char message[100];
      sprintf(message, "For a rectangle, w and h must be perpendicular. Dot product: %f", _w * _h);
      throw WarningAppError(message);
    }
    h = _h;
    w = _w;
  }

  Rectangle::Rectangle(const Point& center, const double w, const double h, const double angle) {
    if (w == 0 or h == 0) {
      throw FatalAppError("Width or height must be more than 0");
    }
    this->center = center;
    this->w = Vector(w / 2 * cos(angle), w / 2 * sin(angle));
    this->h = this->w.normalized().perpendicular() * h / 2;
  }

  Rectangle::Rectangle(const Vector& w, const Vector& h) : Rectangle({}, w, h) {}

  Rectangle Rectangle::translatedBy(const Vector& direction) const {
    return {center + direction, w, h};
  }

  bool Rectangle::contain(const Point& p) const {
    typedef Number::FloatInterval dInterval;
    Point pInLocalSpace = p.relativeTo(center);
    double wProj = pInLocalSpace.projectionValue(w), hProj = pInLocalSpace.projectionValue(h);
    double wLen = w.length(), hLen = h.length();
    return dInterval(-wLen, wLen).contain(wProj) && dInterval(-hLen, hLen).contain(hProj);
  }


  std::vector<Point> Rectangle::getCorners() const {
    std::vector<Point> res;
    res.push_back(center - h + w);
    res.push_back(center - h - w);
    res.push_back(center + h - w);
    res.push_back(center + h + w);
    return res;
  }

}// namespace Geometry