#include <SDL.h>

#include <engine/physics/physics.hpp>
#include <game/objects/wall.hpp>
#include <iostream>
#include <vector>

#include "engine/manager/game.hpp"
#include "engine/render/color.hpp"
#include "game/objects/const.hpp"
#include "game/objects/player.hpp"
#include "timeline/map_creator.hpp"
#include "timeline/spawn_enemy.hpp"
#include "utils/error/error.hpp"


int main() {
  try {
    auto* game = GameManager::createInstance(false);
    Renderer::createInstance("My game", SCREEN_W, SCREEN_H);
    Physics::World::init(200);
    GameObject* ball = new Player({100, 300}, 200);
    GameManager::registerObject(ball);
    //GameObject* floor = new Floor({600, 700}, 1200, 40, 0, Palette::get()->Violet);
    //GameManager::registerObject(floor);
    game->timeline.schedule(new MapCreator(0));
    game->timeline.schedule(new SpawnEnemyEvent(1));
    GameManager::loop();
    delete ball;

    GameManager::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cerr << err << '\n';
  }
}
// make && ./bin/sdl-ball