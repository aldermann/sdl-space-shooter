//
// Created by Trần Công Việt An on 6/5/20.
//

#include "number.hpp"

namespace Number {
  FloatInterval::FloatInterval(double start, double end)
      : FloatInterval(start, false, end, false) {}

  FloatInterval::FloatInterval(double start, bool startOpen, double end, bool endOpen)
      : start(start), end(end), startOpen(startOpen), endOpen(endOpen) {}

  bool FloatInterval::contain(double num) const {
    bool c1 = startOpen ? start < num : start <= num;
    bool c2 = endOpen ? num < end : num <= end;
    return c1 and c2;
  }

  int FloatInterval::compare(double num) const {
    bool c1 = startOpen ? start < num : start <= num;
    if (!c1) return -1;
    bool c2 = endOpen ? num < end : num <= end;
    if (!c2) return 1;
    return 0;
  }

  std::vector<int> range(int start, int end, int step) {
    std::vector<int> res;
    for (int i = start; i < end; i += step) {
      res.push_back(i);
    }
    return res;
  }

  std::vector<int> range(int start, int end) {
    return range(start, end, 1);
  }

  std::vector<int> range(int end) {
    return range(0, end, 1);
  }
}// namespace Number
