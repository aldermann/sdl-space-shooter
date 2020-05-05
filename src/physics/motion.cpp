//
// Created by Trần Công Việt An on 2/5/20.
//

#include "motion.hpp"

#include <iostream>

namespace Physics {
  Motion::Motion() : mass(1) {}
  Motion::Motion(double mass) : mass(mass) {}

  Geometry::Point Motion::move(const Geometry::Point &p, double t) {
    Geometry::Point res = p + velocity * t + acceleration * t * t * 0.5f;
    velocity = velocity + acceleration * t;
    return res;
  }

  void Motion::setGravity(double g) {
    acceleration = acceleration + Geometry::Vector(0, g);
  }

  void Motion::setVelocity(const Geometry::Vector &v) {
    velocity = v;
  }
}// namespace Physics
