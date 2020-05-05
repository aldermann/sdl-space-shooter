#include <SDL.h>

#include <algorithm>
#include <iostream>
#include <utils/timer.hpp>

#include "game/game.hpp"
#include "render/renderer.hpp"
#include "utils/error/sdl_error.hpp"


int main() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Ball emulator",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        640,
                                        480,
                                        SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    return 1;
  }


  Renderer *renderer = Renderer::createInstance(window);
  Color backgroundColor(0xffffff);
  Game game;

  Geometry::Point position(50, 350);

  Color ballColor(0xff00ff);
  GameObject ball = GameObject::createRoundObject(position, 1, 20, ballColor);
  game.addObject(&ball);
  ball.motion.setGravity(200);
  ball.motion.setVelocity({100, -400});

  //  int fps = 5;
  //  int milisecond_per_frame = 1000 / fps;

  Timer timer;

  bool quit = false;
  timer.start();
  while (!quit) {
    try {
      SDL_Event e;
      SDL_PollEvent(&e);
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        }
      }
      double time = timer.elapsedSecondsHR();
      timer.reset();
      renderer->clearScreen(backgroundColor);
      game.render(time);
      renderer->present();
      SDL_Delay(20);
    } catch (AppError &error) {
      std::cerr << error;
      if (error.severity == FATAL) {
        exit(-1);
      }
    }
  }
  Renderer::releaseInstance();
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
