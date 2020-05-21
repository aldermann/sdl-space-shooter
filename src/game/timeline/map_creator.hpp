//
// Created by Trần Công Việt An on 20/5/20.
//

#pragma once


#include "engine/manager/timeline.hpp"
class MapCreator : public TimelineEvent {
  public:
    explicit MapCreator (int frame);
    long long int executeEvent() override;
};
