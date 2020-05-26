//
// Created by Trần Công Việt An on 2/5/20.
//

#pragma once


#include <unordered_set>

#include "engine/object/object.hpp"
#include "timeline.hpp"
class GameManager {
public:
  friend class GameObject;

private:
  GameManager(const std::vector<TimelineEventCallable>& events, bool debugMode);

  TimelineManager timeline;
  std::unordered_set<GameObject*> objectList;
  std::vector<GameObject*> insertList, deleteList;
  bool debugMode;
  bool quit = false;
  bool restartScheduled = false;
  static GameManager* instance;

  void _registerObject(GameObject* object);
  void _deleteObject(GameObject* object);
  void _registerMultipleObjects(std::vector<GameObject*> objects);
  void _loop();
  void applyObjectListModification();

  void handleKeyDown(SDL_Keycode key);
  void handleKeyUp(SDL_Keycode key);
  void handleDynamic(double time);
  void handleRender();
  void handleCollision(double time);
  void handleExternalEvent();
  void wipeObjects();
  void reloadGameState();

public:
  static GameManager* createInstance(const std::vector<TimelineEventCallable>& events,
                                     bool dbgMode);
  static GameManager* getInstance();
  static void releaseInstance();

  static void registerObject(GameObject* object);
  static void deleteObject(GameObject* object);
  static void registerMultipleObjects(std::vector<GameObject*> objects);
  static void loop();
  static void restart();
};
