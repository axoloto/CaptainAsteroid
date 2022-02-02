#include "Game.hpp"

#include "Logging.hpp"

#include "systems/PlayerControlS.hpp"
#include "systems/MovementS.hpp"
#include "systems/CollisionS.hpp"

#include <chrono>
#include <algorithm>
#include <cmath>

namespace AsteroidsCPP
{
Game::Game() : m_eventManager(),
               m_entityManager(m_eventManager),
               m_systemManager(m_entityManager, m_eventManager),
               m_gameManager(m_entityManager, m_eventManager)
{
  Utils::InitializeLogger();

  //m_ship = std::make_unique<SpaceShip>();
}

void Game::init(float boundaryV, float boundaryH)
{
  LOG_INFO("Initializing Plugin Game Engine");
  m_gameManager.init();
  createSystems(boundaryV, boundaryH);
  //m_ship->init(boundaryV, boundaryH);
}

void Game::createSystems(float boundaryV, float boundaryH)
{
  m_systemManager.add<PlayerControlS>();
  m_systemManager.add<MovementS>(boundaryV, boundaryH);
  m_systemManager.add<CollisionS>();
  m_systemManager.configure();
}

void Game::update(Utils::KeyState keyState, float deltaTime)
{
  if (keyState.State != 0)
  {
    m_eventManager.emit<PlayerInputE>(keyState);
  }

  if (m_gameManager.isRunning() && m_gameManager.gameState() == GS_Playing)
  {
    //m_ship->update(keyState, deltaTime);

    m_systemManager.update<PlayerControlS>(deltaTime);
    m_systemManager.update<MovementS>(deltaTime);
    m_systemManager.update<CollisionS>(deltaTime);
  }
}

void Game::getSpaceShipCoords(float &x, float &y, float &rotDeg)
{
  //if (m_ship)
  {
    //   auto coords = m_ship->getCoords();
    //   x = coords[0];
    //   y = coords[1];
    //   rotDeg = coords[2];
  }
}

}// namespace AsteroidsCPP
