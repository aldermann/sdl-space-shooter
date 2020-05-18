//
// Created by Trần Công Việt An on 16/5/20.
//

#include "dynamic.hpp"

#include <engine/render/renderer.hpp>
#include <iostream>
#include <utils/number.hpp>

#include "physics.hpp"

namespace Physics {
  Dynamic::Dynamic() : Dynamic(Geometry::Point(), 0, 0) {}

  Dynamic::Dynamic(const Geometry::Point &position, double mass, double elasticity)
      : Dynamic(MotionState(position), mass, elasticity) {}

  Dynamic::Dynamic(const MotionState &initialMotion, double mass, double elasticity)
      : lastMotion(initialMotion), motion(initialMotion), mass(mass),
        elasticity(Number::clamp(elasticity, 0.0, 1.0)), movable(true) {}

  Dynamic::Dynamic(const MotionState &initialMotion, bool movable)
      : lastMotion(initialMotion), motion(initialMotion), mass(movable ? 1 : 1e18),
        elasticity(movable ? 1 : 0), movable(movable) {}

  Dynamic::Dynamic(const Geometry::Point &position, bool movable)
      : Dynamic(MotionState(position), movable) {}

  const Geometry::Vector &Dynamic::velocity() const {
    return motion.velocity;
  }

  const Geometry::Vector &Dynamic::acceleration() const {
    return motion.acceleration;
  }

  const Geometry::Point &Dynamic::position() const {
    return motion.position;
  }

  void Dynamic::setVelocity(const Geometry::Vector &v) {
    motion = motion.withVelocity(v);
  }
  void Dynamic::setHorizontalVelocity(double hVelocity) {
    motion = motion.withVelocity({hVelocity, motion.velocity.y});
  }

  void Dynamic::setVerticalVelocity(double vVelocity) {
    motion = motion.withVelocity({motion.velocity.x, vVelocity});
  }
  void Dynamic::render(const Geometry::Point &p) const {
    auto renderer = Renderer::getInstance();
    renderer->drawVector(p, motion.velocity, Palette::get()->Green);
  }

  void Dynamic::advance(double time) {
    if (movable) {
      lastMotion = motion;
      motion = motion.nextState(time);
      motion.acceleration = World::getGravity();
    }
  }

  Geometry::Vector Dynamic::velocityAfterCollision(const Dynamic &other,
                                                   const Geometry::Vector &normalVec) const {
    double massConstant = 2 * other.mass / (mass + other.mass);
    return motion.velocity -
           massConstant *
                   Geometry::Vector::dotProduct(motion.velocity - other.motion.velocity,
                                                normalVec) *
                   normalVec;
  }

  void Dynamic::handleSolidCollision(Dynamic &aDyn,
                                     Dynamic &bDyn,
                                     BoundingBox::Box *aBox,
                                     BoundingBox::Box *bBox,
                                     double time) {
    auto checker = [aBox, bBox](Physics::MotionState &aState, Physics::MotionState &bState) {
      return aBox->checkCollision(aState.position, bState.position, bBox);
    };
    auto states = exactCollisionState(aDyn.motion, bDyn.motion, time, checker);
    aDyn.motion = states.first;
    bDyn.motion = states.second;
    Geometry::Vector normalVec =
            aBox->normalCollisionVector(aDyn.position(), bDyn.position(), bBox);
    Geometry::Vector newVelocityA = aDyn.velocityAfterCollision(bDyn, normalVec) * aDyn.elasticity;
    Geometry::Vector newVelocityB = bDyn.velocityAfterCollision(aDyn, -normalVec) * bDyn.elasticity;
    if (aDyn.movable) {
      aDyn.setVelocity(newVelocityA);
    }
    if (bDyn.movable) {
      bDyn.setVelocity(newVelocityB);
    }
  }


}// namespace Physics
