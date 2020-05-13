#include <SDL.h>

#include <iostream>
#include <utils/error/error.hpp>

#include "game/game.hpp"
#include "render/renderer.hpp"


int main() {
  try {
    auto game = Game::createInstance(true);
    Renderer::createInstance();
    Palette* palette = Palette::init();
    GameObject ball = GameObject::createRoundObject({200, 200}, 5, 30, palette->Red);
    GameObject ball2 = GameObject::createRoundObject({400, 300}, 5, 30, palette->Red);
    GameObject ball3 = GameObject::createRoundObject({400, 600}, 5, 30, palette->Red);
    //    GameObject ball4 = GameObject::createRoundObject({590, 200}, 5, 30, palette->Red);
    GameObject wall1 =
            GameObject::createImmovableRectangleObject({600, 100}, 1000, 100, 0, palette->Blue);
    GameObject wall2 =
            GameObject::createImmovableRectangleObject({600, 700}, 1000, 100, 0, palette->Blue);
    GameObject wall3 =
            GameObject::createImmovableRectangleObject({100, 400}, 100, 600, 0, palette->Blue);
    GameObject wall4 =
            GameObject::createImmovableRectangleObject({1100, 400}, 100, 600, 0, palette->Blue);
    game->addObject(&wall1);
    game->addObject(&wall2);
    game->addObject(&wall3);
    game->addObject(&wall4);
    game->addObject(&ball);
    game->addObject(&ball2);
    game->addObject(&ball3);
    ball.motion.setVelocity({150, -5});
    ball2.motion.setVelocity({0, 50});
    ball3.motion.setVelocity({0, -50});
    //    ball4.motion.setVelocity({-100, 0});
    game->loop();
    Game::releaseInstance();
    Renderer::releaseInstance();
    SDL_Quit();
  } catch (const AppError& err) {
    std::cout << err << '\n';
  }
}
