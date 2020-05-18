//
// Created by Trần Công Việt An on 17/5/20.
//

#pragma once


#include "engine/object/object.hpp"

class Wall : public GameObject {
  Geometry::Rectangle rect;

public:
  Wall(const Geometry::Point& position, double width, double height, double angle);

  void render(const Geometry::Point& position) override;
};

class Floor : public Wall {
public:
  Floor(const Geometry::Point& position, double width, double height, double angle);
};
