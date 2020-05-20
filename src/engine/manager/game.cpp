//
// Created by Trần Công Việt An on 2/5/20.
//

#include "game.hpp"

#include <engine/physics/physics.hpp>
#include <iostream>

#include "utils/error/error.hpp"
#include "utils/timer.hpp"
GameManager::GameManager(bool debugMode) : objectList(), debugMode(debugMode) {
  /// Game manager:
  /// The manager manager is a singleton (only one instance can exist)
  /// It manage various aspect of the manager (renderer rendering loop, fps, manager objects, ...)
}
GameManager *GameManager::instance = nullptr;

GameManager *GameManager::createInstance(bool debugMode) {
  ///
  /// new manager instance
  /// @param [bool] debugMode: set to true to draw some additional debugging tool
  ///
  if (GameManager::instance == nullptr) {
    GameManager::instance = new GameManager(debugMode);
    Palette::init();
  }
  return GameManager::instance;
}

GameManager *GameManager::getInstance() {
  /**
   * Get the current instance
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  if (GameManager::instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  return GameManager::instance;
}

void GameManager::releaseInstance() {
  /**
   * Delete the current instance
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  if (GameManager::instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  Renderer::releaseInstance();
  delete GameManager::instance;
}

void GameManager::_registerObject(GameObject *object) {
  /**
   * Add a new object into the game
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  insertList.push_back(object);
}

void GameManager::_deleteObject(GameObject *object) {
  auto item = objectList.find(object);
  if (item == objectList.end()) {
    throw WarningAppError("No such item");
  }
  deleteList.push_back(object);
}

void GameManager::applyObjectListModification() {
  for (GameObject *ptr : insertList) {
    objectList.insert(ptr);
  }
  insertList.clear();
  for (GameObject *ptr : deleteList) {
    objectList.erase(ptr);
    delete ptr;
  }
  deleteList.clear();
}

void GameManager::handleRender() {
  Renderer *renderer = Renderer::getInstance();
  renderer->clearScreen(Palette::get()->White);
  for (GameObject *it : objectList) {
    it->innerRender();
  }
  renderer->present();
}

void GameManager::handleDynamic(double time) {
  for (GameObject *it : objectList) {
    it->dynamic.advance(time);
  }
}

void GameManager::handleCollision(double time) {
  for (GameObject *ob1 : objectList) {
    for (GameObject *ob2 : objectList) {
      if (ob2 == ob1) {
        break;
      }
      GameObject::handleCollision(ob1, ob2, time);
    }
  }
}

void GameManager::handleExternalEvent() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        handleKeyDown(e.key.keysym.sym);
        break;
      case SDL_KEYUP:
        handleKeyUp(e.key.keysym.sym);
        break;
    }
  }
}

void GameManager::handleKeyDown(SDL_Keycode key) {
  for (GameObject *ob : objectList) {
    ob->onKeyDown(key);
  }
}

void GameManager::handleKeyUp(SDL_Keycode key) {
  for (GameObject *ob : objectList) {
    ob->onKeyUp(key);
  }
}
void GameManager::waitIndefinitely() {
  while (true) {
    SDL_Event a;
    SDL_WaitEvent(&a);
    if (a.type == SDL_QUIT) {
      return;
    }
  }
}

void GameManager::_loop() {
  Timer timer;
  timer.start();
  long long frame = 0;
  double last_frame_duration = 0.1;
  while (!quit) {
    try {
      timer.tick();
      handleExternalEvent();
      timeline.run();
      handleDynamic(last_frame_duration);
      handleCollision(last_frame_duration);
      handleRender();
      applyObjectListModification();
      last_frame_duration = timer.elapsedSecondsHRSinceTick();
      ++frame;
    } catch (AppError &error) {
      std::cerr << error;
      if (error.severity == FATAL) {
        exit(-1);
      }
    }
  }
}

void GameManager::registerObject(GameObject *object) {
  instance->_registerObject(object);
}

void GameManager::deleteObject(GameObject *object) {
  instance->_deleteObject(object);
}

void GameManager::loop() {
  instance->_loop();
}
