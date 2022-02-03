#pragma once

#include "GameManager.hpp"
#include "Utils.hpp"
#include "entities/SpaceShip.hpp"
#include "entities/AsteroidField.hpp"
#include "entities/LaserShots.hpp"

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

  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType);

private:
  void createSystems(float boundaryV, float boundaryH);

  entityx::EventManager m_eventManager;

  entityx::EntityManager m_entityManager;

  entityx::SystemManager m_systemManager;

  GameManager m_gameManager;

  SpaceShip m_spaceShip;

  AsteroidField m_asteroidField;

  LaserShots m_laserShots;
};
}// namespace AsteroidsCPP