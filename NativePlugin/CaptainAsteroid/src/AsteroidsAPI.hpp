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

//#include "Game.hpp"//WIP to remove
#include "Utils.hpp"
#include <cstdint>
namespace AsteroidsCPP
{
class Game;
}

extern "C"
{
  namespace AsteroidsCPP
  {
    // Sample Functions

    ASTEROID_EXPORT const char *HelloWorld();

    ASTEROID_EXPORT AsteroidsCPP::Game *CreateInstance();

    ASTEROID_EXPORT void DeleteInstance(AsteroidsCPP::Game *ptr);

    ASTEROID_EXPORT void Init(AsteroidsCPP::Game *gamePtr, float boundaryV, float boundaryH);

    ASTEROID_EXPORT void Update(AsteroidsCPP::Game *gamePtr, AsteroidsCPP::Utils::KeyState keyState, float deltaTime);

    ASTEROID_EXPORT void GetSpaceShipCoords(AsteroidsCPP::Game *gamePtr, float &x, float &y, float &angle);

    ASTEROID_EXPORT void FillPosEntityList(AsteroidsCPP::Game *gamePtr, float *posEntities, int size, int *nbEntities, AsteroidsCPP::Utils::EntityType entityType);

  }// namespace AsteroidsCPP
}
