//
// Created by Trần Công Việt An on 1/5/20.
//

#pragma once

#include <boost/stacktrace.hpp>
#include <string>

enum Severity { FATAL, WARNING, INFO };
class AppError : private std::exception {
private:
  boost::stacktrace::stacktrace trace;

protected:
  AppError(std::string message, Severity severity);
  friend std::ostream &operator<<(std::ostream &os, const AppError &err);

public:
  std::string message;
  Severity severity;
};

class FatalAppError : public AppError {
public:
  explicit FatalAppError(std::string message);
};
