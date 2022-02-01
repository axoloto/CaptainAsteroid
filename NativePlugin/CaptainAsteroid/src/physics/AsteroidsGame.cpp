#include "AsteroidsGame.hpp"

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

void Game::update(KeyState keyState, float deltaTime)
{
  m_ship->update(keyState, deltaTime);
}

void Game::getSpaceShip(float &x, float &y)
{
  x = (float)(rand() % 4);
  y = (float)(6.888f);

  if (m_ship)
  {
    auto coords = m_ship->getCoords();
    x = coords.first;
    y = coords.second;
  }
}

}// namespace AsteroidsCPP
