#include "Game.hpp"

#include "Logging.hpp"

#include "systems/PlayerControlS.hpp"
#include "systems/MoveS.hpp"
#include "systems/CollideS.hpp"
#include "systems/FireLaserS.hpp"
#include "systems/ReduceLifeTimeS.hpp"

#include "components/MotionC.hpp"
#include "components/PositionC.hpp"
#include "components/PlayerControlC.hpp"
#include "components/LaserC.hpp"

#include "events/PlayGameE.hpp"

namespace AsteroidsCPP
{
Game::Game() : m_eventManager(),
               m_entityManager(m_eventManager),
               m_systemManager(m_entityManager, m_eventManager),
               m_gameManager(m_entityManager, m_eventManager),
               m_spaceShip(m_entityManager),
               m_asteroidField(m_entityManager),
               m_laserShots(m_entityManager)
{
  Utils::InitializeLogger();
}

void Game::init(float boundaryV, float boundaryH)
{
  LOG_INFO("Initializing Plugin Game Engine");
  m_gameManager.init();
  m_spaceShip.init();
  m_asteroidField.init(30, boundaryV, boundaryH);

  createSystems(boundaryV, boundaryH);

  m_eventManager.emit<PlayGameE>();
}

void Game::createSystems(float boundaryV, float boundaryH)
{
  m_systemManager.add<PlayerControlS>();
  m_systemManager.add<MoveS>(boundaryV, boundaryH);
  m_systemManager.add<CollideS>(m_asteroidField);
  m_systemManager.add<FireLaserS>(m_laserShots);
  m_systemManager.add<ReduceLifeTimeS>(m_laserShots);
  m_systemManager.configure();
}

void Game::update(Utils::KeyState keyState, float deltaTime)
{
  m_eventManager.emit<PlayerInputE>(keyState);

  if (m_gameManager.isRunning() && m_gameManager.gameState() == GS_Playing)
  {
    m_systemManager.update<PlayerControlS>(deltaTime);
    m_systemManager.update<MoveS>(deltaTime);
    m_systemManager.update<CollideS>(deltaTime);
    m_systemManager.update<FireLaserS>(deltaTime);
    m_systemManager.update<ReduceLifeTimeS>(deltaTime);
  }
}

void Game::getSpaceShipCoords(float &x, float &y, float &rotDeg)
{
  auto coordsAndRot = m_spaceShip.getPosAndDir();
  x = coordsAndRot[0];
  y = coordsAndRot[1];
  rotDeg = coordsAndRot[2];
}

void Game::fillPosEntityList(float *posEntities, int size, int *nbEntities, Utils::EntityType entityType)
{
  if (entityType & Utils::EntityType::Asteroid_XXL
      || entityType & Utils::EntityType::Asteroid_M
      || entityType & Utils::EntityType::Asteroid_S)
  {
    m_asteroidField.fillPosEntityList(posEntities, size, nbEntities, entityType);
  }
  else if (entityType & Utils::EntityType::LaserShot)
  {
    m_laserShots.fillPosEntityList(posEntities, size, nbEntities, entityType);
  }
}

}// namespace AsteroidsCPP
