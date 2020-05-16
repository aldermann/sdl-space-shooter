//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <unordered_map>

#include "object/object.hpp"
class GameManager {
  std::unordered_map<int, GameObject*> objectList;
  bool debugMode;

private:
  explicit GameManager(bool debugMode);
  void render(double time);
  void manageCollision(double time);

public:
  static GameManager* instance;
  int addObject(GameObject* object);
  void removeObject(int key);
  void loop();
  static GameManager* getInstance();
  static GameManager* createInstance(bool);
  static void releaseInstance();
  static void waitIndefinitely();
};
