//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <object/object.hpp>
#include <unordered_map>
class Game {
  std::unordered_map<int, GameObject*> objectList;
  bool debugMode;

private:
  explicit Game(bool debugMode);
  void render(double time);
  void checkCollision();

public:
  static Game* instance;
  int addObject(GameObject* object);
  void removeObject(int key);
  void loop();
  static Game* getInstance();
  static Game* createInstance(bool);
  static void releaseInstance();
  static void waitIndefinitely();
};
