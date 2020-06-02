//
// Created by Trần Công Việt An on 1/6/20.
//

#pragma once


#include <engine/object/object.hpp>
#include <engine/render/texture.hpp>

class Healthbar : public GameObject {
private:
  Texture heart;
public:
  Healthbar();
  int currentHealth = 5;
  void reduceHealth (int x);
  void render() override;
};
