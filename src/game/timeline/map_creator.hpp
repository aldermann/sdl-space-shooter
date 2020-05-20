//
// Created by Trần Công Việt An on 20/5/20.
//

#pragma once


#include "engine/manager/timeline.hpp"
class MapCreator : public TimelineEvent {
  long long int executeEvent() override;
};
