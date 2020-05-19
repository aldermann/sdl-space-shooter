//
// Created by Trần Công Việt An on 17/5/20.
//

#include "player.hpp"

#include <engine/manager/game.hpp>
#include <iostream>

#include "bullet.hpp"
#include "const.hpp"
#include<math.h>

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
    case SDLK_r:
      GameManager::restart();
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
void Player::mouseDown(int posMouseX, int posMouseY)
{
  shoot(posMouseX-position().x, posMouseY-position().y);
}
void Player::shoot(double vecx, double vecy)
{
  double leng = sqrt(vecx*vecx+vecy*vecy);
  vecx/=leng;
  vecy/=leng;
  vecx*=vel;
  vecy*=vel;
  if(vecx>0)
  {
    auto bullet = new Bullet(position() + Geometry::Vector(size + 10, 10), {vecx, vecy});
    GameManager::registerObject(bullet);
  }
  else
  {
    auto bullet = new Bullet(position() - Geometry::Vector(size + 10, 10), {vecx, vecy});
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
