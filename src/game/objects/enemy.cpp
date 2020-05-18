//
// Created by Trần Công Việt An on 18/5/20.
//

#include "enemy.hpp"
Enemy::Enemy(const Geometry::Point& position, double speed, Color col)
    : GameObject(new BoundingBox::CircleBox(30), position, 5, 1, true), speed(speed),
      color(col) {}