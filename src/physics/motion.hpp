//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <geometry/geometry.hpp>
namespace Physics {
  class Motion {
  public:
    Motion();
    explicit Motion(double mass);

    Geometry::Vector velocity, acceleration;
    double mass;

    Geometry::Point move(const Geometry::Point &p, double t);
    void setVelocity(const Geometry::Vector &v);
    void setGravity(double g);
  };
}// namespace Physics
