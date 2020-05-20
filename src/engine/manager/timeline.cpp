//
// Created by Trần Công Việt An on 19/5/20.
//

#include "timeline.hpp"

#include <iostream>
TimelineEvent::TimelineEvent(int frame) : frame(frame) {}
long long TimelineEvent::executeEvent() {
  /**
   * Method called upon execution of the event
   *
   * This method will be called upon execution of the event. You will need to override this method
   * for every type of event you want to implement.
   *
   * @return a long long int. If you return a number larger than the current event frame, this event
   * will be rescheduled at that frame. Ignore if you return any number less than or equal to the
   * current frame
   */
  return 0;
}

TimelineEvent::TimelineEvent(const TimelineEvent& other) = default;

bool TimelineEvent::LessComparator::operator()(const TimelineEvent* x, const TimelineEvent* y) {
  return x->frame < y->frame;
}

void TimelineManager::reset() {
  currentFrame = 0;
  while (not eventQueue.empty()) {
    eventQueue.pop();
  }
}

void TimelineManager::schedule(TimelineEvent* event) {
  eventQueue.push(event);
}

void TimelineManager::run() {
  ++currentFrame;
  std::vector<TimelineEvent*> newEvent;
  while (not eventQueue.empty()) {
    TimelineEvent* event = eventQueue.top();
    if (event->frame > currentFrame) {
      break;
    }
    long long nextFrame = event->executeEvent();
    if (nextFrame > currentFrame) {
      event->frame = nextFrame;
      newEvent.push_back(event);
    }
    eventQueue.pop();
  }
  for (TimelineEvent* e : newEvent) {
    eventQueue.push(e);
  }
}
