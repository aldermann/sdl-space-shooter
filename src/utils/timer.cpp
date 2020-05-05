//
// Created by Trần Công Việt An on 4/5/20.
//

#include "timer.hpp"

using namespace std::chrono;

void Timer::start() {
  m_StartTime = high_resolution_clock::now();
  m_bRunning = true;
}

void Timer::stop() {
  m_EndTime = high_resolution_clock::now();
  m_bRunning = false;
}

double Timer::elapsedSecondsHR() {
  time_point<high_resolution_clock> endTime;

  if (m_bRunning) {
    endTime = high_resolution_clock::now();
  } else {
    endTime = m_EndTime;
  }

  return duration_cast<duration<double>>(endTime - m_StartTime).count();
}

double Timer::elapsedMilliseconds() {
  time_point<high_resolution_clock> endTime;

  if (m_bRunning) {
    endTime = high_resolution_clock::now();
  } else {
    endTime = m_EndTime;
  }

  return duration_cast<milliseconds>(endTime - m_StartTime).count();
}

void Timer::reset() {
  m_StartTime = high_resolution_clock::now();
}

double Timer::elapsedSeconds() {
  return elapsedMilliseconds() / 1000.0;
}
