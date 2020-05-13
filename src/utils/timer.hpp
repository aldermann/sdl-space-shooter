#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>

class Timer {
public:
  void start();
  void stop();
  double elapsedMilliseconds();
  double elapsedSecondsHR();
  void tick();
  double elapsedSecondsHRSinceTick();
  double elapsedMillisecondsSinceTick();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime, lastTick;
  bool running = false;
};
