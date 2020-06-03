//
// Created by Trần Công Việt An on 2/5/20.
//

#include "game.hpp"

#include <engine/physics/physics.hpp>
#include <iostream>
#include <utility>
#include <utils/random.hpp>

#include "utils/error/error.hpp"
#include "utils/timer.hpp"

GameManager::GameManager(const std::vector<TimelineEventCallable> &events, bool debugMode)
    : timeline(events), objectList(), debugMode(debugMode) {
  /**
  * Game manager:
  * The manager manager is a singleton (only one instance can exist)
  * It manage various aspect of the manager (renderer rendering loop, fps, manager objects, ...)
  */
}
GameManager *GameManager::instance = nullptr;

GameManager *GameManager::createInstance(const std::vector<TimelineEventCallable> &onStartEvents,
                                         bool dbgMode) {
  /**
  * Create new manager instance
  * @param onStartEvents: events that must be called on game start or game restart
  * @param [bool] debugMode: set to true to draw some additional debugging tool
  */

  if (instance == nullptr) {
    instance = new GameManager(onStartEvents, dbgMode);
    Palette::init();
    Random::initialize();
  }
  instance->reloadGameState();
  return instance;
}

GameManager *GameManager::getInstance() {
  /**
   * Get the current instance
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  if (instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  return instance;
}

void GameManager::releaseInstance() {
  /**
   * Delete the current instance
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  if (instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  instance->wipeObjects();
  Renderer::releaseInstance();
  delete instance;
}

void GameManager::_loop() {
  Timer timer;
  timer.start();
  double last_frame_duration = 0.1;
  while (!quit) {
    if (restartScheduled) {
      reloadGameState();
      continue;
    }
    try {
      timer.tick();
      handleExternalEvent();
      timeline.run();
      handleTick(last_frame_duration);
      handleDynamic(last_frame_duration);
      handleCollision(last_frame_duration);
      handleRender();
      applyObjectListModification();
      last_frame_duration = timer.elapsedSecondsHRSinceTick();
    } catch (AppError &error) {
      std::cerr << error;
      if (error.severity == FATAL) {
        exit(-1);
      }
    }
  }
}

void GameManager::loop() {
  instance->_loop();
}

void GameManager::reloadGameState() {
  restartScheduled = false;
  wipeObjects();
  timeline.reset();
}

void GameManager::restart() {
  instance->restartScheduled = true;
}
void GameManager::handleTick(double duration) {
  for (auto *obj : objectList) {
    obj->tick(duration);
  }
}
