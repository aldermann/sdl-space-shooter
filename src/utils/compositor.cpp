//
// Created by Trần Công Việt An on 1/5/20.
//

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
