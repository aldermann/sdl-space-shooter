//
// Created by Trần Công Việt An on 2/5/20.
//

#include "color.hpp"

#include "utils/error/error.hpp"

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : r(red), g(green), b(blue), a(alpha) {}

Color::Color(uint32_t hex, uint8_t alpha)
    : Color((hex >> 16u) & 0xffu, (hex >> 8u) & 0xffu, hex & 0xffu, alpha) {}
Color::Color(uint32_t hex) : Color(hex, 0xff) {}
Color::Color() : Color(0x000000) {}


std::ostream &operator<<(std::ostream &os, const Color &c) {
  return os << "Color (r: " << (int) c.r << "; g: " << (int) c.g << "; b: " << (int) c.b
            << "; a: " << (int) c.a << ")";
}
int Color::getHex() const {
  return (r << 16u) + (g << 8u) + b;
}

int Color::getAlphaHex() const {
  return (r << 24u) + (g << 16u) + (b << 8u) + a;
}

Palette *Palette::instance = nullptr;

Palette *Palette::init() {
  if (instance != nullptr) {
    return instance;
  }
  instance = new Palette();
  instance->Red = Color(0xFF0000);
  instance->Orange = Color(0xFF7F00);
  instance->Yellow = Color(0xFFFF00);
  instance->Green = Color(0x00FF00);
  instance->Blue = Color(0x0000FF);
  instance->Indigo = Color(0x2E2B5F);
  instance->Violet = Color(0x8B00FF);
  instance->Black = Color(0x000000);
  instance->White = Color(0xffffff);
  instance->Grey = Color(0xBDBDBD);
  return instance;
}
Palette *Palette::get() {
  if (Palette::instance != nullptr) {
    return Palette::instance;
  }
  throw FatalAppError("Palette hasn't been instantiated yet");
}
// namespace Palette
