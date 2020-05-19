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

GameObject::GameObject(BoundingBox::Box *bounding,
                       const Geometry::Point &position,
                       double mass,
                       double elasticity,
                       bool solid)
    : boundingBox(bounding), dynamic(position, mass, elasticity), solid(solid) {}

GameObject::GameObject(BoundingBox::Box *bounding, const Physics::Dynamic &dynamic)
    : GameObject(bounding, dynamic, true) {}

GameObject::~GameObject() {
  delete boundingBox;
}

void GameObject::innerRender() {
  render();
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

void GameObject::handleCollision(GameObject *objectA, GameObject *objectB, double time) {
  Physics::Dynamic &aDyn = objectA->dynamic, &bDyn = objectB->dynamic;
  BoundingBox::Box *aBox = objectA->boundingBox, *bBox = objectB->boundingBox;
  if (!aBox->checkCollision(aDyn.position(), bDyn.position(), bBox)) {
    return;
  }
  Geometry::Vector normalVec =
          aBox->normalCollisionVector(aDyn.position(), bDyn.position(), bBox);
  objectA->onCollide(objectB);
  objectB->onCollide(objectA);
  if (objectA->solid and objectB->solid) {
    Physics::Dynamic::handleSolidCollision(aDyn, bDyn, aBox, bBox, normalVec, time);
  }
}

void GameObject::onKeyDown(SDL_Keycode) {}
void GameObject::onKeyUp(SDL_Keycode key) {}
void GameObject::mouseDown(int posx, int posy) {}
void GameObject::onCollide(GameObject *otherObject) {}
void GameObject::render() {}
void GameObject::destroy() {
  /**
   * Call this method to destroy the object.
   * DON'T touch the object after calling destroy, or you will get fucked.
   */
  GameManager::deleteObject(this);
}
