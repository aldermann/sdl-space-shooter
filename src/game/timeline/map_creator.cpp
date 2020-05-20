//
// Created by Trần Công Việt An on 20/5/20.
//

#include "map_creator.hpp"
#include "game/objects/wall.hpp"
#include "engine/manager/game.hpp"

const int MAP_WH = 32; 

enum MapRectangle
{
  leftX, 
  leftY, 
  rightX, 
  rightY,
  color
};

MapCreator::MapCreator(int frame) : TimelineEvent(frame){}

long long int MapCreator::executeEvent() {
  int rectCoordinate[8][5] = {  0, 14, 19, 17, 1,
                                20, 14, 39, 17, 2,
                                4, 11, 6, 11, 1,
                                7, 9, 9, 9, 1,
                                29, 10, 31, 10, 2,
                                31, 11, 34, 11, 2,
                                11, 7, 19, 7, 2,
                                20, 7, 28, 7, 1};
                                
    std::vector <GameObject*> floors;
    for (int i = 0; i < 8; ++i)
    {
      double posX = rectCoordinate[i][leftX] * MAP_WH;
      double posY = rectCoordinate[i][leftY] * MAP_WH;

      double width = (rectCoordinate[i][rightX] - rectCoordinate[i][leftX] + 1) * MAP_WH;
      double height = (rectCoordinate[i][rightY] - rectCoordinate[i][leftY] + 1) * MAP_WH;

      double centerX = posX + width / 2;
      double centerY = posY + height / 2; 
      
      Color col;
      if (rectCoordinate[i][color] == 1) col = Color(0, 0, 0, 255);
      else col = Color(255, 255, 255, 255);

      floors.push_back(new Floor({centerX, centerY}, width, height, 0, col));
      
    }
    for (auto floor : floors) 
      GameManager::registerObject(floor);


  return 0;
}
