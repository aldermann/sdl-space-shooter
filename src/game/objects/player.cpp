//
// Created by Trần Công Việt An on 17/5/20.
//

#include "player.hpp"

#include <iostream>

#include "bullet.hpp"
#include "const.hpp"
#include "engine/manager/game.hpp"

Player::Player(const Geometry::Point& position, double speed)
    : size(30), speed(speed), texture("assets/ball.png", 2 * size, 2 * size) {
  boundingBox = new BoundingBox::CircleBox(size);
  type = PLAYER;
  dynamic = {position, 20, 0.5};
}

void Player::render() {
  Renderer* renderer = Renderer::getInstance();
  renderer->drawTexture(texture, position(), 0);
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
    case SDLK_w:
    case SDLK_UP:
      dynamic.setVerticalVelocity(-speed);
      return;
    case SDLK_s:
    case SDLK_DOWN:
      dynamic.setVerticalVelocity(speed);
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
      break;
    case SDLK_UP:
    case SDLK_w:
    case SDLK_DOWN:
    case SDLK_s:
      dynamic.setVerticalVelocity(0);
      break;
    default:
      return;
  }
}

void Player::shoot(const Geometry::Point& target, double bulletVelocity) {
  int time = SDL_GetTicks();
  if (time > lastShoot + 300) {
    lastShoot = time;
    Geometry::Vector shootDirection{position(), target};
    shootDirection = shootDirection.normalized();
    Geometry::Point bulletPosition = position() + shootDirection * size * 2;
    auto bullet = new PlayerBullet(bulletPosition, shootDirection * bulletVelocity);
    GameManager::registerObject(bullet);
  }
}

void Player::onMouseDown(const Geometry::Point& p) {
  shoot(p, 1000);
}

void Player::onCollide(GameObject* otherObject) {
  switch (otherObject->type) {
    case FLOOR:
      onAir = false;
      break;
    case ENEMY_BULLET:
      destroy();
      break;
  }
}

void Player::jump() {
  if (!onAir) {
    dynamic.setVerticalVelocity(-speed * 1.4);
    onAir = true;
  }
}
