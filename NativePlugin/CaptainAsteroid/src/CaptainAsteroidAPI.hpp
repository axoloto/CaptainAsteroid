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
    // First call to be made to generate the game
    ASTEROID_EXPORT CaptainAsteroidCPP::Game *CreateNativeInstance();

    // Last call to be made to delete the game
    ASTEROID_EXPORT void DeleteNativeInstance(CaptainAsteroidCPP::Game *ptr);

    // Initialize step with input parameters from Unity
    ASTEROID_EXPORT void Init(CaptainAsteroidCPP::Game *gamePtr, CaptainAsteroidCPP::Def::InitParams initParams);

    // Update step with dt and player inputs
    ASTEROID_EXPORT void Update(CaptainAsteroidCPP::Game *gamePtr, CaptainAsteroidCPP::Def::KeyState keyState, float deltaTime);

    // Specific function to access Space ship coordinates
    ASTEROID_EXPORT void GetSpaceShipCoords(CaptainAsteroidCPP::Game *gamePtr, float &x, float &y, float &angle);

    // Generic access to all NPC entities coords (Asteroids of all sorts and Laser Shots)
    // Buffer must be allocated on managed side (Unity), this side is only filling it up to the number of entities
    ASTEROID_EXPORT void FillPosEntityList(CaptainAsteroidCPP::Game *gamePtr, float *posEntities, int size, int *nbEntities, CaptainAsteroidCPP::Def::EntityType entityType);

    // Can be Start / Playing / Victory / GameOver
    ASTEROID_EXPORT CaptainAsteroidCPP::Def::GameState CurrentGameState(CaptainAsteroidCPP::Game *gamePtr);

    // Each asteroid type has a different value
    ASTEROID_EXPORT std::int32_t CurrentScore(CaptainAsteroidCPP::Game *gamePtr);

    // Make it to zero and you win
    ASTEROID_EXPORT std::int32_t CurrentNbAsteroids(CaptainAsteroidCPP::Game *gamePtr);
  }// namespace CaptainAsteroidCPP
}
