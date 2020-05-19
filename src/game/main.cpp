#include <SDL.h>

#include <engine/physics/physics.hpp>
#include <game/objects/wall.hpp>
#include <game/objects/map.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include "engine/manager/game.hpp"
#include "game/objects/player.hpp"
#include "utils/error/error.hpp"

const int SCREEN_W = 1280;
const int SCREEN_H = 640;

const int MAP_WH = 32;

void render_Map();

int main() {
  try {
    auto game = GameManager::createInstance(false);
    Renderer::createInstance("My game", SCREEN_W, SCREEN_H);

    std::ifstream inp;
    inp.open("bin/map_file.txt");
    std::vector <GameObject*> map;
    if (!inp.is_open()) std::cout << "Unable to open map file";

    int colorMap;
    for (int i = 1; i <= SCREEN_H / MAP_WH; ++i)
      for (int j = 1; j <= SCREEN_W / MAP_WH; ++j)
      {
        inp >> colorMap;
        Color col;
        //if (colorMap == 0) col = Color(255, 0, 0, 255);
        //if (colorMap == 1) col = Color(0, 0, 0, 255);
        //if (colorMap == 2) col = Color(255, 255, 255, 255);
        //col = Color(255, 0, 0, 255);
        
        //map.push_back(new Map({(j - 0.5) * MAP_WH, (i - 0.5) * MAP_WH }, MAP_WH, MAP_WH, 0, col));
        map.push_back(new Wall({(j - 0.5) * MAP_WH, (i - 0.5) * MAP_WH }, MAP_WH, MAP_WH, 0)); 
      }

    for (auto it : map)
      game->_registerObject(it);
    game->loop();
    for (auto it : map) delete it;
    inp.close();
    
    // Physics::World::init(200);
    // GameObject* ball = new Player({100, 300}, 200);
    // GameObject* floor = new Floor({600, 700}, 1200, 40, 0);
    // GameObject* wall1 = new Wall({1180, 350}, 40, 700, 0);
    // GameObject* wall2 = new Wall({20, 350}, 40, 700, 0);
    // game->_registerObject(ball);
    // game->_registerObject(floor);
    // game->_registerObject(wall1);
    // game->_registerObject(wall2);
    // game->loop();  
    // delete ball;
    // delete floor;

    GameManager::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cerr << err << '\n';
  }
}
// make && ./bin/sdl-ball