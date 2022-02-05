#include "Game.hpp"

#include "Logging.hpp"

#include "systems/PlayerControlS.hpp"
#include "systems/MoveS.hpp"
#include "systems/CollideS.hpp"
#include "systems/FireLaserS.hpp"
#include "systems/ReduceLifeTimeS.hpp"
#include "systems/SplitAsteroidS.hpp"
#include "systems/RemoveDeadS.hpp"

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
  LOG_INFO("Game Created");
}

void Game::init(Def::InitParams initParams)
{
  m_gameManager.init();

  m_spaceShip.init();

  m_asteroidField.init(initParams);

  createSystems(initParams.boundaryDomainV, initParams.boundaryDomainH);

  m_eventManager.emit<PlayGameE>();

  LOG_INFO("Game Initialized");
}

void Game::createSystems(float boundaryV, float boundaryH)
{
  m_systemManager.add<PlayerControlS>();
  m_systemManager.add<MoveS>(boundaryV, boundaryH);
  m_systemManager.add<CollideS>();
  m_systemManager.add<FireLaserS>(m_laserShots);
  m_systemManager.add<ReduceLifeTimeS>();
  m_systemManager.add<SplitAsteroidS>(m_asteroidField);
  m_systemManager.add<RemoveDeadS>(m_asteroidField, m_laserShots);
  m_systemManager.configure();

  LOG_INFO("DOD Systems Initialized");
}

void Game::update(Def::KeyState keyState, float deltaTime)
{
  m_eventManager.emit<PlayerInputE>(keyState);

  if (m_gameManager.isGameRunning())
  {
    m_systemManager.update<PlayerControlS>(deltaTime);
    m_systemManager.update<MoveS>(deltaTime);
    m_systemManager.update<CollideS>(deltaTime);
    m_systemManager.update<FireLaserS>(deltaTime);
    m_systemManager.update<ReduceLifeTimeS>(deltaTime);
    m_systemManager.update<SplitAsteroidS>(deltaTime);
    m_systemManager.update<RemoveDeadS>(deltaTime);
  }
}

void Game::getSpaceShipCoords(float &x, float &y, float &angle) const
{
  const std::array<float, 3> coordsAndRot = m_spaceShip.getPosAndDir();
  x = coordsAndRot[0];
  y = coordsAndRot[1];
  angle = coordsAndRot[2];
}

void Game::fillPosEntityList(float *posEntities, int size, int *nbEntities, Def::EntityType entityType) const
{
  if (entityType & Def::EntityType::Asteroid_XXL
      || entityType & Def::EntityType::Asteroid_M
      || entityType & Def::EntityType::Asteroid_S)
  {
    m_asteroidField.fillPosEntityList(posEntities, size, nbEntities, entityType);
  }
  else if (entityType & Def::EntityType::LaserShot)
  {
    m_laserShots.fillPosEntityList(posEntities, size, nbEntities, entityType);
  }
}

}// namespace AsteroidsCPP
