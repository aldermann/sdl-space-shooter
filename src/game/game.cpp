//
// Created by Trần Công Việt An on 2/5/20.
//

#include "game.hpp"

#include <iostream>
#include <utils/error/error.hpp>
#include <utils/timer.hpp>
Game::Game(bool debugMode) : objectList(), debugMode(debugMode) {}
Game *Game::instance = nullptr;

Game *Game::createInstance(bool debugMode) {
  if (Game::instance == nullptr) {
    Game::instance = new Game(debugMode);
  }
  return Game::instance;
}

Game *Game::getInstance() {
  if (Game::instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  return Game::instance;
}

void Game::releaseInstance() {
  if (Game::instance == nullptr) {
    throw FatalAppError("Game instance hasn't been initialized yet");
  }
  delete Game::instance;
}

int Game::addObject(GameObject *object) {
  int key = (int) random();
  objectList.insert(std::make_pair(key, object));
  return key;
}

void Game::removeObject(const int key) {
  objectList.erase(key);
}

void Game::render(double time) {
  for (std::pair<int, GameObject *> it : objectList) {
    it.second->render(time, debugMode, debugMode);
  }
}

void Game::checkCollision() {
  for (std::pair<int, GameObject *> it : objectList) {
    for (std::pair<int, GameObject *> it2 : objectList) {
      if (it2.first < it.first) {
        GameObject *ob1 = it.second, *ob2 = it2.second;
        if (ob1->checkCollision(ob2)) {
          std::cout << ob1->position << ' ' << ob2->position << '\n';
          GameObject::handleCollision(ob1, ob2);
        }
      }
    }
  }
}

void Game::waitIndefinitely() {
  while (true) {
    SDL_Event a;
    SDL_WaitEvent(&a);
    if (a.type == SDL_QUIT) {
      return;
    }
  }
}

void Game::loop() {
  Timer timer;
  bool quit = false;
  timer.start();
  long long frame = 0;
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
      double time = timer.elapsedSecondsHRSinceTick();
      timer.tick();
      renderer->clearScreen(Palette::get()->White);
      render(time);
      checkCollision();
      renderer->present();
      ++frame;
    } catch (AppError &error) {
      std::cerr << error;
      if (error.severity == FATAL) {
        exit(-1);
      }
    }
  }
}
