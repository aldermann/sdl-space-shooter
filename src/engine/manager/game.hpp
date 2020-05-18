//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <unordered_map>

#include "engine/object/object.hpp"
class GameManager {
  std::unordered_map<int, GameObject*> objectList;
  bool debugMode;
  friend class GameObject;

private:
  explicit GameManager(bool debugMode);
  void runRender(double time);
  void handleCollision(double time);

public:
  static GameManager* instance;
  int addObject(GameObject* object);
  GameObject* removeObject(int key);
  GameObject* getObject(int key);
  void loop();
  static GameManager* getInstance();
  static GameManager* createInstance(bool);
  static void releaseInstance();
  static void waitIndefinitely();
  void handleKeyDown(SDL_Keycode key);
  void handleKeyUp(SDL_Keycode key);
};
