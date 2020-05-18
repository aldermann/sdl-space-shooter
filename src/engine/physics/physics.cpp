//
// Created by Trần Công Việt An on 17/5/20.
//

#include "physics.hpp"

#include <engine/geometry/geometry.hpp>
namespace Physics {
  World* World::instance = nullptr;
  World::World(double g) : gravity(0, g) {}
  World* Physics::World::init(double g) {
    if (World::instance == nullptr) {
      instance = new World(g);
    }
    return instance;
  }
  Geometry::Vector World::getGravity() {
    return instance->gravity;
  }
}// namespace Physics
