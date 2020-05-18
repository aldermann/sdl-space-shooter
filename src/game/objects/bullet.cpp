//
// Created by Trần Công Việt An on 18/5/20.
//

#include "bullet.hpp"
Bullet::Bullet(const Geometry::Point& pos, const Geometry::Vector& velocity) : GameObject() {
  boundingBox = new BoundingBox::CircleBox(5);
  dynamic = {Physics::MotionState(pos, velocity), 1, 1};
}

void Bullet::render(const Geometry::Point& pos) {
  Renderer::getInstance()->drawCircle(Geometry::Circle(pos, 5), Palette::get()->Red);
}

void Bullet::onCollide(GameObject* otherObject) {
  destroy();
}
