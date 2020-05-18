//
// Created by Trần Công Việt An on 16/5/20.
//

#pragma once

#include "engine/geometry/geometry.hpp"
#include "engine/object/bounding_box/bounding_box.hpp"
#include "motion.hpp"

namespace Physics {
  class Dynamic {


  protected:
    MotionState lastMotion, motion;
    double mass, elasticity;
    bool movable;

  public:
    Dynamic();
    Dynamic(const MotionState &initialMotion, double mass, double elasticity);
    Dynamic(const Geometry::Point &position, double mass, double elasticity);
    Dynamic(const MotionState &initialMotion, bool movability);
    Dynamic(const Geometry::Point &position, bool movability);

    [[nodiscard]] const Geometry::Vector &velocity() const;
    [[nodiscard]] const Geometry::Vector &acceleration() const;
    [[nodiscard]] const Geometry::Point &position() const;

    void render(const Geometry::Point &p) const;
    void advance(double time);

    void setVelocity(const Geometry::Vector &v);
    void setHorizontalVelocity(double hVelocity);
    void setVerticalVelocity(double vVelocity);

    static void handleSolidCollision(Dynamic &aDyn,
                                     Dynamic &bDyn,
                                     BoundingBox::Box *aBox,
                                     BoundingBox::Box *bBox,
                                     double time);

  private:
    [[nodiscard]] Geometry::Vector velocityAfterCollision(const Dynamic &other,
                                                          const Geometry::Vector &normalVec) const;
  };

}// namespace Physics
