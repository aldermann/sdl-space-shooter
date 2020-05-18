//
// Created by Trần Công Việt An on 17/5/20.
//

#include "player.hpp"

#include <iostream>

Player::Player(const Geometry::Point& position, double speed) : size(30), speed(speed) {
  boundingBox = new BoundingBox::CircleBox(size);
  type = "player";
  dynamic = {position, 5, 0.5};
}

void Player::render(const Geometry::Point& position) {
  Renderer* renderer = Renderer::getInstance();
  renderer->drawCircle(Geometry::Circle(position, size), Palette::get()->Red);
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

void Player::onCollide(GameObject* otherObject) {
  if (otherObject->type == "floor") {
    onAir = false;
  }
}

void Player::jump() {
  if (!onAir) {
    dynamic.setVerticalVelocity(-speed * 1.4);
    onAir = true;
  }
}
