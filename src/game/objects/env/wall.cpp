//
// Created by Trần Công Việt An on 17/5/20.
//

#include "wall.hpp"

#include <iostream>

#include "game/objects/character/const.hpp"

Wall::Wall(const Geometry::Point& position, double width, double height, double angle, Color col)
    : rect(position, width, height, angle), col(col) {
  boundingBox = new BoundingBox::RectangleBox(width, height, angle);
  type = WALL;
  dynamic = {position, false};
}

void Wall::render() {
  Renderer::getInstance()->drawRectangle(rect, col);
}

Floor::Floor(const Geometry::Point& position, double width, double height, double angle, Color col)
    : Wall(position, width, height, angle, col) {
  type = FLOOR;
}
