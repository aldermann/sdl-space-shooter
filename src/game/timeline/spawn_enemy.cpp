//
// Created by Trần Công Việt An on 20/5/20.
//

#include "spawn_enemy.hpp"

#include "engine/manager/game.hpp"
#include "game/objects/character/enemy.hpp"

long long SpawnEnemy(long long frame) {
  if (Enemy::count < 5) {
    auto *enemy = new Enemy({1000, 100}, 50, Palette::get()->Yellow);
    ++Enemy::count;
    GameManager::registerObject(enemy);
  }
  return frame + 200;
}
