//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <unordered_set>

#include "engine/object/object.hpp"
#include "timeline.hpp"
class GameManager {
public:
  TimelineManager timeline;

private:
  std::unordered_set<GameObject*> objectList;
  std::vector<GameObject*> insertList, deleteList;
  bool debugMode;
  friend class GameObject;
  bool quit = false;
  static GameManager* instance;

  explicit GameManager(bool debugMode);
  void handleRender();
  void handleCollision(double time);
  void applyObjectListModification();

  void _registerObject(GameObject* object);
  void _deleteObject(GameObject* object);
  void _loop();

  void handleKeyDown(SDL_Keycode key);
  void handleKeyUp(SDL_Keycode key);
  void handleDynamic(double time);
  void handleExternalEvent();

public:
  static void registerObject(GameObject* object);
  static void deleteObject(GameObject* object);
  static void loop();
  static GameManager* getInstance();
  static GameManager* createInstance(bool);
  static void releaseInstance();
  static void waitIndefinitely();
};
