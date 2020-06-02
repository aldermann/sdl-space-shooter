#pragma once

#include "error.hpp"

class TTFError : public AppError {
public:
  explicit TTFError(Severity severity);
};

class FatalTTFError : public TTFError {
public:
  FatalTTFError();
};

class WarningTTFError : public TTFError {
public:
  WarningTTFError();
};