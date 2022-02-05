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

namespace CaptainAsteroidCPP
{
class Game;
}

extern "C"
{
  namespace CaptainAsteroidCPP
  {
    // TODO
    ASTEROID_EXPORT CaptainAsteroidCPP::Game *CreateNativeInstance();

    ASTEROID_EXPORT void DeleteNativeInstance(CaptainAsteroidCPP::Game *ptr);

    ASTEROID_EXPORT void Init(CaptainAsteroidCPP::Game *gamePtr, CaptainAsteroidCPP::Def::InitParams initParams);

    ASTEROID_EXPORT void Update(CaptainAsteroidCPP::Game *gamePtr, CaptainAsteroidCPP::Def::KeyState keyState, float deltaTime);

    ASTEROID_EXPORT void GetSpaceShipCoords(CaptainAsteroidCPP::Game *gamePtr, float &x, float &y, float &angle);

    ASTEROID_EXPORT void FillPosEntityList(CaptainAsteroidCPP::Game *gamePtr, float *posEntities, int size, int *nbEntities, CaptainAsteroidCPP::Def::EntityType entityType);

    ASTEROID_EXPORT CaptainAsteroidCPP::Def::GameState CurrentGameState(CaptainAsteroidCPP::Game *gamePtr);

    ASTEROID_EXPORT std::int32_t CurrentScore(CaptainAsteroidCPP::Game *gamePtr);

    ASTEROID_EXPORT std::int32_t CurrentNbAsteroids(CaptainAsteroidCPP::Game *gamePtr);
  }// namespace CaptainAsteroidCPP
}
