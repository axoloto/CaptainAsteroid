
#include "GameManager.hpp"

using namespace AsteroidsCPP;

GameManager::GameManager(entityx::EntityManager &entityManager,
  entityx::EventManager &eventManager)
  : m_entityManager(entityManager),
    m_eventManager(eventManager),
    m_gameState(Def::GS_Start),
    m_score(0)
{
}

void GameManager::init()
{
  m_eventManager.subscribe<PlayGameE>(*this);
  m_eventManager.subscribe<GameOverE>(*this);
  m_eventManager.subscribe<VictoryE>(*this);
  m_eventManager.subscribe<AsteroidDestroyedE>(*this);
}

Def::GameState GameManager::gameState() const
{
  return m_gameState;
}

int GameManager::score() const
{
  return m_score;
}

bool GameManager::isGameRunning() const
{
  return m_gameState == Def::GS_Playing;
}

void GameManager::receive(const PlayGameE &start)
{
  m_gameState = Def::GS_Playing;//WIP
}

void GameManager::receive(const GameOverE &gameOver)
{
  m_gameState = Def::GS_GameOver;
}

void GameManager::receive(const VictoryE &victory)
{
  m_gameState = Def::GS_Victory;
}

void GameManager::receive(const AsteroidDestroyedE &asteroidDestroyed)
{
  if (asteroidDestroyed.type == Type::XXL)
  {
    m_score += 300;
  }
  else if (asteroidDestroyed.type == Type::M)
  {
    m_score += 150;
  }
  else if (asteroidDestroyed.type == Type::S)
  {
    m_score += 25;
  }
}