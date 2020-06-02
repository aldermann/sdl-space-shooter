//
// Created by Trần Công Việt An on 20/5/20.
//
#include "game_setup.hpp"

#include <SDL_image.h>

#include <game/objects/player.hpp>
#include <iostream>

#include "engine/manager/game.hpp"
#include "engine/render/texture.hpp"
#include "game/objects/const.hpp"
#include "game/objects/wall.hpp"
#include "game/objects/score.hpp"

const int MAP_WH = 32;

Floor* buildFloor(int leftX, int leftY, int rightX, int rightY, const Color& col) {
  double posX = leftX * MAP_WH;
  double posY = leftY * MAP_WH;

  double width = (rightX - leftX + 1) * MAP_WH;
  double height = (rightY - leftY + 1) * MAP_WH;

  double centerX = posX + width / 2;
  double centerY = posY + height / 2;

  return new Floor({centerX, centerY}, width, height, 0, col);
}

void setupMap() {
  Color black = Palette::get()->Black, white = Palette::get()->White;

  std::vector<GameObject*> objects = {buildFloor(0, 14, 19, 17, white),
                                      buildFloor(20, 14, 39, 17, black),
                                      buildFloor(4, 11, 6, 11, white),
                                      buildFloor(7, 9, 9, 9, white),
                                      buildFloor(29, 10, 31, 10, black),
                                      buildFloor(31, 11, 34, 11, black),
                                      buildFloor(11, 7, 19, 7, black),
                                      buildFloor(20, 7, 28, 7, white)};
  GameManager::registerMultipleObjects(objects);
  GameManager::registerObject(new Score());
}

void setupCharacters() {
  GameManager::registerObject(new Player({100, 300}, 200));
}

long long int GameSetup(long long) {
  setupCharacters();
  setupMap();
  return 0;
}
