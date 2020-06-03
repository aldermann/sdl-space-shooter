//
// Created by Trần Công Việt An on 2/6/20.
//

#pragma once

#include <engine/geometry/geometry.hpp>
#include <random>

class Random {
  static Random* instance;
  std::random_device dv;
  std::mt19937 generator;
  Random();

public:
  static void initialize();
  static int randInt(int low, int high);
  static float randFloat(float low, float high);
  static double randDouble(double low, double high);
  static Geometry::Vector randVector(double lowX, double highX, double lowY, double highY);
};
