#pragma once

#include "SpaceShip.hpp"
#include "Utils.hpp"

#include <cstdint>
#include <memory>

namespace AsteroidsCPP
{
class Game
{
public:
  Game();

  void update(KeyState state, float deltaTime);

  void getSpaceShip(float &x, float &y);

private:
  std::unique_ptr<SpaceShip> m_ship;
};
}// namespace AsteroidsCPP