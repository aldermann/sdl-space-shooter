//
// Created by Trần Công Việt An on 2/5/20.
//

#include "motion.hpp"

#include <iostream>

#include "dynamic.hpp"
#include "engine/render/renderer.hpp"


namespace Physics {
  MotionState::MotionState() = default;
  MotionState::MotionState(const Geometry::Point &position) : position(position) {}
  MotionState::MotionState(const Geometry::Point &position,
                           const Geometry::Vector &velocity,
                           const Geometry::Vector &acceleration)
      : position(position), velocity(velocity), acceleration(acceleration) {}
  MotionState::MotionState(const Geometry::Point &position, const Geometry::Vector &velocity): position(position), velocity(velocity) {}

  MotionState MotionState::nextState(double t) const {
    MotionState newState = *this;
    newState.position = position + velocity * t + acceleration * t * t * 0.5f;
    newState.velocity = velocity + acceleration * t;
    if (abs(newState.velocity.x) < 1e-2) {
      newState.velocity.x = 0;
    }
    if (abs(newState.velocity.y) < 1e-2) {
      newState.velocity.y = 0;
    }
    return newState;
  }

  MotionState MotionState::withVelocity(const Geometry::Vector &v) const {
    MotionState newState = *this;
    newState.velocity = v;
    return newState;
  }

  std::pair<MotionState, MotionState> exactCollisionState(const MotionState &a,
                                                          const MotionState &b,
                                                          double time,
                                                          const CollisionChecker &f) {
    double lower = 0, upper = time;
    while (true) {
      double mid = (upper + lower) / 2;
      Physics::MotionState aNext = a.nextState(mid);
      Physics::MotionState bNext = b.nextState(mid);
      if (f(aNext, bNext)) {
        upper = mid;
      } else {
        lower = mid;
      }
      if (upper - lower < 1e-3) {
        break;
      }
    }
    return std::make_pair(a.nextState(lower), b.nextState(lower));
  }
}// namespace Physics
