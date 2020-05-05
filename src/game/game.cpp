//
// Created by Trần Công Việt An on 2/5/20.
//

#include "game.hpp"
#include <iostream>
Game::Game() : objectList() {}

int Game::addObject(GameObject *object) {
  int key = rand();
  objectList.insert(std::make_pair(key, object));
  return key;
}

void Game::removeObject(const int key) {
  objectList.erase(key);
}

void Game::render(double time) {
  for (std::pair<int, GameObject *> it : objectList) {
    it.second->render(time);
  }
}
