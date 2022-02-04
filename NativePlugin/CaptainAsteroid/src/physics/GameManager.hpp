#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "events/PlayGameE.hpp"
#include "events/GameOverE.hpp"
#include "events/VictoryE.hpp"

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

  bool isGameRunning() const;

  void receive(const PlayGameE &playGame);
  void receive(const GameOverE &gameOver);
  void receive(const VictoryE &victory);

private:
  entityx::EntityManager &m_entityManager;

  entityx::EventManager &m_eventManager;

  GameState m_gameState;
};


}// namespace AsteroidsCPP
