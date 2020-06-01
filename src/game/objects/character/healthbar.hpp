//
// Created by Trần Công Việt An on 1/6/20.
//

#pragma once


#include <engine/object/object.hpp>
class Healthbar : public GameObject {
public:
  int currentHealth = 5;
  void reduceHealth (int x);
};
