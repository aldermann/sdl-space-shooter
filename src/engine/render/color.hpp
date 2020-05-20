//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once

#include <cstdint>
#include <ostream>

class Color {
public:
  uint8_t r{}, g{}, b{}, a{};
  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
  Color(uint32_t hex, uint8_t alpha);
  explicit Color(uint32_t hex);
  Color();
  friend std::ostream &operator<<(std::ostream &os, const Color &p);
  [[nodiscard]] int getHex() const;
  [[nodiscard]] int getAlphaHex() const;
};

class Palette {
private:
  static Palette *instance;

public:
  static Palette *init();
  static Palette *get();
  Color Red, Orange, Yellow, Green, Blue, Indigo, Violet, Black, White, Grey;
};
