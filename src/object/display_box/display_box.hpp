//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once

#include <geometry/geometry.hpp>
#include <render/color.hpp>
#include <render/renderer.hpp>

namespace DisplayBox {
  class Box {
    Color color;

  protected:
    Box(Color color);

  public:
    virtual ~Box();
    virtual void render(const Geometry::Point &position) = 0;
  };

  class CircleBox : public Box {
  public:
    CircleBox(double radius, Color color);
    Color color;
    Geometry::Circle circle;

    CircleBox(Geometry::Point offset, double radius, Color color);
    CircleBox(Geometry::Circle circle, Color color);
    ~CircleBox() override;
    void render(const Geometry::Point &position) override;
  };
}// namespace DisplayBox
