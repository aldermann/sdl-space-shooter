#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>

class Timer {
public:
  void start();
  void stop();
  double elapsedMilliseconds();
  double elapsedSeconds();
  double elapsedSecondsHR();
  void reset();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
  bool m_bRunning = false;
};
