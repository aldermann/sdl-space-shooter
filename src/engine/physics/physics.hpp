//
// Created by Trần Công Việt An on 17/5/20.
//

#pragma once


#include <engine/geometry/geometry.hpp>
namespace Physics {
  class World {
    /**
     * Class that hold global physics properties
     */

  private:
    Geometry::Vector gravity;
    static World* instance;
    explicit World(double gravity);

  public:
    static World* init(double g);
    static Geometry::Vector getGravity();
  };
}// namespace Physics
