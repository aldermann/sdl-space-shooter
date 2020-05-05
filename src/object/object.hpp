//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <physics/motion.hpp>

#include "./bounding_box/bounding_box.hpp"
#include "./display_box/display_box.hpp"

class GameObject {
public:
  BoundingBox::Box *boundingBox;
  DisplayBox::Box *displayBox;
  Physics::Motion motion;
  Geometry::Point position;


  GameObject(Geometry::Point position,
             BoundingBox::Box *bounding,
             DisplayBox::Box *display,
             double mass);
  ~GameObject();

public:
  void render(double time);
  static GameObject createRoundObject(Geometry::Point position,
                                      double mass,
                                      double radius,
                                      Color color);
};
