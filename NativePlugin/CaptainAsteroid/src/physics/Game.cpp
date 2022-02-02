#include "Game.hpp"

#include "Logging.hpp"

#include <chrono>
#include <algorithm>
#include <cmath>

namespace AsteroidsCPP
{
Game::Game()
{
  Utils::InitializeLogger();
  LOG_INFO("Initialize Plugin Game Engine");

  m_ship = std::make_unique<SpaceShip>();
}

void Game::init(float boundaryV, float boundaryH)
{
  m_ship->init(boundaryV, boundaryH);
}

void Game::update(KeyState keyState, float deltaTime)
{
  m_ship->update(keyState, deltaTime);
}

void Game::getSpaceShipCoords(float &x, float &y, float &rotDeg)
{
  if (m_ship)
  {
    auto coords = m_ship->getCoords();
    x = coords[0];
    y = coords[1];
    rotDeg = coords[2];
  }
}

}// namespace AsteroidsCPP
