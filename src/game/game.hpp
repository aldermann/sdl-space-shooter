//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <object/object.hpp>
#include <unordered_map>
class Game {
  std::unordered_map<int, GameObject *> objectList;

public:
  Game();
  int addObject(GameObject *object);
  void removeObject(const int key);
  void render(double time);
};
