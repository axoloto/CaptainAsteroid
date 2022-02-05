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

#include "Define.hpp"
#include <cstdint>

namespace AsteroidsCPP
{
class Game;
}

extern "C"
{
  namespace AsteroidsCPP
  {
    // TODO
    ASTEROID_EXPORT AsteroidsCPP::Game *CreateNativeInstance();

    ASTEROID_EXPORT void DeleteNativeInstance(AsteroidsCPP::Game *ptr);

    ASTEROID_EXPORT void Init(AsteroidsCPP::Game *gamePtr, AsteroidsCPP::Def::InitParams initParams);

    ASTEROID_EXPORT void Update(AsteroidsCPP::Game *gamePtr, AsteroidsCPP::Def::KeyState keyState, float deltaTime);

    ASTEROID_EXPORT void GetSpaceShipCoords(AsteroidsCPP::Game *gamePtr, float &x, float &y, float &angle);

    ASTEROID_EXPORT void FillPosEntityList(AsteroidsCPP::Game *gamePtr, float *posEntities, int size, int *nbEntities, AsteroidsCPP::Def::EntityType entityType);

    ASTEROID_EXPORT AsteroidsCPP::Def::GameState CurrentGameState(AsteroidsCPP::Game *gamePtr);

  }// namespace AsteroidsCPP
}
