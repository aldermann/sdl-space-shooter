//
// Created by Trần Công Việt An on 17/5/20.
//

#pragma once


#include "engine/object/object.hpp"
#include "engine/render/color.hpp"

class Wall : public GameObject {
  Geometry::Rectangle rect;
  Color col;

public:
  Wall(const Geometry::Point& position, double width, double height, double angle, Color col);

  void render() override;
};

class Floor : public Wall {
public:
  Floor(const Geometry::Point& position, double width, double height, double angle, Color col);
};
