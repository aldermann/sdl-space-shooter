#include <SDL.h>

#include <game/objects/wall.hpp>
#include <iostream>

#include "engine/manager/game.hpp"
#include "game/objects/player.hpp"
#include "utils/error/error.hpp"


int main() {
  try {
    auto game = GameManager::createInstance(false);
    GameObject* ball = new Player({100, 300}, 200);
    GameObject* floor = new Floor({600, 700}, 1200, 40, 0);
    game->addObject(ball);
    game->addObject(floor);
    game->loop();
    delete ball;
    delete floor;
    GameManager::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cerr << err << '\n';
  }
}
