//
// Created by Trần Công Việt An on 2/5/20.
//

#include "display_box.hpp"

#include <iostream>
#include <utility>


namespace DisplayBox {
  Box::Box(Color col) : color(col) {}
  Box::~Box() = default;
  void Box::setColor(const Color &col) {
    this->color = col;
  }

  CircleBox::CircleBox(Geometry::Circle circle, Color color)
      : Box(color), circle(std::move(circle)) {}

  CircleBox::CircleBox(const Geometry::Point &offset, double radius, Color color)
      : Box(color), circle(offset, radius) {}

  CircleBox::CircleBox(double radius, Color color) : Box(color), circle(radius) {}

  void CircleBox::render(const Geometry::Point &position) {
    Renderer *renderer = Renderer::getInstance();
    Geometry::Circle c = circle.translatedBy(Geometry::Vector(position));
    renderer->drawCircle(c, this->color);
  }
  CircleBox::~CircleBox() = default;

  RectangleBox::RectangleBox(const Geometry::Point &offset,
                             double w,
                             double h,
                             double angle,
                             Color color)
      : Box(color), rect(offset, w, h, angle) {}

  RectangleBox::RectangleBox(double w, double h, double angle, Color color)
      : RectangleBox({}, w, h, angle, color) {}


  RectangleBox::RectangleBox(Geometry::Rectangle rectangle, Color color)
      : Box(color), rect(std::move(rectangle)) {}

  void RectangleBox::render(const Geometry::Point &position) {
    Renderer *renderer = Renderer::getInstance();
    Geometry::Rectangle r = rect.translatedBy(Geometry::Vector(position));
    renderer->drawRectangle(r, this->color);
  }

  RectangleBox::~RectangleBox() = default;

}// namespace DisplayBox
