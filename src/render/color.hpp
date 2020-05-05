//
// Created by Trần Công Việt An on 2/5/20.
//

#ifndef SDL_SPACE_SHOOTER_COLOR_HPP
#define SDL_SPACE_SHOOTER_COLOR_HPP


#include <cstdint>
class Color {
public:
  uint8_t r, g, b, a;
  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
  Color(uint32_t hex, uint8_t alpha);
  explicit Color(uint32_t hex);
  Color();
};


#endif//SDL_SPACE_SHOOTER_COLOR_HPP
