
#include "GameManager.hpp"

using namespace AsteroidsCPP;

GameManager::GameManager(entityx::EntityManager &entityManager,
  entityx::EventManager &eventManager)
  : m_entityManager(entityManager),
    m_eventManager(eventManager),
    m_gameState(Def::GS_Start)
{
}

void GameManager::init()
{
  m_eventManager.subscribe<PlayGameE>(*this);
  m_eventManager.subscribe<GameOverE>(*this);
  m_eventManager.subscribe<VictoryE>(*this);
}

Def::GameState GameManager::gameState() const
{
  return m_gameState;
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