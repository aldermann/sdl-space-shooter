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
  }
  Renderer::createInstance();
  Palette::init();
  Physics::World::init(150);
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

int GameManager::addObject(GameObject *object) {
  /**
   * Add a new object into the game
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  int key = (int) random();
  objectList.insert(std::make_pair(key, object));
  return key;
}
GameObject *GameManager::getObject(const int key) {
  auto item = objectList.find(key);
  if (item == objectList.end()) {
    throw WarningAppError("No such item with key");
  }
  return item->second;
}
GameObject *GameManager::removeObject(const int key) {
  auto item = objectList.find(key);
  if (item == objectList.end()) {
    throw WarningAppError("No such item with key");
  }
  objectList.erase(key);
  return item->second;
}

void GameManager::runRender(double time) {
  for (std::pair<int, GameObject *> it : objectList) {
    it.second->innerRender(time);
  }
}

void GameManager::handleCollision(double time) {
  for (std::pair<int, GameObject *> it : objectList) {
    for (std::pair<int, GameObject *> it2 : objectList) {
      if (it2.first == it.first) {
        break;
      }
      GameObject *ob1 = it.second, *ob2 = it2.second;
      if (ob1->checkCollision(ob2)) {
        ob1->onCollide(ob2);
        ob2->onCollide(ob1);
        GameObject::handleCollision(ob1, ob2, time);
      }
    }
  }
}

void GameManager::handleKeyDown(SDL_Keycode key) {
  for (std::pair<int, GameObject *> it : objectList) {
    it.second->onKeyDown(key);
  }
}

void GameManager::handleKeyUp(SDL_Keycode key) {
  for (std::pair<int, GameObject *> it : objectList) {
    it.second->onKeyUp(key);
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

void GameManager::loop() {
  Timer timer;
  bool quit = false;
  timer.start();
  long long frame = 0;
  double last_frame_duration = 0.1;
  Renderer *renderer = Renderer::getInstance();
  while (!quit) {
    try {
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
      timer.tick();
      renderer->clearScreen(Palette::get()->White);
      runRender(last_frame_duration);
      handleCollision(last_frame_duration);
      renderer->present();
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
