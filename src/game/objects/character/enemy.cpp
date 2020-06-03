//
// Created by Trần Công Việt An on 18/5/20.
//

#include "enemy.hpp"

#include <engine/manager/game.hpp>
#include <utils/random.hpp>
#include <utils/utils.hpp>

#include "bullet.hpp"
#include "const.hpp"
int Enemy::count = 0;
Enemy::Enemy(const Geometry::Point& position, double speed, Color col)
    : GameObject(new BoundingBox::CircleBox(30), position, 5, 0.3, false), speed(speed),
      color(col) {
  dynamic.setHorizontalVelocity(-speed);
  dynamic.setVerticalVelocity(Random::randDouble(-speed, speed));
}

void Enemy::onCollide(GameObject* otherObject) {
  switch (otherObject->type) {
    case PLAYER_BULLET:
      --Enemy::count;
      // Show score
      destroy();
  }
}

void Enemy::tick(double time) {
  reloadTime -= time;
  changeDirectionTime -= time;
  if (reloadTime <= 0) {
    reloadTime = 1;
    GameManager::registerObject(
            new EnemyBullet(position() + Geometry::Vector(-40, 0), Geometry::Vector(-1000, 0)));
  }
  if (changeDirectionTime <= 0) {
    changeDirectionTime = 3;
    double newVSign = -signum(dynamic.velocity().y);
    double newV = Random::randDouble(newVSign * 50, newVSign * 100);
    dynamic.setVerticalVelocity(newV);
  }
}
void Enemy::render() {
  Renderer* renderer = Renderer::getInstance();
  renderer->drawCircle(Geometry::Circle(position(), 30), color);
}
