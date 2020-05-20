//
// Created by Trần Công Việt An on 18/5/20.
//

#include "bullet.hpp"

#include "const.hpp"
Bullet::Bullet(const Geometry::Point& pos, const Geometry::Vector& velocity) : GameObject() {
  boundingBox = new BoundingBox::CircleBox(5);
  dynamic = {Physics::MotionState(pos, velocity), 1, 1};
}

void Bullet::render() {
  Geometry::Circle circ(position(), 5);
  Renderer::getInstance()->drawCircle(circ, Palette::get()->Red);
}

void Bullet::onCollide(GameObject* otherObject) {
  destroy();
}

PlayerBullet::PlayerBullet(const Geometry::Point& pos, const Geometry::Vector& velocity)
    : Bullet(pos, velocity) {
  type = PLAYER_BULLET;
}

EnemyBullet::EnemyBullet(const Geometry::Point& pos, const Geometry::Vector& velocity)
        : Bullet(pos, velocity) {
  type = ENEMY_BULLET;
}
