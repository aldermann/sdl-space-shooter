//
// Created by Trần Công Việt An on 6/5/20.
//
#pragma once

#include <vector>

namespace Number {
  class FloatInterval {
  public:
    double start, end;
    bool startOpen, endOpen;
    FloatInterval(double start, double end);
    FloatInterval(double start, bool startOpen, double end, bool endOpen);
    [[nodiscard]] bool contain(double num) const;
    [[nodiscard]] int compare(double num) const;
  };

  std::vector<int> range(int start, int end, int step);
  std::vector<int> range(int start, int end);
  std::vector<int> range(int end);

  template<typename T>
  T clamp(T num, T lower, T upper);
}// namespace Number
