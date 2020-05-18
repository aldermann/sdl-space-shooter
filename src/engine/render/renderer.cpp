//
// Created by Trần Công Việt An on 1/5/20.
//

#include "renderer.hpp"

#include <chrono>
#include <iostream>

#include "SDL2_gfxPrimitives.h"
#include "utils/error/sdl_error.hpp"
#include "utils/number.hpp"
#include "utils/timer.hpp"
#include "utils/utils.hpp"

Renderer::Renderer(SDL_Renderer *renderer) : sdlRenderer(renderer) {}
Renderer::~Renderer() {
  SDL_DestroyRenderer(sdlRenderer);
}

Renderer *Renderer::instance = nullptr;
SDL_Window *Renderer::window = nullptr;

Renderer *Renderer::createInstance() {
  if (Renderer::instance == nullptr) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      throw FatalSDLError();
    }
    Renderer::window = SDL_CreateWindow("Ball emulator",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        1200,
                                        780,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    disable_compositor();
    if (Renderer::window == nullptr) {
      throw FatalSDLError();
    }
    SDL_Renderer *render = SDL_CreateRenderer(Renderer::window,
                                              -1,
                                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == nullptr) {
      throw FatalSDLError();
    }
    Renderer::instance = new Renderer(render);
  }
  return Renderer::instance;
}

Renderer *Renderer::getInstance() {
  if (Renderer::instance == nullptr) {
    throw FatalAppError("Renderer's instance not initialized.");
  }
  return Renderer::instance;
}

void Renderer::releaseInstance() {
  delete Renderer::instance;
  SDL_DestroyWindow(Renderer::window);
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
