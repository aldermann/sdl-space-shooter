#include "background.hpp"

#include "game/objects/character/const.hpp"

Background::Background(const char* path,
                       Geometry::Point center,
                       int imageW,
                       int imageH,
                       int outputW,
                       int outputH)
    : center(center), texture(path,
                              (imageH - outputH) / 2,
                              (imageH - outputH) / 2,
                              (imageW - outputW) / 2,
                              (imageW - outputW) / 2,
                              outputW,
                              outputH) {}

Background::Background(const char* path, Geometry::Point center, int outputW, int outputH)
    : center(center), texture(path, outputW, outputH) {}

void Background::render() {
  Renderer* renderer = Renderer::getInstance();
  renderer->drawTexture(texture, center, 0);
}