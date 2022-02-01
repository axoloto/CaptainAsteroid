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
}

void Game::update(KeyState keyState, float deltaTime)
{
}

void Game::getSpaceShip(float &x, float &y)
{
  x = (float)(rand() % 4);
  y = (float)(6.888f);
}

}// namespace AsteroidsCPP
