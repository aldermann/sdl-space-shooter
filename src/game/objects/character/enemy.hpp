//
// Created by Trần Công Việt An on 18/5/20.
//

#pragma once


#include "engine/object/object.hpp"

class Enemy : public GameObject {
public:
  static int count;
  double speed;
  double reloadTime = 1, changeDirectionTime = 3;
  Color color;
  Enemy(const Geometry::Point& position, double speed, Color col);
  void onCollide(GameObject* otherObject) override;
  void render() override;
  void tick(double time) override;
};
