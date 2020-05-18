//
// Created by Trần Công Việt An on 2/5/20.
//

#include "object.hpp"

#include <engine/manager/game.hpp>
#include <iostream>
#include <utility>

GameObject::GameObject() : boundingBox(nullptr), solid(true) {}
GameObject::GameObject(BoundingBox::Box *bounding, Physics::Dynamic dynamic, bool solid)
    : boundingBox(bounding), dynamic(std::move(dynamic)), solid(solid) {}

GameObject::GameObject(BoundingBox::Box *bounding, const Physics::Dynamic &dynamic)
    : GameObject(bounding, dynamic, true) {}

GameObject::~GameObject() {
  delete boundingBox;
}

void GameObject::innerRender(double time) {
  dynamic.advance(time);
  render(position());
  bool debugMode = GameManager::getInstance()->debugMode;
  if (debugMode) {
    boundingBox->render(position());
  }
  if (debugMode) {
    dynamic.render(position());
  }
}

const Geometry::Point &GameObject::position() const {
  return dynamic.position();
}

bool GameObject::checkCollision(GameObject *other) const {
  bool res = boundingBox->checkCollision(position(), other->position(), other->boundingBox);
  return res;
}

void GameObject::handleCollision(GameObject *objectA, GameObject *objectB, double time) {
  Physics::Dynamic &aDyn = objectA->dynamic, &bDyn = objectB->dynamic;
  BoundingBox::Box *aBox = objectA->boundingBox, *bBox = objectB->boundingBox;
  if (objectA->solid and objectB->solid) {
    Physics::Dynamic::handleSolidCollision(aDyn, bDyn, aBox, bBox, time);
  }
}

void GameObject::onKeyDown(SDL_Keycode) {}
void GameObject::onKeyUp(SDL_Keycode key) {}
void GameObject::onCollide(GameObject *otherObject) {}
void GameObject::render(const Geometry::Point &position) {}
