//
// Created by Trần Công Việt An on 17/5/20.
//

#pragma once


#include <engine/object/object.hpp>


class Player : public GameObject {
private:
  double size, speed;
  bool onAir = false;
  void jump();

public:
  Player(const Geometry::Point& position, double speed);
  void render(const Geometry::Point& position) override;
  void onKeyDown(SDL_Keycode key) override;
  void onKeyUp(SDL_Keycode key) override;
  void onCollide(GameObject* otherObject) override;
  void shoot();
};
