//
// Created by Trần Công Việt An on 2/5/20.
//

#include "bounding_box.hpp"

#include <iostream>

namespace BoundingBox {
  // Box
  Box::~Box() = default;

  // CircleBox
  CircleBox::~CircleBox() = default;

  CircleBox::CircleBox(Geometry::Point offset, double radius) : circle(offset, radius) {}

  CircleBox::CircleBox(double radius) : circle(radius) {}

  bool CircleBox::checkCollision(Geometry::Point &position,
                                 Geometry::Point &otherPosition,
                                 CircleBox &otherBox) {
    Geometry::Circle thisCircle = circle + Geometry::Vector(position);
    Geometry::Circle otherCircle = otherBox.circle + Geometry::Vector(otherPosition);
    double dist = thisCircle.origin.distance(otherCircle.origin);
    return dist <= thisCircle.radius + otherCircle.radius;
  }

  void CircleBox::print() {
    std::cout << "Circle radius " << circle.radius << "; Circle origin " << circle.origin.x << " ; "
              << circle.origin.y << "\n";
  }

  Shape CircleBox::getShape() {
    return Circle;
  }

  bool CircleBox::checkCollision(Geometry::Point &position,
                                 Geometry::Point &otherPosition,
                                 RectangleBox &other) {
    return false;
  }
  Geometry::Vector CircleBox::normalCollisionVector(RectangleBox &other) {
    return {};
  }
  Geometry::Vector CircleBox::normalCollisionVector(CircleBox &other) {
    return Geometry::Vector(this->circle.origin, other.circle.origin).normalized();
  }


}// namespace BoundingBox
