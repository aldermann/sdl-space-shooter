//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once

#include"geometry/geometry.hpp"
#include"render/color.hpp"
#include"render/renderer.hpp"

namespace DisplayBox {
  class Box {

  protected:
    Color color;
    explicit Box(Color color);

  public:
    virtual ~Box();
    virtual void render(const Geometry::Point &position) = 0;
    void setColor(const Color& col);
  };

  class CircleBox : public Box {
  public:
    Geometry::Circle circle;
    CircleBox(double radius, Color color);
    CircleBox(const Geometry::Point& offset, double radius, Color color);
    CircleBox(Geometry::Circle circle, Color color);
    ~CircleBox() override;
    void render(const Geometry::Point &position) override;
  };

  class RectangleBox : public Box {
  public:
    RectangleBox(double w, double h, double angle, Color color);
    Geometry::Rectangle rect;
    RectangleBox(const Geometry::Point& offset, double w, double h, double angle, Color color);
    RectangleBox(Geometry::Rectangle rectangle, Color color);
    ~RectangleBox() override;
    void render(const Geometry::Point &position) override;
  };
}// namespace DisplayBox
