//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <physics/motion.hpp>
#include <unordered_set>

#include "./bounding_box/bounding_box.hpp"
#include "./display_box/display_box.hpp"

class GameObject {
public:
  BoundingBox::Box *boundingBox;
  DisplayBox::Box *displayBox;
  Physics::MotionState motion;

  GameObject(const Geometry::Point &pos,
             BoundingBox::Box *bounding,
             DisplayBox::Box *display,
             double mass,
             bool immovable);
  ~GameObject();

public:
  /**
   * Render the GameObject
   * @param time The time delta used for physics related function
   * @param renderWireFrame If true, render the wireframe of the object
   * @param renderMotion If true, render movement vector.
   */
  void render(double time, bool renderWireFrame, bool renderMotion);
  bool checkCollision(GameObject *other);
  static void handleCollision(GameObject *a, GameObject *b);
  static GameObject *createRectangleObject(const Geometry::Point &pos,
                                          double w,
                                          double h,
                                          double angle,
                                          double mass,
                                          const Color &color);

  static GameObject *createRoundObject(const Geometry::Point &pos,
                                      double mass,
                                      double radius,
                                      const Color &color);
  static GameObject *createImmovableRectangleObject(const Geometry::Point &pos,
                                                   double w,
                                                   double h,
                                                   double angle,
                                                   const Color &color);
  static GameObject *createImmovableRoundObject(const Geometry::Point &pos,
                                               double radius,
                                               const Color &color);
  Geometry::Point &position();
};
