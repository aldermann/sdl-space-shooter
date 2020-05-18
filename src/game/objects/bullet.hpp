//
// Created by Trần Công Việt An on 18/5/20.
//

#pragma once


#include "engine/object/object.hpp"
class Bullet : public GameObject {
  void render(const Geometry::Point& pos) override;
  void onCollide(GameObject* otherObject) override;

public:
  explicit Bullet(const Geometry::Point& pos, const Geometry::Vector& velocity);
};
