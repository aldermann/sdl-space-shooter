//
// Created by Trần Công Việt An on 1/5/20.
//

#pragma once

#include "render/color.hpp"
#include <SDL.h>
#include <geometry/geometry.hpp>

class Renderer {
  SDL_Renderer *sdlRenderer;
  static Renderer *instance;

private:
  explicit Renderer(SDL_Renderer *);
  ~Renderer();

public:
  static Renderer *createInstance(SDL_Window *window);
  static Renderer *getInstance();
  static void releaseInstance();
  void clearScreen(Color c);
  //  void drawRect(int x, int y, int w, int h);
  //  void drawRect(SDL_Rect *rect);
  void drawCircle(Geometry::Circle c, Color col);
  void present();
  void setDrawColor(Color c);
};
