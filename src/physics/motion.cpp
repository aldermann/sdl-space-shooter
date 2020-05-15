//
// Created by Trần Công Việt An on 2/5/20.
//

#include "motion.hpp"

#include <iostream>
#include <render/renderer.hpp>

namespace Physics {
  MotionState::MotionState() : mass(1), immovable(false) {}
  MotionState::MotionState(const Geometry::Point &position, double mass, bool immovable)
      : position(position), immovable(immovable) {
    if (immovable) {
      this->mass = 1e18;
    } else {
      this->mass = mass;
    }
  }

  void MotionState::move(double t) {
    position = position + velocity * t + acceleration * t * t * 0.5f;
    velocity = velocity + acceleration * t;
  }

  void MotionState::setGravity(double g) {
    acceleration = acceleration + Geometry::Vector(0, g);
  }

  void MotionState::setVelocity(const Geometry::Vector &v) {
    velocity = v;
  }

  void MotionState::setDrag(const float &coefficient) {}

  Geometry::Vector MotionState::calculateCollision(MotionState &other,
                                                     const Geometry::Vector &normalVec) const {
    double massConstant = 2 * other.mass / (mass + other.mass);
    return velocity - massConstant *
                              Geometry::Vector::dotProduct(velocity - other.velocity, normalVec) *
                              normalVec;
  }

  void MotionState::render(const Geometry::Point &p) const {
    auto renderer = Renderer::getInstance();
    renderer->drawVector(p, velocity, Palette::get()->Green);
  }

}// namespace Physics
