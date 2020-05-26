//
// Created by Trần Công Việt An on 26/5/20.
//

#include "game.hpp"

void GameManager::handleRender() {
  Renderer *renderer = Renderer::getInstance();
  renderer->clearScreen(Palette::get()->Blue);
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
    if (ob1->boundingBox == nullptr) {
      continue;
    }
    for (GameObject *ob2 : objectList) {
      if (ob2 == ob1) {
        break;
      }
      if (ob2->boundingBox == nullptr) {
        continue;
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
      case SDL_MOUSEBUTTONDOWN:
        int mousePosX, mousePosY;
        SDL_GetMouseState(&mousePosX, &mousePosY);
        handleMouseButtonDown(Geometry::Point(mousePosX, mousePosY));
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

void GameManager::handleMouseButtonDown(const Geometry::Point &p) {
  for (GameObject *ob : objectList) {
    ob->onMouseDown(p);
  }
}
