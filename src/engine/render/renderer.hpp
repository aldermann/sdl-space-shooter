//
// Created by Trần Công Việt An on 1/5/20.
//

#pragma once

#include <SDL.h>

#include "color.hpp"
#include "engine/geometry/geometry.hpp"

class Renderer {
private:
  SDL_Renderer *sdlRenderer;
  static Renderer *instance;
  static SDL_Window *window;
  explicit Renderer(SDL_Renderer *);
  ~Renderer();

public:
  static Renderer *createInstance(const std::string& title, int width, int height);
  static Renderer *getInstance();
  static void releaseInstance();
  static SDL_Renderer* getSDLRenderer();
  void clearScreen(Color c);
  void drawCircle(const Geometry::Circle &c, Color col);
  void drawCircleBorder(const Geometry::Circle &c, Color col);
  void present();
  void setDrawColor(Color c);
  void drawRectangle(const Geometry::Rectangle &r, Color col);
  void drawRectangleBorder(const Geometry::Rectangle &r, Color col);
  void drawSegment(const Geometry::Segment &s, double thickness, Color col);
  void drawVector(const Geometry::Point &position, const Geometry::Vector &v, Color col);
};
