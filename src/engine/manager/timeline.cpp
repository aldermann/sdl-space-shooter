//
// Created by Trần Công Việt An on 19/5/20.
//

#include "timeline.hpp"

#include <utility>


void TimelineManager::reset() {
  currentFrame = 0;
  while (not eventQueue.empty()) {
    eventQueue.pop();
  }
  for (const TimelineEvent& e : scheduledEvent) {
    eventQueue.push(e);
  }
}

void TimelineManager::run() {
  ++currentFrame;
  std::vector<TimelineEvent> newEvent;
  while (not eventQueue.empty()) {
    TimelineEvent event = eventQueue.top();
    if (event.first > currentFrame) {
      break;
    }
    long long nextFrame = event.second(currentFrame);
    if (nextFrame > currentFrame) {
      newEvent.emplace_back(nextFrame, event.second);
    }
    eventQueue.pop();
  }
  for (const TimelineEvent& e : newEvent) {
    eventQueue.push(e);
  }
}

void TimelineManager::schedule(long long int frame, const TimelineEventCallable& event) {
  eventQueue.push(std::pair(frame, event));
}
TimelineManager::TimelineManager(std::vector<TimelineEvent> scheduledEvents)
    : scheduledEvent(std::move(scheduledEvents)) {}
TimelineManager::TimelineManager(const std::vector<TimelineEventCallable>& onStartEvents) {
  for (const auto& event : onStartEvents) {
    scheduledEvent.emplace_back(0, event);
  }
}

bool TimelineManager::EventComparer::operator()(const TimelineEvent& a, const TimelineEvent& b) {
  return a.first < b.first;
}
