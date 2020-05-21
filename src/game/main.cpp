#include <SDL.h>

#include <engine/physics/physics.hpp>
#include <game/objects/wall.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "timeline/map_creator.hpp"
#include "timeline/spawn_enemy.hpp"
#include "engine/manager/game.hpp"
#include "game/objects/player.hpp"
#include "utils/error/error.hpp"
#include "engine/render/color.hpp"

const int SCREEN_W = 1280;
const int SCREEN_H = 576;

int main() {
  try {
    auto game = GameManager::createInstance(false);
    Renderer::createInstance("My game", SCREEN_W, SCREEN_H);
    Physics::World::init(200);
    GameObject* ball = new Player({100, 300}, 200);
    // GameObject* floor = new Floor({600, 700}, 1200, 40, 0);
    // GameObject* wall1 = new Wall({1180, 350}, 40, 700, 0);
    // GameObject* wall2 = new Wall({20, 350}, 40, 700, 0);
    GameManager::registerObject(ball);
    // GameManager::registerObject(floor);
    // GameManager::registerObject(wall1);
    // GameManager::registerObject(wall2);
    game->timeline.schedule(new MapCreator(0));
    game->timeline.schedule(new SpawnEnemyEvent(1));
    GameManager::loop();
    delete ball;
    // delete floor;

    //for (int i = 0; i < (int)floors.size(); ++i) delete floors[i];

    GameManager::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cerr << err << '\n';
  }
}
// make && ./bin/sdl-ball