//
// Created by Trần Công Việt An on 2/5/20.
//

#include "object.hpp"

#include <iostream>

GameObject::GameObject(const Geometry::Point &pos,
                       BoundingBox::Box *bounding,
                       DisplayBox::Box *display,
                       double mass,
                       bool immovable,
                       double elastic)
    : boundingBox(bounding), displayBox(display), motion(pos, mass, immovable),
      elasticity(std::max(0.0, std::min(elastic, 1.0))) {}

GameObject::~GameObject() {
  delete displayBox;
  delete boundingBox;
}

void GameObject::render(double time, bool renderWireFrame, bool renderMotion) {
  setMotionState(motion.nextState(time));
  displayBox->render(this->position());
  if (renderWireFrame) {
    boundingBox->render(this->position());
  }
  if (renderMotion) {
    motion.render(this->position());
  }
}

bool GameObject::checkCollision(GameObject *other) {
  bool res = boundingBox->checkCollision(this->position(), other->position(), other->boundingBox);
  return res;
}

void GameObject::handleBounce(GameObject *a, GameObject *b, double time) {
  auto collisionChecker = [a, b](Physics::MotionState aState, Physics::MotionState bState) {
    return a->boundingBox->checkCollision(aState.position, bState.position, b->boundingBox);
  };
  auto motions =
          Physics::exactCollisionPosition(a->lastMotion, b->lastMotion, time, collisionChecker);
  Physics::MotionState &aMotion = motions.first, &bMotion = motions.second;
  Geometry::Vector normalVec =
          a->boundingBox->normalCollisionVector(aMotion.position, bMotion.position, b->boundingBox);
  Geometry::Vector newVelocityA = aMotion.velocityAfterCollision(bMotion, normalVec);
  Geometry::Vector newVelocityB = bMotion.velocityAfterCollision(aMotion, -normalVec);
  aMotion.setVelocity(newVelocityA * a->elasticity);
  bMotion.setVelocity(newVelocityB * b->elasticity);
  a->setMotionState(aMotion);
  b->setMotionState(bMotion);
}

Geometry::Point &GameObject::position() {
  return motion.position;
}

void GameObject::setMotionState(const Physics::MotionState &m) {
  lastMotion = motion;
  motion = m;
}
