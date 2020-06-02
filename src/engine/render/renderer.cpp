//
// Created by Trần Công Việt An on 1/5/20.
//

#include "renderer.hpp"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <chrono>
#include <iostream>

#include "SDL2_gfxPrimitives.h"
#include "texture.hpp"
#include "utils/error/sdl_error.hpp"
#include "utils/number.hpp"
#include "utils/timer.hpp"
#include "utils/utils.hpp"

Renderer::Renderer(SDL_Renderer *renderer, SDL_Window *window)
    : sdlRenderer(renderer), window(window) {
  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  TTF_Init();
}
Renderer::~Renderer() {
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  TTF_Quit();
}

Renderer *Renderer::instance = nullptr;
Renderer *Renderer::createInstance(const std::string &title, int width, int height) {
  if (instance == nullptr) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
      throw FatalSDLError();
    }
    SDL_Window *window = SDL_CreateWindow(title.c_str(),
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width,
                                          height,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    disable_compositor();
    if (window == nullptr) {
      throw FatalSDLError();
    }
    SDL_Renderer *render =
            SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr) {
      throw FatalSDLError();
    }
    if (SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND)) {
      throw FatalSDLError();
    }
    instance = new Renderer(render, window);
  }
  return instance;
}

Renderer *Renderer::getInstance() {
  if (instance == nullptr) {
    throw FatalAppError("Renderer's instance not initialized.");
  }
  return instance;
}

SDL_Renderer *Renderer::getSDLRenderer() {
  return getInstance()->sdlRenderer;
}

Uint32 Renderer::getPixelFormat() {
  auto res = SDL_GetWindowPixelFormat(instance->window);
  if (res == SDL_PIXELFORMAT_UNKNOWN) {
    throw FatalSDLError();
  }
  return res;
}

void Renderer::releaseInstance() {
  delete instance;
}

void Renderer::setDrawColor(Color c) {
  SDL_SetRenderDrawColor(sdlRenderer, c.r, c.g, c.b, c.a);
}

void Renderer::clearScreen(Color c) {
  this->setDrawColor(c);
  int ok = SDL_RenderClear(sdlRenderer);
  if (ok < 0) {
    throw FatalSDLError();
  }
}

void Renderer::present() {
  SDL_RenderPresent(sdlRenderer);
}

void Renderer::drawCircle(const Geometry::Circle &c, Color col) {
  if (filledCircleRGBA(sdlRenderer, c.center.x, c.center.y, c.radius, col.r, col.g, col.b, col.a) <
      0) {
    throw WarningSDLError();
  }
}

void Renderer::drawCircleBorder(const Geometry::Circle &c, Color col) {
  if (circleRGBA(sdlRenderer, c.center.x, c.center.y, c.radius, col.r, col.g, col.b, col.a) < 0) {
    throw WarningSDLError();
  }
}

void Renderer::drawRectangle(const Geometry::Rectangle &r, Color col) {
  auto corners = r.getCorners();
  Sint16 cornerX[4], cornerY[4];
  for (int i : Number::range(4)) {
    cornerX[i] = (int) corners[i].x;
    cornerY[i] = (int) corners[i].y;
  }
  if (filledPolygonRGBA(sdlRenderer, cornerX, cornerY, 4, col.r, col.g, col.b, col.a) < 0) {
    throw WarningSDLError();
  }
}

void Renderer::drawRectangleBorder(const Geometry::Rectangle &r, Color col) {
  auto corners = r.getCorners();
  Sint16 cornerX[4], cornerY[4];
  for (int i : Number::range(4)) {
    cornerX[i] = (int) corners[i].x;
    cornerY[i] = (int) corners[i].y;
  }
  if (polygonRGBA(sdlRenderer, cornerX, cornerY, 4, col.r, col.g, col.b, col.a) < 0) {
    throw WarningSDLError();
  }
}

void Renderer::drawSegment(const Geometry::Segment &s, double thickness, Color col) {
  const Geometry::Point &a = s.a, &b = s.b;
  if (thickLineRGBA(sdlRenderer, a.x, a.y, b.x, b.y, thickness, col.r, col.g, col.b, col.a) < 0) {
    throw WarningSDLError();
  }
}

void Renderer::drawVector(const Geometry::Point &position, const Geometry::Vector &v, Color col) {
  Geometry::Point endPoint = position + v;
  drawSegment({position, endPoint}, 5, col);
}

void Renderer::drawTexture(const Texture &texture, const Geometry::Point &position, double angle) {
  SDL_Rect renderArea = texture.getRenderArea(position);
  SDL_RenderCopyEx(sdlRenderer,
                   texture.mTexture,
                   &texture.cropRect,
                   &renderArea,
                   angle,
                   nullptr,
                   SDL_FLIP_NONE);
}
