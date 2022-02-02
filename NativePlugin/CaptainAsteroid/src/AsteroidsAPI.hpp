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

#include "Game.hpp"//WIP to remove
#include <cstdint>

extern "C"
{
  namespace AsteroidsCPP
  {
    // Sample Functions

    ASTEROID_EXPORT const char *HelloWorld();

    ASTEROID_EXPORT AsteroidsCPP::Game *CreateInstance();
    ASTEROID_EXPORT void DeleteInstance(AsteroidsCPP::Game *ptr);

    ASTEROID_EXPORT void Init(AsteroidsCPP::Game *gamePtr, float boundaryV, float boundaryH)
    {
      if (gamePtr) gamePtr->init(boundaryV, boundaryH);
    }

    ASTEROID_EXPORT void GetSpaceShipCoords(AsteroidsCPP::Game *gamePtr, float &x, float &y, float &angle)
    {
      if (gamePtr) gamePtr->getSpaceShipCoords(x, y, angle);
    }

    ASTEROID_EXPORT void
      Update(AsteroidsCPP::Game *gamePtr, AsteroidsCPP::KeyState keyState, float deltaTime)
    {
      if (gamePtr) gamePtr->update(keyState, deltaTime);
    }
  }// namespace AsteroidsCPP
}
