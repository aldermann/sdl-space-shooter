#include "ttf_error.hpp"
#include <SDL2/SDL_ttf.h>

TTFError::TTFError(Severity severity) : AppError(TTF_GetError(), severity) {
  TTF_ClearError();
}
FatalTTFError::FatalTTFError() : TTFError(FATAL) {}
WarningTTFError::WarningTTFError() : TTFError(WARNING) {}