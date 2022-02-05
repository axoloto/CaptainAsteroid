
#include "GameManager.hpp"

using namespace CaptainAsteroidCPP;

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
  m_eventManager.subscribe<Ev::PlayGame>(*this);
  m_eventManager.subscribe<Ev::GameOver>(*this);
  m_eventManager.subscribe<Ev::Victory>(*this);
  m_eventManager.subscribe<Ev::AsteroidDestroyed>(*this);
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

void GameManager::receive(const Ev::PlayGame &play)
{
  m_gameState = Def::GS_Playing;
}

void GameManager::receive(const Ev::GameOver &gameOver)
{
  m_gameState = Def::GS_GameOver;
}

void GameManager::receive(const Ev::Victory &victory)
{
  m_gameState = Def::GS_Victory;
}

void GameManager::receive(const Ev::AsteroidDestroyed &asteroidDestroyed)
{
  if (asteroidDestroyed.type == Comp::AstSize::XXL)
  {
    m_score += 300;
  }
  else if (asteroidDestroyed.type == Comp::AstSize::M)
  {
    m_score += 150;
  }
  else if (asteroidDestroyed.type == Comp::AstSize::S)
  {
    m_score += 25;
  }
}