#pragma once

#include "GameManager.hpp"
//#include "SpaceShip.hpp"
#include "Utils.hpp"

#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"

#include <cstdint>
#include <memory>

namespace AsteroidsCPP
{
class Game
{
public:
  Game();

  void init(float boundaryV, float boundaryH);

  void update(Utils::KeyState state, float deltaTime);

  void getSpaceShipCoords(float &x, float &y, float &angle);

private:
  void createSystems(float boundaryV, float boundaryH);

  entityx::EventManager m_eventManager;

  entityx::EntityManager m_entityManager;

  entityx::SystemManager m_systemManager;

  GameManager m_gameManager;

  //std::unique_ptr<SpaceShip> m_ship;
};
}// namespace AsteroidsCPP