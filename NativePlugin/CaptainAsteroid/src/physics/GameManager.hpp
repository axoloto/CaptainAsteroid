#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "events/GameOverE.hpp"

namespace AsteroidsCPP
{
enum GameState
{
  GS_Start,
  GS_Playing,
  GS_GameOver,
  GS_Victory,
};

class GameManager : public entityx::Receiver<GameManager>
{
public:
  GameManager(entityx::EntityManager &entityManager,
    entityx::EventManager &eventManager);

  void init();

  GameState gameState() const;

  bool isRunning() const;

  void receive(const GameOverE &gameOver);

private:
  entityx::EntityManager &m_entityManager;

  entityx::EventManager &m_eventManager;

  GameState m_gameState;

  bool m_isRunning;
};


}// namespace AsteroidsCPP
