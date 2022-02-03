#pragma once

#include <array>

#include "entityx/System.h"

namespace AsteroidsCPP
{
class SpaceShip
{
public:
  SpaceShip(entityx::EntityManager &entityManager) : m_entityManager(entityManager){};

  void init();
  std::array<float, 3> getPosAndDir();

private:
  entityx::EntityManager &m_entityManager;
};
}// namespace AsteroidsCPP