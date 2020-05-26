//
// Created by Trần Công Việt An on 19/5/20.
//

#pragma once


#include <functional>
#include <queue>

typedef std::function<long long int(long long int)> TimelineEventCallable;
typedef std::pair<long long int, TimelineEventCallable> TimelineEvent;

class TimelineManager {
  struct EventComparer {
    bool operator()(const TimelineEvent& a, const TimelineEvent& b);
  };
  std::priority_queue<TimelineEvent, std::vector<TimelineEvent>, EventComparer> eventQueue;
  std::vector<TimelineEvent> scheduledEvent;
  long long currentFrame = 0;


public:
  explicit TimelineManager(std::vector<TimelineEvent> scheduledEvents);
  explicit TimelineManager(const std::vector<TimelineEventCallable>& onStartEvents);
  void reset();
  void schedule(long long int frame, const TimelineEventCallable& event);
  void run();
};
