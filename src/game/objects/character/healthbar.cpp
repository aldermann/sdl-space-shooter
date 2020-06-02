//
// Created by Trần Công Việt An on 1/6/20.
//

#include "healthbar.hpp"

Healthbar::Healthbar():heart("assets/heart.png", 38, 0, 39, 1){}

void Healthbar::reduceHealth(int x) {
  currentHealth -= x;
}

void Healthbar::render(){
  Geometry::Point center = {1248, 32};
  for (int i = 0; i < currentHealth; ++i)
  {
    Renderer* renderer = Renderer::getInstance();
    renderer->drawTexture(heart, {center.x - 64 * i, center.y}, 0);
  }
}
