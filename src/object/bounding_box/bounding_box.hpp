//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once
#include "geometry/geometry.hpp"
#include"render/renderer.hpp"

namespace BoundingBox {
  enum Shape { Rectangle, Circle };

  class CircleBox;
  class RectangleBox;

  class Box {
  public:
    virtual ~Box();
    virtual Shape getShape() = 0;
    virtual void render(Geometry::Point &position) = 0;
    bool checkCollision(Geometry::Point &position, Geometry::Point &otherPosition, Box *otherBox);
    Geometry::Vector normalCollisionVector(const Geometry::Point &pos,
                                           const Geometry::Point &otherPos,
                                           Box *otherBox);

    virtual bool checkCollisionCirc(const Geometry::Point &position,
                                    const Geometry::Point &otherPosition,
                                    CircleBox *otherBox) = 0;
    virtual bool checkCollisionRect(const Geometry::Point &position,
                                    const Geometry::Point &otherPosition,
                                    RectangleBox *otherBox) = 0;

    virtual Geometry::Vector normalCollisionVectorRect(const Geometry::Point &pos,
                                                       const Geometry::Point &otherPos,
                                                       RectangleBox *otherBox) = 0;
    virtual Geometry::Vector normalCollisionVectorCirc(const Geometry::Point &pos,
                                                       const Geometry::Point &otherPos,
                                                       CircleBox *other) = 0;
  };

  class CircleBox : public Box {

  public:
    Geometry::Circle circle;
    CircleBox(const Geometry::Point &offset, double radius);
    explicit CircleBox(double radius);
    ~CircleBox() override;
    Shape getShape() override;
    void render(Geometry::Point &position) override;
    bool checkCollisionCirc(const Geometry::Point &position,
                            const Geometry::Point &otherPosition,
                            CircleBox *otherBox) override;
    bool checkCollisionRect(const Geometry::Point &position,
                            const Geometry::Point &otherPosition,
                            RectangleBox *other) override;

    Geometry::Vector normalCollisionVectorRect(const Geometry::Point &pos,
                                               const Geometry::Point &otherPos,
                                               RectangleBox *otherBox) override;
    Geometry::Vector normalCollisionVectorCirc(const Geometry::Point &pos,
                                               const Geometry::Point &otherPos,
                                               CircleBox *other) override;
  };

  class RectangleBox : public Box {

  public:
    Geometry::Rectangle rect;
    void render(Geometry::Point &position) override;
    RectangleBox(const Geometry::Point &offset, double w, double h, double angle);
    RectangleBox(const Geometry::Point &offset,
                 const Geometry::Vector &w,
                 const Geometry::Vector &h);
    explicit RectangleBox(const Geometry::Vector &w, const Geometry::Vector &h);

    ~RectangleBox() override;
    Shape getShape() override;

    bool checkCollisionCirc(const Geometry::Point &position,
                            const Geometry::Point &otherPosition,
                            CircleBox *other) override;

    bool checkCollisionRect(const Geometry::Point &position,
                            const Geometry::Point &otherPosition,
                            RectangleBox *otherBox) override;

    Geometry::Vector normalCollisionVectorCirc(const Geometry::Point &pos,
                                               const Geometry::Point &otherPos,
                                               CircleBox *otherBox) override;
    Geometry::Vector normalCollisionVectorRect(const Geometry::Point &pos,
                                               const Geometry::Point &otherPos,
                                               RectangleBox *other) override;
  };
};// namespace BoundingBox
