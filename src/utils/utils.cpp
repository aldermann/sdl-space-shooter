//
// Created by Trần Công Việt An on 6/5/20.
//
//
// Created by Trần Công Việt An on 1/5/20.
//

#include "utils.hpp"

#include <algorithm>
#include <iostream>

#include "SDL.h"

void disable_compositor() {
#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
  // Disable compositor bypass
  if (!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0")) {
    std::cout << "SDL can not disable compositor bypass!" << std::endl;
    std::exit(-1);
  }
#endif
}

double signum(double a) {
  if (a < 0) {
    return -1;
  }
  if (a > 0) {
    return 1;
  }
  return 0;
}

bool doubleEqual(const double &a, const double &b) {
  return (abs(a - b) < 1e-6);
}

boost::filesystem::path getParentPath(const boost::filesystem::path &p) {
  const std::string &m = p.string();
  const std::string slash("/");
  auto last_slash(
          std::find_end(std::cbegin(m), std::cend(m), std::cbegin(slash), std::cend(slash)));
  const std::string parent(m.begin(), last_slash);
  return boost::filesystem::path(parent);
}