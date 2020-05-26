//
// Created by Trần Công Việt An on 20/5/20.
//
#include "map_creator.hpp"

#include <SDL_image.h>

#include <iostream>

#include "engine/manager/game.hpp"
#include "engine/render/texture.hpp"
#include "game/objects/const.hpp"
#include "game/objects/wall.hpp"

const int MAP_WH = 32;

MapCreator::MapCreator(int frame) : TimelineEvent(frame) {}

struct Rect {
  int leftX, leftY, rightX, rightY, color;
};

long long int MapCreator::executeEvent() {
  /* Background Loading */
  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if ((IMG_Init(imgFlags) & imgFlags) == 0) {
    std::cout << IMG_GetError() << '\n';
    return -1;
  }


  /* Map Loading */
  std::vector<Rect> rectCoordinate = {{0, 14, 19, 17, 1},
                                      {20, 14, 39, 17, 2},
                                      {4, 11, 6, 11, 1},
                                      {7, 9, 9, 9, 1},
                                      {29, 10, 31, 10, 2},
                                      {31, 11, 34, 11, 2},
                                      {11, 7, 19, 7, 2},
                                      {20, 7, 28, 7, 1}};


  for (auto& i : rectCoordinate) {
    double posX = i.leftX * MAP_WH;
    double posY = i.leftY * MAP_WH;

    double width = (i.rightX - i.leftX + 1) * MAP_WH;
    double height = (i.rightY - i.leftY + 1) * MAP_WH;

    double centerX = posX + width / 2;
    double centerY = posY + height / 2;

    Color col;
    if (i.color == 1) {
      col = Palette::get()->Black;
    } else {
      col = Palette::get()->White;
    }

    GameManager::registerObject(new Floor({centerX, centerY}, width, height, 0, col));
  }
  return 0;
}
