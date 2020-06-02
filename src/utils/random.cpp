//
// Created by Trần Công Việt An on 2/6/20.
//

#include "random.hpp"

#include <engine/geometry/geometry.hpp>

Random* Random::instance = nullptr;

Random::Random() : dv(), generator(dv()) {}

int Random::randInt(int low, int high) {
  std::uniform_int_distribution<> distribution(low, high);
  return distribution(instance->generator);
}

float Random::randFloat(float low, float high) {
  return static_cast<float>(randDouble(low, high));
}

double Random::randDouble(double low, double high) {
  std::uniform_real_distribution<> distribution(low, high);
  return distribution(instance->generator);
}

Geometry::Vector Random::randVector(double lowX, double highX, double lowY, double highY) {
  double x = randDouble(lowX, highX);
  double y = randDouble(lowY, highY);
  return {x, y};
}

void Random::initialize() {
  instance = new Random();
}
