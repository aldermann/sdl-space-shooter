//
// Created by Trần Công Việt An on 5/5/20.
//
#include <iostream>

#include "bounding_box.hpp"

namespace BoundingBox {
  CircleBox::~CircleBox() = default;

  CircleBox::CircleBox(const Geometry::Point &offset, double radius) : circle(offset, radius) {}

  CircleBox::CircleBox(double radius) : circle(radius) {}

  Shape CircleBox::getShape() {
    return Circle;
  }

  bool CircleBox::checkCollisionCirc(const Geometry::Point &position,
                                     const Geometry::Point &otherPosition,
                                     CircleBox *otherBox) {
    Geometry::Circle thisCircle = circle.translatedBy(Geometry::Vector(position));
    Geometry::Circle otherCircle = otherBox->circle.translatedBy(Geometry::Vector(otherPosition));
    double dist = thisCircle.center.distance(otherCircle.center);
    return dist <= thisCircle.radius + otherCircle.radius;
  }


  bool CircleBox::checkCollisionRect(const Geometry::Point &position,
                                     const Geometry::Point &otherPosition,
                                     RectangleBox *other) {
    return other->checkCollisionCirc(otherPosition, position, this);
  }

  Geometry::Vector CircleBox::normalCollisionVectorRect(const Geometry::Point &pos,
                                                        const Geometry::Point &otherPos,
                                                        RectangleBox *otherBox) {
    return otherBox->normalCollisionVector(otherPos, pos, this);
  }
  Geometry::Vector CircleBox::normalCollisionVectorCirc(const Geometry::Point &pos,
                                                        const Geometry::Point &otherPos,
                                                        CircleBox *other) {
    return -Geometry::Vector(pos.withOrigin(circle.center),
                             otherPos.withOrigin(other->circle.center))
                    .normalized();
  }
  void CircleBox::render(Geometry::Point &position) {
    Renderer *renderer = Renderer::getInstance();
    renderer->drawCircleBorder(circle.translatedBy(Geometry::Vector(position)),
                               Palette::get()->Green);
  }


}// namespace BoundingBox
