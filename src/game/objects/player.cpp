//
// Created by Trần Công Việt An on 17/5/20.
//

#include "player.hpp"

#include <engine/manager/game.hpp>
#include <iostream>

#include "bullet.hpp"
#include "const.hpp"


Player::Player(const Geometry::Point& position, double speed) : size(30), speed(speed) {
  boundingBox = new BoundingBox::CircleBox(size);
  type = PLAYER;
  dynamic = {position, 20, 0.5};
}

void Player::render() {
  Renderer* renderer = Renderer::getInstance();
  renderer->drawCircle(Geometry::Circle(position(), size), Palette::get()->Red);
}

void Player::onKeyDown(SDL_Keycode key) {
  switch (key) {
    case SDLK_LEFT:
    case SDLK_a:
      dynamic.setHorizontalVelocity(-speed);
      return;
    case SDLK_RIGHT:
    case SDLK_d:
      dynamic.setHorizontalVelocity(speed);
      return;
    case SDLK_j:
      shoot();
      return;
    case SDLK_w:
    case SDLK_UP:
    case SDLK_SPACE:
      jump();
      return;
    default:
      return;
  }
}

void Player::onKeyUp(SDL_Keycode key) {
  switch (key) {
    case SDLK_LEFT:
    case SDLK_a:
    case SDLK_RIGHT:
    case SDLK_d:
      dynamic.setHorizontalVelocity(0);
      return;
    default:
      return;
  }
}

void Player::shoot() {
  int time = SDL_GetTicks();
  if (time > lastShoot + 300) {
    lastShoot = time;
    auto bullet = new PlayerBullet(position() + Geometry::Vector(size + 10, 0), {1000, 0});
    GameManager::registerObject(bullet);
  }
}

void Player::onCollide(GameObject* otherObject) {
  switch (otherObject->type) {
    case FLOOR:
      onAir = false;
      break;
  }
}

void Player::jump() {
  if (!onAir) {
    dynamic.setVerticalVelocity(-speed * 1.4);
    onAir = true;
  }
}
