//
// Created by Trần Công Việt An on 2/5/20.
//

#include "game.hpp"

#include <iostream>

#include "utils/error/error.hpp"
#include "utils/timer.hpp"
GameManager::GameManager(bool debugMode) : objectList(), debugMode(debugMode) {
  /// Game manager:
  /// The game manager is a singleton (only one instance can exist)
  /// It manage various aspect of the game (renderer rendering loop, fps, game objects, ...)
}
GameManager *GameManager::instance = nullptr;

GameManager *GameManager::createInstance(bool debugMode) {
  ///
  /// new game instance
  /// @param [bool] debugMode: set to true to draw some additional debugging tool
  ///
  if (GameManager::instance == nullptr) {
    GameManager::instance = new GameManager(debugMode);
  }
  Renderer::createInstance();
  Palette::init();
  return GameManager::instance;
}

GameManager *GameManager::getInstance() {
  /**
   * Get the current instance
   * Will throw a FatalAppError if the game instance hasn't been initialized yet
   */
  if (GameManager::instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  return GameManager::instance;
}

void GameManager::releaseInstance() {
  /**
   * Delete the current instance
   * Will throw a FatalAppError if the game instance hasn't been initialized yet
   */
  if (GameManager::instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  Renderer::releaseInstance();
  delete GameManager::instance;
}

int GameManager::addObject(GameObject *object) {
  /**
   * Add a
   * Will throw a FatalAppError if the game instance hasn't been initialized yet
   */
  int key = (int) random();
  objectList.insert(std::make_pair(key, object));
  return key;
}

void GameManager::removeObject(const int key) {
  objectList.erase(key);
}

void GameManager::render(double time) {
  for (std::pair<int, GameObject *> it : objectList) {
    it.second->render(time, debugMode, debugMode);
  }
}

void GameManager::manageCollision(double time) {
  for (std::pair<int, GameObject *> it : objectList) {
    for (std::pair<int, GameObject *> it2 : objectList) {
      if (it2.first == it.first) {
        break;
      }
      GameObject *ob1 = it.second, *ob2 = it2.second;
      if (ob1->checkCollision(ob2)) {
        GameObject::handleBounce(ob1, ob2, time);
      }
    }
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
      SDL_PollEvent(&e);
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }
      timer.tick();
      renderer->clearScreen(Palette::get()->White);
      render(last_frame_duration);
      manageCollision(last_frame_duration);
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
