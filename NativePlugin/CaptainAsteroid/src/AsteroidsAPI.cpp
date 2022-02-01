#include "AsteroidsAPI.hpp"

#include "AsteroidsGame.hpp"

#include <string>

namespace AsteroidsCPP
{

const char *HelloWorld()
{
  return "Hello Captain Asteroid!";
}

AsteroidsCPP::Game *CreateInstance()
{

  return new AsteroidsCPP::Game();
}

void DeleteInstance()
{
}

std::uint32_t AddNumbers(std::uint32_t a, std::uint32_t b)
{
  return a + b;
}

std::uint32_t MultiplyNumbers(std::uint32_t a, std::uint32_t b)
{
  return a * b;
}

void GetSpaceShip(void *gamePtr, float &x, float &y)
{
  if (gamePtr != nullptr)
  {
    x = (float)(rand() % 4);
    y = (float)(rand() % 4);
  }

  x = 10.0f;
  y = 7.0f;
}


/*
ASTEROID_EXPORT void GetSpaceShipCoords(void *gamePtr, float &x, float &y);

    ASTEROID_EXPORT void
      Update(void *gamePtr, AsteroidsCPP::Game::KeyState keyState, float deltaTime)
    {
      static_cast<AsteroidsCPP::Game *>(gamePtr)->Update(keyState, deltaTime);
    }
*/

}// namespace AsteroidsCPP
