#pragma once

#include <engine/geometry/geometry.hpp>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL.h"

class Texture {
public:
  Texture();
  explicit Texture(const char* path);
  Texture(const std::string& path,
          int cropTop,
          int cropBottom,
          int cropLeft,
          int cropRight,
          int outputWidth,
          int outputHeight);
  Texture(const char* path, int outputWidth, int outputHeight);
  Texture(std::string textureText, SDL_Color textColor);
  ~Texture();
  friend class Renderer;

private:
  [[nodiscard]] SDL_Rect getRenderArea(const Geometry::Point& position) const;
  SDL_Texture* mTexture;
  SDL_Rect cropRect;
  TTF_Font* gFont = TTF_OpenFont("assets/lazy.ttf", 15);
  int outputWidth = 0, outputHeight = 0;
};
