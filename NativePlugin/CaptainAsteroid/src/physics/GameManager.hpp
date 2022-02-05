#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "events/PlayGameE.hpp"
#include "events/GameOverE.hpp"
#include "events/VictoryE.hpp"

#include "Define.hpp"

namespace AsteroidsCPP
{
class GameManager : public entityx::Receiver<GameManager>
{
public:
  GameManager(entityx::EntityManager &entityManager,
    entityx::EventManager &eventManager);

  void init();

  Def::GameState gameState() const;

  bool isGameRunning() const;

  void receive(const PlayGameE &playGame);
  void receive(const GameOverE &gameOver);
  void receive(const VictoryE &victory);

private:
  entityx::EntityManager &m_entityManager;

  entityx::EventManager &m_eventManager;

  Def::GameState m_gameState;
};


}// namespace AsteroidsCPP
