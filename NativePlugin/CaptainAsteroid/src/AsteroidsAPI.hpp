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
    ASTEROID_EXPORT void DeleteInstance();

    ASTEROID_EXPORT std::uint32_t AddNumbers(std::uint32_t a, std::uint32_t b);

    ASTEROID_EXPORT std::uint32_t MultiplyNumbers(std::uint32_t a, std::uint32_t b);

    ASTEROID_EXPORT void GetSpaceShip(void *gamePtr, float &x, float &y);

    ASTEROID_EXPORT void
      Update(void *gamePtr, AsteroidsCPP::Game::KeyState keyState, float deltaTime)
    {
      static_cast<AsteroidsCPP::Game *>(gamePtr)->Update(keyState, deltaTime);
    }
  }// namespace AsteroidsCPP
}
