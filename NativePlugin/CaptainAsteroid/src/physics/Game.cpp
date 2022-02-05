#include "Game.hpp"

#include "Logging.hpp"

#include "systems/PlayerControl.hpp"
#include "systems/Move.hpp"
#include "systems/Collide.hpp"
#include "systems/FireLaser.hpp"
#include "systems/ReduceLifeTime.hpp"
#include "systems/SplitAsteroid.hpp"
#include "systems/RemoveDead.hpp"

#include "components/Motion.hpp"
#include "components/Position.hpp"
#include "components/PlayerControl.hpp"
#include "components/Laser.hpp"

#include "events/PlayGame.hpp"

namespace CaptainAsteroidCPP
{
Game::Game() : m_eventManager(),
               m_entityManager(m_eventManager),
               m_systemManager(m_entityManager, m_eventManager),
               m_gameManager(m_entityManager, m_eventManager),
               m_spaceShip(m_entityManager),
               m_asteroidField(m_entityManager, m_eventManager),
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

  m_eventManager.emit<Ev::PlayGame>();

  LOG_INFO("Game Initialized");
}

void Game::createSystems(float boundaryV, float boundaryH)
{
  m_systemManager.add<Sys::PlayerControl>();
  m_systemManager.add<Sys::Move>(boundaryV, boundaryH);
  m_systemManager.add<Sys::Collide>();
  m_systemManager.add<Sys::FireLaser>(m_laserShots);
  m_systemManager.add<Sys::ReduceLifeTime>();
  m_systemManager.add<Sys::SplitAsteroid>(m_asteroidField);
  m_systemManager.add<Sys::RemoveDead>(m_asteroidField, m_laserShots);
  m_systemManager.configure();

  LOG_INFO("DOD Systems Initialized");
}

void Game::update(Def::KeyState keyState, float deltaTime)
{
  m_eventManager.emit<Ev::PlayerInput>(keyState);

  if (m_gameManager.isGameRunning())
  {
    m_systemManager.update<Sys::PlayerControl>(deltaTime);
    m_systemManager.update<Sys::Move>(deltaTime);
    m_systemManager.update<Sys::Collide>(deltaTime);
    m_systemManager.update<Sys::FireLaser>(deltaTime);
    m_systemManager.update<Sys::ReduceLifeTime>(deltaTime);
    m_systemManager.update<Sys::SplitAsteroid>(deltaTime);
    m_systemManager.update<Sys::RemoveDead>(deltaTime);
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

Def::GameState Game::currentGameState() const
{
  return m_gameManager.gameState();
}

std::int32_t Game::currentScore() const
{
  return m_gameManager.score();
}

std::int32_t Game::currentNbAsteroids() const
{
  return m_asteroidField.totalNbAsteroids();
}

}// namespace CaptainAsteroidCPP
