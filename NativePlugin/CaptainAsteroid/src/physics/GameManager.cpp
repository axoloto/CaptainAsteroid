
#include "GameManager.hpp"

#include "events/GameOverE.hpp"

using namespace AsteroidsCPP;

GameManager::GameManager(entityx::EntityManager &entityManager,
  entityx::EventManager &eventManager)
  : m_entityManager(entityManager),
    m_eventManager(eventManager),
    m_gameState(GS_Start),
    m_isRunning(false)
{
}

void GameManager::init()
{
  m_eventManager.subscribe<GameOverE>(*this);
  m_isRunning = true;
}

GameState GameManager::gameState() const
{
  return m_gameState;
}

bool GameManager::isRunning() const
{
  return m_isRunning;
}

void GameManager::receive(const GameOverE &gameOver)
{
  m_gameState = GS_GameOver;

  m_entityManager.reset();
}