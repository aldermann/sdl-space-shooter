//
// Created by Trần Công Việt An on 1/5/20.
//

#include "error.hpp"
#include <iostream>
#include <utility>
AppError::AppError(std::string message, const Severity severity) : message(std::move(message)), severity(severity) {
  this->trace = boost::stacktrace::stacktrace();
}

std::ostream &operator<<(std::ostream &os, const AppError &err) {
  return os << "App error:\nMessage: " << err.message << "\nStacktrace: " << err.trace << "\n";
}

FatalAppError::FatalAppError(std::string message) : AppError(std::move(message), FATAL) {}
