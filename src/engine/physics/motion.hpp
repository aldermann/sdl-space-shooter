//
// Created by Trần Công Việt An on 17/5/20.
//

#pragma once

#include "engine/geometry/geometry.hpp"

namespace Physics {
  class MotionState {
  public:
    MotionState();
    explicit MotionState(const Geometry::Point &position);
    MotionState(const Geometry::Point &position,
                const Geometry::Vector &velocity);
    MotionState(const Geometry::Point &position,
                const Geometry::Vector &velocity,
                const Geometry::Vector &acceleration);
    Geometry::Point position;
    Geometry::Vector velocity, acceleration;

    [[nodiscard]] MotionState nextState(double t) const;
    [[nodiscard]] MotionState withVelocity(const Geometry::Vector &v) const;
  };

  typedef std::function<bool(MotionState &x, MotionState &y)> CollisionChecker;
  std::pair<MotionState, MotionState> exactCollisionState(const MotionState &a,
                                                          const MotionState &b,
                                                          double time,
                                                          const CollisionChecker &f);
}// namespace Physics
