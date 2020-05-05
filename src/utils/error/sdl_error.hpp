//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once

#include "error.hpp"

class SDLError : public AppError {
public:
  explicit SDLError(Severity severity);
};

class FatalSDLError : public SDLError {
public:
  FatalSDLError();
};

class WarningSDLError : public SDLError {
public:
  WarningSDLError();
};
