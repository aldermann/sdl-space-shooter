//
// Created by Trần Công Việt An on 18/5/20.
//

#pragma once


#include "engine/object/object.hpp"
class Bullet : public GameObject {
  void render() override;
  void onCollide(GameObject* otherObject) override;

public:
  Bullet(const Geometry::Point& pos, const Geometry::Vector& velocity);
};

class PlayerBullet : public Bullet {
  PlayerBullet(const Geometry::Point& pos, const Geometry::Vector& velocity);
};

class EnemyBullet : public Bullet {
  EnemyBullet(const Geometry::Point& pos, const Geometry::Vector& velocity);
};
