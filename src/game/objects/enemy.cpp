//
// Created by Trần Công Việt An on 18/5/20.
//

#include "enemy.hpp"

#include "const.hpp"
int Enemy::count = 0;
Enemy::Enemy(const Geometry::Point& position, double speed, Color col)
    : GameObject(new BoundingBox::CircleBox(30), position, 5, 0.3 , true), speed(speed), color(col) {}

void Enemy::onCollide(GameObject* otherObject) {
  switch (otherObject->type) {
    case PLAYER_BULLET:
      --Enemy::count;
      // Show score
      destroy();
  }
}
void Enemy::render() {
  Renderer* renderer = Renderer::getInstance();
  renderer->drawCircle(Geometry::Circle(position(), 30), color);
}
