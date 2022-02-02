#pragma once

#include "GameManager.hpp"
#include "Utils.hpp"
#include "entities/SpaceShip.hpp"
#include "entities/AsteroidField.hpp"

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

  void getEntitiesCoords(){};

private:
  void createSystems(float boundaryV, float boundaryH);

  entityx::EventManager m_eventManager;

  entityx::EntityManager m_entityManager;

  entityx::SystemManager m_systemManager;

  GameManager m_gameManager;

  SpaceShip m_spaceShip;

  AsteroidField m_asteroidField;
};
}// namespace AsteroidsCPP