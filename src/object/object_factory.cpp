//
// Created by Trần Công Việt An on 16/5/20.
//
#include "object.hpp"

GameObject *GameObject::createRoundObject(const Geometry::Point &pos,
                                          double mass,
                                          double radius,
                                          const Color &color,
                                          double elastic) {
  auto *bndBox = new BoundingBox::CircleBox(radius);
  auto *dspBox = new DisplayBox::CircleBox(radius, color);
  return new GameObject(pos, bndBox, dspBox, mass, false, elastic);
}

GameObject *GameObject::createImmovableRoundObject(const Geometry::Point &pos,
                                                   double radius,
                                                   const Color &color,
                                                   double elastic) {
  auto *bndBox = new BoundingBox::CircleBox(radius);
  auto *dspBox = new DisplayBox::CircleBox(radius, color);
  return new GameObject(pos, bndBox, dspBox, 1e9, true, elastic);
}

GameObject *GameObject::createRectangleObject(const Geometry::Point &pos,
                                              double w,
                                              double h,
                                              double angle,
                                              double mass,
                                              const Color &color,
                                              double elastic) {
  auto *bndBox = new BoundingBox::RectangleBox({0, 0}, w, h, angle);
  auto *dspBox = new DisplayBox::RectangleBox(w, h, angle, color);
  return new GameObject(pos, bndBox, dspBox, mass, false, elastic);
}

GameObject *GameObject::createImmovableRectangleObject(const Geometry::Point &pos,
                                                       double w,
                                                       double h,
                                                       double angle,
                                                       const Color &color,
                                                       double elastic) {

  Geometry::Point offset(0, 0);
  auto *bndBox = new BoundingBox::RectangleBox(offset, w, h, angle);
  auto *dspBox = new DisplayBox::RectangleBox(w, h, angle, color);
  return new GameObject(pos, bndBox, dspBox, 1e9, true, elastic);
}