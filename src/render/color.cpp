//
// Created by Trần Công Việt An on 2/5/20.
//

#include "color.hpp"
Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : r(red), g(green), b(blue), a(alpha) {}

Color::Color(uint32_t hex, uint8_t alpha) : Color((hex >> 16u) & 0xffu, (hex >> 8u) & 0xFFu, hex & 0xFFu, alpha) {}
Color::Color(uint32_t hex) : Color(hex, 0xff) {}
Color::Color() : Color(0x000000) {}
