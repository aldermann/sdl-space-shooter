//
// Created by Trần Công Việt An on 26/5/20.
//

#include <utils/error/error.hpp>

#include "game.hpp"

void GameManager::_registerObject(GameObject *object) {
  /**
   * Add a new object into the game
   * Will throw a FatalAppError if the manager instance hasn't been initialized yet
   */
  insertList.push_back(object);
}

void GameManager::_registerMultipleObjects(std::vector<GameObject *> objects) {
  insertList.reserve(insertList.size() + objects.size());
  insertList.insert(insertList.end(), objects.begin(), objects.end());
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
void GameManager::registerObject(GameObject *object) {
  instance->_registerObject(object);
}

void GameManager::registerMultipleObjects(std::vector<GameObject *> objects) {
  instance->_registerMultipleObjects(std::move(objects));
}

void GameManager::deleteObject(GameObject *object) {
  instance->_deleteObject(object);
}

void GameManager::wipeObjects() {
  for (auto *object : objectList) {
    delete object;
  }
  objectList.clear();
}


