//
// Created by Trần Công Việt An on 2/5/20.
//

#include "motion.hpp"

#include <iostream>
#include <render/renderer.hpp>

namespace Physics {
  Motion::Motion() : mass(1), immovable(false) {}
  Motion::Motion(double mass, bool immovable) : immovable(immovable) {
    if (immovable) {
      this->mass = 1e18;
    } else {
      this->mass = mass;
    }
  }

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

  Geometry::Vector Motion::calculateElasticCollision(Motion &other,
                                                     const Geometry::Vector &normalVec) const {
    double massConstant = 2 * other.mass / (mass + other.mass);
    return velocity - massConstant *
                              Geometry::Vector::dotProduct(velocity - other.velocity, normalVec) *
                              normalVec;
  }
  void Motion::render(const Geometry::Point &p) {
    auto renderer = Renderer::getInstance();
    renderer->drawVector(p, velocity, Palette::get()->Green);
  }

}// namespace Physics
