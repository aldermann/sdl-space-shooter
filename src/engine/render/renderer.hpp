//
// Created by Trần Công Việt An on 1/5/20.
//

#pragma once

#include <SDL.h>

#include "color.hpp"
#include "engine/geometry/geometry.hpp"
#include "texture.hpp"

class Renderer {

private:
  static Renderer *instance;
  Renderer(SDL_Renderer *renderer, SDL_Window *window, int w, int h);
  ~Renderer();

private:
  SDL_Renderer *sdlRenderer;
  SDL_Window *window;
  Texture *background;
  int w, h;


public:
  static Renderer *createInstance(const std::string &title, int width, int height);
  static Renderer *getInstance();
  static void releaseInstance();
  static SDL_Renderer *getSDLRenderer();
  static Uint32 getPixelFormat();

public:
  void clearScreen(Color c);
  void drawCircle(const Geometry::Circle &c, Color col);
  void drawCircleBorder(const Geometry::Circle &c, Color col);
  void present();
  void setDrawColor(Color c);
  void setBackground(const std::string &path);
  void drawRectangle(const Geometry::Rectangle &r, Color col);
  void drawRectangleBorder(const Geometry::Rectangle &r, Color col);
  void drawSegment(const Geometry::Segment &s, double thickness, Color col);
  void drawVector(const Geometry::Point &position, const Geometry::Vector &v, Color col);
  void drawTexture(const Texture &texture, const Geometry::Point &position, double angle);
  void clearBackground();
};
