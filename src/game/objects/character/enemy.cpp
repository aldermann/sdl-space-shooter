//
// Created by Trần Công Việt An on 18/5/20.
//

#include "enemy.hpp"

#include "bullet.hpp"
#include "const.hpp"
#include "engine/manager/game.hpp"

int Enemy::count = 0;
Enemy::Enemy(const Geometry::Point& position, double speed, Color col)
    : GameObject(new BoundingBox::CircleBox(30), position, 5, 0.3, true), speed(speed), color(col) {
  dynamic.setHorizontalVelocity(-speed);
}

void Enemy::onCollide(GameObject* otherObject) {
  switch (otherObject->type) {
    case PLAYER_BULLET:
      --Enemy::count;
      // Show score
      destroy();
  }
}
void Enemy::shoot() {
  GameManager::registerObject(
          new EnemyBullet(position() + Geometry::Vector(-40, 0), Geometry::Vector(-1000, 0)));
}

void Enemy::render() {
  int time = (int) SDL_GetTicks();
  if (lastShoot + 1000 <= time) {
    lastShoot = time;
    shoot();
  }
  Renderer* renderer = Renderer::getInstance();
  renderer->drawCircle(Geometry::Circle(position(), 30), color);
}
