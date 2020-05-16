//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once
#include "geometry/geometry.hpp"
namespace Physics {
  class MotionState {
  public:
    MotionState();
    explicit MotionState(const Geometry::Point &position, double mass, bool immovable);

    Geometry::Point position;
    Geometry::Vector velocity, acceleration;
    double mass, g, drag;
    bool immovable;

    MotionState nextState(double t) const;
    void setVelocity(const Geometry::Vector &v);
    void setGravity(double g);
    Geometry::Vector velocityAfterCollision(MotionState &other,
                                            const Geometry::Vector &normalVec) const;
    void render(const Geometry::Point &p) const;
    void setDrag(const float &coefficient);

    typedef std::function<bool(MotionState &x, MotionState &y)> collisionPredicate;
  };
  std::pair<MotionState, MotionState> exactCollisionPosition(MotionState &a,
                                                              MotionState &b,
                                                              double time,
                                                              const MotionState::collisionPredicate& f);

}// namespace Physics
