//
// Created by Trần Công Việt An on 2/5/20.
//

#include "motion.hpp"

#include <iostream>
#include"render/renderer.hpp"

namespace Physics {
  MotionState::MotionState() : mass(1), g(0), drag(0), immovable(false) {}
  MotionState::MotionState(const Geometry::Point &position, double mass, bool immovable)
      : position(position), g(0), drag(0), immovable(immovable) {
    if (immovable) {
      this->mass = 1e18;
    } else {
      this->mass = mass;
    }
  }

  MotionState MotionState::nextState(double t) const {
    MotionState newState = *this;
    newState.position = position + velocity * t + acceleration * t * t * 0.5f;
    newState.velocity = velocity + acceleration * t;
    if (abs(newState.velocity.x + newState.velocity.y) < 1e-2) {
      newState.velocity = {0, 0};
    }
    newState.acceleration = acceleration - velocity * drag + newState.velocity * drag;
    return newState;
  }

  void MotionState::setGravity(double newG) {
    acceleration = acceleration + Geometry::Vector(0, newG - g);
    g = newG;
  }

  void MotionState::setVelocity(const Geometry::Vector &v) {
    velocity = v;
  }

  void MotionState::setDrag(const float &coefficient) {
    drag = coefficient;
  }

  Geometry::Vector MotionState::velocityAfterCollision(MotionState &other,
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

  std::pair<MotionState, MotionState> exactCollisionPosition(MotionState &a,
                                                              MotionState &b,
                                                              double time,
                                                              const MotionState::collisionPredicate& f) {
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
