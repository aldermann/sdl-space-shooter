#include "texture.hpp"

#include <SDL_image.h>

#include "engine/render/renderer.hpp"
#include "utils/error/sdl_error.hpp"

Texture::Texture() : mTexture(nullptr), cropRect() {}
Texture::Texture(const char* path) : Texture(path, 0, 0, 0, 0, 0, 0) {}
Texture::Texture(const char* path, int outputWidth, int outputHeight)
    : Texture(path, 0, 0, 0, 0, outputWidth, outputHeight) {}

Texture::Texture(const char* path,
                 int cropTop,
                 int cropBottom,
                 int cropLeft,
                 int cropRight,
                 int outputWidth,
                 int outputHeight)
    : cropRect() {
  mTexture = IMG_LoadTexture(Renderer::getSDLRenderer(), path);
  if (mTexture == nullptr) {
    throw FatalSDLError();
  }
  int imageW, imageH;
  SDL_QueryTexture(mTexture, nullptr, nullptr, &imageW, &imageH);
  SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
  cropRect.x = cropLeft;
  cropRect.y = cropTop;
  cropRect.h = imageH - cropTop - cropBottom;
  cropRect.w = imageW - cropLeft - cropRight;
  this->outputHeight = outputHeight ? outputHeight : cropRect.h;
  this->outputWidth = outputWidth ? outputWidth : cropRect.w;
}

Texture::~Texture() {
  if (mTexture != nullptr) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}

SDL_Rect Texture::getRenderArea(const Geometry::Point& pos) const {
  SDL_Rect res;
  res.w = outputWidth;
  res.h = outputHeight;
  res.x = (int) pos.x - res.w / 2;
  res.y = (int) pos.y - res.h / 2;
  return res;
}
