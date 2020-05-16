//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <unordered_set>

#include "./bounding_box/bounding_box.hpp"
#include "./display_box/display_box.hpp"
#include "physics/motion.hpp"

class GameObject {
  /**
 * Render the GameObject
 * @param time The time delta used for physics related function
 * @param renderWireFrame If true, render the wireframe of the object
 * @param renderMotion If true, render movement vector.
 */
public:
  BoundingBox::Box *boundingBox;
  DisplayBox::Box *displayBox;
  Physics::MotionState motion, lastMotion;
  double elasticity;

  GameObject(const Geometry::Point &pos,
             BoundingBox::Box *bounding,
             DisplayBox::Box *display,
             double mass,
             bool immovable,
             double elastic);
  ~GameObject();

  void render(double time, bool renderWireFrame, bool renderMotion);
  bool checkCollision(GameObject *other);
  static void handleBounce(GameObject *a, GameObject *b, double time);

  static GameObject *createRectangleObject(const Geometry::Point &pos,
                                           double w,
                                           double h,
                                           double angle,
                                           double mass,
                                           const Color &color,
                                           double elastic);

  static GameObject *createRoundObject(const Geometry::Point &pos,
                                       double mass,
                                       double radius,
                                       const Color &color,
                                       double elastic);
  static GameObject *createImmovableRectangleObject(const Geometry::Point &pos,
                                                    double w,
                                                    double h,
                                                    double angle,
                                                    const Color &color,
                                                    double elastic);
  static GameObject *createImmovableRoundObject(const Geometry::Point &pos,
                                                double radius,
                                                const Color &color,
                                                double elastic);
  Geometry::Point &position();
  void setMotionState(const Physics::MotionState &m);
};
