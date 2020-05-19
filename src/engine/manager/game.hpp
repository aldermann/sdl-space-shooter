//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <unordered_set>

#include "engine/object/object.hpp"
class GameManager {
private:
  std::unordered_set<GameObject*> objectList;
  std::vector<GameObject*> insertList, deleteList;
  bool debugMode;
  friend class GameObject;
  bool quit = false;

  explicit GameManager(bool debugMode);
  void handleRender();
  void handleCollision(double time);
  void applyObjectListModification();

public:
  static GameManager* instance;
  void _registerObject(GameObject* object);
  static void registerObject(GameObject* object);
  void _deleteObject(GameObject* ptr);
  static void deleteObject(GameObject* object);
  void loop();
  static GameManager* getInstance();
  static GameManager* createInstance(bool);
  static void releaseInstance();
  static void waitIndefinitely();
  void handleKeyDown(SDL_Keycode key);
  void handleKeyUp(SDL_Keycode key);
  void handleDynamic(double time);
  void handleEvent();
};
