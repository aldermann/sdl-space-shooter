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
#include "game/objects/background.hpp"

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

Background* buildBackground(const char* path, int leftX, int leftY, int rightX, int rightY) {
  double posX = leftX * MAP_WH;
  double posY = leftY * MAP_WH;

  double outputW = (rightX - leftX + 1) * MAP_WH;
  double outputH = (rightY - leftY + 1) * MAP_WH;

  double centerX = posX + outputW / 2;
  double centerY = posY + outputH / 2;

  return new Background(path, {centerX, centerY}, outputW, outputH);
}

void setupMap() {
  Color black = Palette::get()->Black, white = Palette::get()->White;

  std::vector<GameObject*> objects = {// buildFloor(0, 14, 19, 17, white),
                                      // buildFloor(20, 14, 39, 17, black),
                                      // buildFloor(4, 11, 6, 11, white),
                                      // buildFloor(7, 9, 9, 9, white),
                                      // buildFloor(29, 10, 31, 10, black),
                                      // buildFloor(31, 11, 34, 11, black),
                                      // buildFloor(11, 7, 19, 7, black),
                                      // buildFloor(20, 7, 28, 7, white),
                                      buildFloor(-1, -1, 40, -1, white),
                                      buildFloor(-1, 0, -1, 17, white),
                                      buildFloor(-1, 18, 40, 18, black),
                                      buildFloor(40, 0, 40, 17, black),
                                      buildBackground("assets/space-1500x844.jpg", 0, 0, 39, 17),
                                      buildBackground("assets/heart-256x256.png", 38, 0, 39, 1),
                                      buildBackground("assets/heart-256x256.png", 36, 0, 37, 1),
                                      buildBackground("assets/heart-256x256.png", 34, 0, 35, 1),
                                      buildBackground("assets/heart-256x256.png", 32, 0, 33, 1),
                                      buildBackground("assets/heart-256x256.png", 30, 0, 31, 1),
                                      };
  GameManager::registerMultipleObjects(objects);
}

void setupCharacters() {
  GameManager::registerObject(new Player({100, 300}, 200));
}

long long int GameSetup(long long) {
  setupCharacters();
  setupMap();
  return 0;
}
