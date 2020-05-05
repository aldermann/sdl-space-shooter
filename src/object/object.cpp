//
// Created by Trần Công Việt An on 2/5/20.
//

#include "object.hpp"
#include <iostream>

GameObject::GameObject(Geometry::Point position, BoundingBox::Box *bounding, DisplayBox::Box *display, double mass)
    : boundingBox(bounding), displayBox(display), motion(mass), position(position) {}


void GameObject::render(double time) {
  position = motion.move(position, time);
  displayBox->render(position);
}

GameObject GameObject::createRoundObject(Geometry::Point position, double mass, double radius, Color color) {
  auto *bndBox = new BoundingBox::CircleBox(radius);
  auto *dspBox = new DisplayBox::CircleBox(radius, color);
  return GameObject(position, bndBox, dspBox, mass);
}

GameObject::~GameObject() {
  delete displayBox;
  delete boundingBox;
}
