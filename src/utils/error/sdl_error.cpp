//
// Created by Trần Công Việt An on 2/5/20.
//

#include "sdl_error.hpp"
#include "SDL.h"

SDLError::SDLError(Severity severity) : AppError(SDL_GetError(), severity) {
  SDL_ClearError();
}
FatalSDLError::FatalSDLError() : SDLError(FATAL) {}
WarningSDLError::WarningSDLError() : SDLError(WARNING) {}
