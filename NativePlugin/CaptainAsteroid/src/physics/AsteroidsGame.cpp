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

void Game::Update(KeyState keyState, float deltaTime)
{
}
}// namespace AsteroidsCPP
