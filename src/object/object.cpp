//
// Created by Trần Công Việt An on 2/5/20.
//

#include "object.hpp"

#include <iostream>

GameObject::GameObject(const Geometry::Point &pos,
                       BoundingBox::Box *bounding,
                       DisplayBox::Box *display,
                       double mass,
                       bool immovable)
    : boundingBox(bounding), displayBox(display), motion(pos, mass, immovable) {}

GameObject::~GameObject() {
  delete displayBox;
  delete boundingBox;
}


void GameObject::render(double time, bool renderWireFrame, bool renderMotion) {
  motion.move(time);
  displayBox->render(this->position());
  if (renderWireFrame) {
    boundingBox->render(this->position());
  }
  if (renderMotion) {
    motion.render(this->position());
  }
}

GameObject *GameObject::createRoundObject(const Geometry::Point &pos,
                                          double mass,
                                          double radius,
                                          const Color &color) {
  auto *bndBox = new BoundingBox::CircleBox(radius);
  auto *dspBox = new DisplayBox::CircleBox(radius, color);
  return new GameObject(pos, bndBox, dspBox, mass, false);
}

GameObject *GameObject::createImmovableRoundObject(const Geometry::Point &pos,
                                                   double radius,
                                                   const Color &color) {
  auto *bndBox = new BoundingBox::CircleBox(radius);
  auto *dspBox = new DisplayBox::CircleBox(radius, color);
  return new GameObject(pos, bndBox, dspBox, 1e9, true);
}

GameObject *GameObject::createRectangleObject(const Geometry::Point &pos,
                                              double w,
                                              double h,
                                              double angle,
                                              double mass,
                                              const Color &color) {
  auto *bndBox = new BoundingBox::RectangleBox({0, 0}, w, h, angle);
  auto *dspBox = new DisplayBox::RectangleBox(w, h, angle, color);
  return new GameObject(pos, bndBox, dspBox, mass, false);
}

GameObject *GameObject::createImmovableRectangleObject(const Geometry::Point &pos,
                                                       double w,
                                                       double h,
                                                       double angle,
                                                       const Color &color) {

  Geometry::Point offset(0, 0);
  auto *bndBox = new BoundingBox::RectangleBox(offset, w, h, angle);
  auto *dspBox = new DisplayBox::RectangleBox(w, h, angle, color);
  return new GameObject(pos, bndBox, dspBox, 1e9, true);
}

bool GameObject::checkCollision(GameObject *other) {
  bool res = boundingBox->checkCollision(this->position(), other->position(), other->boundingBox);
  return res;
}
void GameObject::handleCollision(GameObject *a, GameObject *b) {
  Geometry::Vector normalVec =
          a->boundingBox->normalCollisionVector(a->position(), b->position(), b->boundingBox);
  Geometry::Vector newVelocityA = a->motion.calculateCollision(b->motion, normalVec);
  Geometry::Vector newVelocityB = b->motion.calculateCollision(a->motion, -normalVec);
  a->motion.setVelocity(newVelocityA);
  b->motion.setVelocity(newVelocityB);
}

Geometry::Point &GameObject::position() {
  return motion.position;
}
