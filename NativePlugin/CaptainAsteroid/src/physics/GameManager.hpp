#pragma once

#include "entityx/Event.h"
#include "entityx/Entity.h"

#include "events/PlayGame.hpp"
#include "events/GameOver.hpp"
#include "events/Victory.hpp"
#include "events/AsteroidDestroyed.hpp"

#include "Define.hpp"

namespace CaptainAsteroidCPP
{
class GameManager : public entityx::Receiver<GameManager>
{
public:
  GameManager(entityx::EntityManager &entityManager,
    entityx::EventManager &eventManager);

  void init();

  Def::GameState gameState() const;

  int score() const;

  bool isGameRunning() const;

  void receive(const Ev::PlayGame &playGame);
  void receive(const Ev::GameOver &gameOver);
  void receive(const Ev::Victory &victory);
  void receive(const Ev::AsteroidDestroyed &victory);

private:
  entityx::EntityManager &m_entityManager;

  entityx::EventManager &m_eventManager;

  Def::GameState m_gameState;

  int m_score;
};


}// namespace CaptainAsteroidCPP
