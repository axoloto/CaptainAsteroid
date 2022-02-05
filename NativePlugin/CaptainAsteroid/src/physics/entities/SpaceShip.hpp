#pragma once

#include <array>

#include "entityx/System.h"

namespace CaptainAsteroidCPP
{
class SpaceShip
{
public:
  SpaceShip(entityx::EntityManager &entityManager) : m_entityManager(entityManager){};

  void init();

  std::array<float, 3> getPosAndDir() const;

private:
  entityx::EntityManager &m_entityManager;
};
}// namespace CaptainAsteroidCPP
