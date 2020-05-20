//
// Created by Trần Công Việt An on 20/5/20.
//

#pragma once


#include "engine/manager/timeline.hpp"

class SpawnEnemyEvent : public TimelineEvent {
public:
  explicit SpawnEnemyEvent(int frame);
  long long executeEvent() override;
};
