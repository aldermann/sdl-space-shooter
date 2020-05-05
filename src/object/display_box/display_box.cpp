//
// Created by Trần Công Việt An on 2/5/20.
//

#include "display_box.hpp"

namespace DisplayBox {
  Box::Box(Color color) : color(color) {}
  Box::~Box() {}

  CircleBox::CircleBox(Geometry::Circle circle, Color color) : Box(color), circle(circle) {}

  CircleBox::CircleBox(Geometry::Point offset, double radius, Color color) : Box(color), circle(offset, radius) {}

  CircleBox::CircleBox(double radius, Color color) : Box(color), circle(radius) {}

  void CircleBox::render(const Geometry::Point &position) {
    Renderer *renderer = Renderer::getInstance();
    renderer->drawCircle(circle + Geometry::Vector(position), color);
  }
  CircleBox::~CircleBox() {}
}// namespace DisplayBox
