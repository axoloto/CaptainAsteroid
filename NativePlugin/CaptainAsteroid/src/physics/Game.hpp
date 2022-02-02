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

  void getSpaceShipCoords(float &x, float &y, float &angle);

  void init(float boundaryV, float boundaryH);

private:
  std::unique_ptr<SpaceShip> m_ship;
};
}// namespace AsteroidsCPP