#pragma once

#ifdef _WIN32
#ifdef NOEXPORT
#define ASTEROID_EXPORT
#else
#define ASTEROID_EXPORT __declspec(dllexport)
#endif
#else
#define ASTEROID_EXPORT
#endif

#include "AsteroidsGame.hpp"
#include <cstdint>

extern "C"
{
  namespace AsteroidsCPP
  {
    // Sample Functions

    ASTEROID_EXPORT const char *HelloWorld();

    ASTEROID_EXPORT AsteroidsCPP::Game *CreateInstance();
    ASTEROID_EXPORT void DeleteInstance(AsteroidsCPP::Game *ptr);

    ASTEROID_EXPORT std::uint32_t AddNumbers(std::uint32_t a, std::uint32_t b);

    ASTEROID_EXPORT std::uint32_t MultiplyNumbers(std::uint32_t a, std::uint32_t b);

    ASTEROID_EXPORT void GetSpaceShip(AsteroidsCPP::Game *gamePtr, float &x, float &y)
    {
      if (gamePtr) gamePtr->getSpaceShip(x, y);
    }

    ASTEROID_EXPORT void
      Update(AsteroidsCPP::Game *gamePtr, AsteroidsCPP::KeyState keyState, float deltaTime)
    {
      if (gamePtr) gamePtr->update(keyState, deltaTime);
    }
  }// namespace AsteroidsCPP
}
