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
    double mass;
    bool immovable;

    void move(double t);
    void setVelocity(const Geometry::Vector &v);
    void setGravity(double g);
    Geometry::Vector calculateCollision(MotionState &other,
                                               const Geometry::Vector &normalVec) const;
    void render(const Geometry::Point &p) const;
    void setDrag(const float &coefficient);
  };


}// namespace Physics
