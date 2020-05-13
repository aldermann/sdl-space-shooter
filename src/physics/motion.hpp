//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include "geometry/geometry.hpp"
namespace Physics {
  class Motion {
  public:
    Motion();
    explicit Motion(double mass, bool immovable);

    Geometry::Vector velocity, acceleration;
    double mass;
    bool immovable;

    Geometry::Point move(const Geometry::Point &p, double t);
    void setVelocity(const Geometry::Vector &v);
    void setGravity(double g);
    Geometry::Vector calculateElasticCollision(Motion &other, const Geometry::Vector &normalVec) const;
    void render(const Geometry::Point &p);
  };
}// namespace Physics
