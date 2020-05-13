//
// Created by Trần Công Việt An on 4/5/20.
//

#include "timer.hpp"

using namespace std::chrono;

void Timer::start() {
  startTime = high_resolution_clock::now();
  lastTick = startTime;
  running = true;
}

void Timer::stop() {
  endTime = high_resolution_clock::now();
  running = false;
}

double Timer::elapsedSecondsHR() {
  auto now = high_resolution_clock::now();
  return duration_cast<duration<double>>(now - startTime).count();
}

double Timer::elapsedMilliseconds() {
  auto now = high_resolution_clock::now();
  return duration_cast<milliseconds>(now - startTime).count();
}

double Timer::elapsedSecondsHRSinceTick() {
  auto now = high_resolution_clock::now();
  return duration_cast<duration<double>>(now - lastTick).count();
}

double Timer::elapsedMillisecondsSinceTick() {
  auto now = high_resolution_clock::now();
  return duration_cast<milliseconds>(now - lastTick).count();
}

void Timer::tick() {
  lastTick = high_resolution_clock::now();
}
