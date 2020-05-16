#include <SDL.h>

#include <iostream>
#include "utils/error/error.hpp"

#include "game/game.hpp"
#include "render/renderer.hpp"


int main() {
  try {
    auto game = GameManager::createInstance(false);
    auto palette = Palette::get();
    GameObject* ball = GameObject::createRoundObject({200, 200}, 5, 30, palette->Red, 0.4);
    GameObject* wall1 =
            GameObject::createImmovableRectangleObject({600, 100}, 1000, 100, 0, palette->Blue, 0);
    GameObject* wall2 =
            GameObject::createImmovableRectangleObject({600, 700}, 1000, 100, 0, palette->Blue, 0);
    GameObject* wall3 =
            GameObject::createImmovableRectangleObject({100, 400}, 100, 600, 0, palette->Blue, 0);
    GameObject* wall4 =
            GameObject::createImmovableRectangleObject({1100, 400}, 100, 600, 0, palette->Blue, 0);
    game->addObject(wall1);
    game->addObject(wall2);
    game->addObject(wall3);
    game->addObject(wall4);
    game->addObject(ball);
    ball->motion.setVelocity({300, -100});
    ball->motion.setGravity(300);
    game->loop();
    delete ball;
    delete wall1;
    delete wall2;
    delete wall3;
    delete wall4;
    GameManager::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cerr << err << '\n';
  }
}
