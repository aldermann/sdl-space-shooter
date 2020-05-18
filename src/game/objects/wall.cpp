//
// Created by Trần Công Việt An on 17/5/20.
//

#include "wall.hpp"

#include "const.hpp"

Wall::Wall(const Geometry::Point& position, double width, double height, double angle)
    : rect(position, width, height, angle) {
  boundingBox = new BoundingBox::RectangleBox(width, height, angle);
  type = WALL;
  dynamic = {position, false};
}

void Wall::render(const Geometry::Point& position) {
  Renderer::getInstance()->drawRectangle(rect, Palette::get()->Blue);
}

Floor::Floor(const Geometry::Point& position, double width, double height, double angle)
    : Wall(position, width, height, angle) {
  type = FLOOR;
}
