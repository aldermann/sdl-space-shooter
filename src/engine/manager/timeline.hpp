//
// Created by Trần Công Việt An on 19/5/20.
//

#pragma once


#include <queue>

class TimelineEvent {
  /**
   * Represent a single event on a timeline
   *
   * @property frame: The frame number that this event is scheduled to execute
   */
  friend class TimelineManager;
  class LessComparator {
  public:
    bool operator()(const TimelineEvent* x, const TimelineEvent* y);
  };

public:
  long long frame = 0;
  explicit TimelineEvent(int frame);
  virtual ~TimelineEvent();
  TimelineEvent(const TimelineEvent& other);
  virtual long long executeEvent();
};

class TimelineManager {
  std::priority_queue<TimelineEvent*, std::vector<TimelineEvent*>, TimelineEvent::LessComparator>
          eventQueue;
  long long currentFrame = 0;


public:
  void reset();
  void schedule(TimelineEvent* event);
  void run();
};
