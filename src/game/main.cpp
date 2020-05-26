#include <SDL.h>

#include <iostream>

#include "engine/manager/game.hpp"
#include "engine/physics/physics.hpp"
#include "engine/render/color.hpp"
#include "game/objects/const.hpp"
#include "game/objects/wall.hpp"
#include "timeline/game_setup.hpp"
#include "timeline/spawn_enemy.hpp"
#include "utils/error/error.hpp"


int main() {
  try {
    /* Create an onStartEvents vector that contain event that should be called every time the game start
     * aka events that setup the game. Pass it to GameManager createInstance
     */
    std::vector<TimelineEventCallable> onStartEvents{&GameSetup, &SpawnEnemy};
    GameManager::createInstance(onStartEvents, false);
    Renderer::createInstance("My game", SCREEN_W, SCREEN_H);
    Physics::World::init(200);
    GameManager::loop();
    GameManager::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cerr << err << '\n';
  }
}
// make && ./bin/sdl-ball