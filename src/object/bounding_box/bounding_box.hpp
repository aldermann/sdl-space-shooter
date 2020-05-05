//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once
#include "geometry/geometry.hpp"

namespace BoundingBox {
  enum Shape { Rectangle, Circle };

  class CircleBox;
  class RectangleBox;

  class Box {
  public:
    virtual void print() = 0;
    virtual ~Box();
    virtual Shape getShape() = 0;
    virtual bool checkCollision(Geometry::Point &position,
                                Geometry::Point &otherPosition,
                                CircleBox &otherBox) = 0;
    virtual bool checkCollision(Geometry::Point &position,
                                Geometry::Point &otherPosition,
                                RectangleBox &other) = 0;
    virtual Geometry::Vector normalCollisionVector(RectangleBox &other) = 0;
    virtual Geometry::Vector normalCollisionVector(CircleBox &other) = 0;
  };

  class CircleBox : public Box {

  private:
    Geometry::Circle circle;

  public:
    CircleBox(Geometry::Point offset, double radius);
    explicit CircleBox(double radius);
    ~CircleBox() override;
    Shape getShape() override;

    bool checkCollision(Geometry::Point &position,
                        Geometry::Point &otherPosition,
                        CircleBox &otherBox) override;
    bool checkCollision(Geometry::Point &position,
                        Geometry::Point &otherPosition,
                        RectangleBox &other) override;
    Geometry::Vector normalCollisionVector(RectangleBox &other) override;
    Geometry::Vector normalCollisionVector(CircleBox &other) override;
    void print() override;
  };

  class RectangleBox : public Box {};

}// namespace BoundingBox
