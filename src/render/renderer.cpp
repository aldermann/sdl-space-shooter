//
// Created by Trần Công Việt An on 1/5/20.
//

#include "renderer.hpp"
#include "SDL2_gfxPrimitives.h"
#include "utils/error/sdl_error.hpp"
#include <chrono>
#include <iostream>
#include <utils/timer.hpp>

Renderer::Renderer(SDL_Renderer *renderer) : sdlRenderer(renderer) {}
Renderer::~Renderer() {
  SDL_DestroyRenderer(sdlRenderer);
}

Renderer *Renderer::instance = nullptr;

Renderer *Renderer::createInstance(SDL_Window *window) {
  if (Renderer::instance == nullptr) {
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
void Renderer::drawCircle(Geometry::Circle c, Color col) {
  if (filledCircleRGBA(sdlRenderer, c.origin.x, c.origin.y, c.radius, col.r, col.g, col.b, col.a) < 0) {
    throw WarningSDLError();
  }
}
