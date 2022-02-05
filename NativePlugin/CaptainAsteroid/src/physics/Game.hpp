#pragma once

#include "GameManager.hpp"
#include "Define.hpp"
#include "Define.hpp"
#include "entities/SpaceShip.hpp"
#include "entities/AsteroidField.hpp"
#include "entities/LaserShots.hpp"

#include "entityx/Event.h"
#include "entityx/Entity.h"
#include "entityx/System.h"

#include <cstdint>
#include <memory>

namespace AsteroidsCPP
{
class Game
{
public:
  Game();

  void init(Def::InitParams initParams);

  void update(Def::KeyState state, float deltaTime);

  // Helper function for specific access to Space Ship coords
  void getSpaceShipCoords(float &x, float &y, float &angle) const;

  // Generic access to any entities in the game (SpaceShip, Asteroids and LaserShots)
  void fillPosEntityList(float *posEntities, int size, int *nbEntities, Def::EntityType entityType) const;

  // Game status StartMenu / Playing / Victory / GameOver
  Def::GameState currentGameState() const;

  // Current game score
  std::int32_t currentScore() const;

  // Current number of remaining asteroids
  std::int32_t currentNbAsteroids() const;

private:
  // Creating DOD pipeline
  void createSystems(float boundaryV, float boundaryH);

  // Data-Oriented-Design Pipeline (DOD)
  // Based on top of wonderful entityx library
  // https://github.com/alecthomas/entityx
  entityx::EventManager m_eventManager;
  entityx::EntityManager m_entityManager;
  entityx::SystemManager m_systemManager;

  // Game Manager ruling the show
  GameManager m_gameManager;

  // Access helpers to Game Entities
  // They don't properly own the entities
  // But they can access them, create them
  // and remove them from the entity pool
  //
  // Captain Asteroid, the player
  SpaceShip m_spaceShip;
  // Field of asteroids of different sizes (XXL, M, S)
  AsteroidField m_asteroidField;
  // All current laser shots in the universe!
  LaserShots m_laserShots;
};
}// namespace AsteroidsCPP