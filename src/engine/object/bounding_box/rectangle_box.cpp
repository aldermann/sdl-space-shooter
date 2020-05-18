//
// Created by Trần Công Việt An on 6/5/20.
//
#include <cmath>

#include "bounding_box.hpp"
#include "utils/number.hpp"
#include "utils/utils.hpp"

namespace BoundingBox {
  RectangleBox::RectangleBox(const Geometry::Point &offset,
                             const Geometry::Vector &w,
                             const Geometry::Vector &h)
      : rect(offset, w, h) {}
  RectangleBox::RectangleBox(const Geometry::Vector &w, const Geometry::Vector &h) : rect(w, h) {}
  RectangleBox::RectangleBox(const Geometry::Point &offset, double w, double h, double angle)
      : rect(offset, w, h, angle) {}
  RectangleBox::RectangleBox(double w, double h, double angle)
          : rect({}, w, h, angle) {}
  Shape RectangleBox::getShape() {
    return Rectangle;
  }

  bool RectangleBox::checkCollisionRect(const Geometry::Point &position,
                                        const Geometry::Point &otherPosition,
                                        RectangleBox *otherBox) {
    return false;
  }

  bool RectangleBox::checkCollisionCirc(const Geometry::Point &position,
                                        const Geometry::Point &otherPosition,
                                        CircleBox *other) {
    double r = other->circle.radius;
    Geometry::Rectangle centerBox(rect.center.withOrigin(position),
                                  rect.w.addLength(r),
                                  rect.h.addLength(r));
    return centerBox.contain(other->circle.center.withOrigin(otherPosition));
  }

  Geometry::Vector RectangleBox::normalCollisionVectorCirc(const Geometry::Point &pos,
                                                           const Geometry::Point &otherPos,
                                                           CircleBox *otherBox) {
    typedef Number::FloatInterval dInterval;
    Geometry::Point rectCenter = rect.center.withOrigin(pos);
    Geometry::Point circleCenter = otherBox->circle.center.withOrigin(otherPos);
    Geometry::Point p = circleCenter.relativeTo(rectCenter);
    double wProj = p.projectionValue(rect.w), hProj = p.projectionValue(rect.h);
    double wLen = rect.w.length(), hLen = rect.h.length();
    int signumW = dInterval(-wLen, wLen).compare(wProj);
    int signumH = dInterval(-hLen, hLen).compare(hProj);
    if (signumH == 0 && signumW == 0) {
      if (wLen - abs(wProj) < hLen - abs(hProj)) {
        return (rect.w * signum(hProj)).normalized();
      }
      return (rect.h * signum(hProj)).normalized();
    }
    if (signumH != 0 && signumW == 0) {
      return (rect.h * signumH).normalized();
    }
    if (signumH == 0) {
      return (rect.w * signumW).normalized();
    }
    return Geometry::Vector(rectCenter + rect.h * signumH + rect.w * signumW, circleCenter)
            .normalized();
  }

  Geometry::Vector RectangleBox::normalCollisionVectorRect(const Geometry::Point &pos,
                                                           const Geometry::Point &otherPos,
                                                           RectangleBox *otherBox) {
    return {};
  }
  void RectangleBox::render(const Geometry::Point &position) {
    Renderer *renderer = Renderer::getInstance();
    renderer->drawRectangleBorder(rect.translatedBy(Geometry::Vector(position)),
                                  Palette::get()->Green);
  }

  RectangleBox::~RectangleBox() = default;
}// namespace BoundingBox
