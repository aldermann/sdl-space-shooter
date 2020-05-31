#pragma once


#include <engine/object/object.hpp>


class Background : public GameObject {
private:
  Geometry::Point center;
  Texture texture;

public:
  Background(const char* path, Geometry::Point center, int outputW, int outputH);
  Background(const char* path, Geometry::Point center, int imageW, int imageH, int outputW, int outputH);
  void render() override;
};
