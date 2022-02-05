#include "CaptainAsteroidAPI.hpp"

#include "Game.hpp"
#include "Logging.hpp"

#include <string>

namespace CaptainAsteroidCPP
{
CaptainAsteroidCPP::Game *CreateNativeInstance()
{
  CaptainAsteroidCPP::Game *gamePtr = nullptr;
  try
  {
    LOG_INFO("Creating Asteroids Plugin instance");
    gamePtr = new CaptainAsteroidCPP::Game();
  }
  catch (const std::exception &e)
  {
    if (gamePtr) delete gamePtr;
    gamePtr = nullptr;
    LOG_ERROR(" Run-time error while creating native instance, error type : {}", e.what());
  }
  catch (...)
  {
    if (gamePtr) delete gamePtr;
    gamePtr = nullptr;
    LOG_ERROR(" Run-time error while creating native instance, error type unknown");
  }
  return gamePtr;
}

void DeleteNativeInstance(CaptainAsteroidCPP::Game *gamePtr)
{
  try
  {
    if (gamePtr)
    {
      LOG_INFO("Removing Asteroids Plugin instance");
      delete gamePtr;
      gamePtr = nullptr;
    }
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while updating plugin, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while updating plugin, error type unknown");
  }
}

void Init(CaptainAsteroidCPP::Game *gamePtr, CaptainAsteroidCPP::Def::InitParams initParams)
{
  try
  {
    if (gamePtr) gamePtr->init(initParams);
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while updating plugin, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while updating plugin, error type unknown");
  }
}

void Update(CaptainAsteroidCPP::Game *gamePtr, CaptainAsteroidCPP::Def::KeyState keyState, float deltaTime)
{
  try
  {
    if (gamePtr) gamePtr->update(keyState, deltaTime);
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while updating plugin, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while updating plugin, error type unknown");
  }
}

void GetSpaceShipCoords(CaptainAsteroidCPP::Game *gamePtr, float &x, float &y, float &angle)
{
  try
  {
    if (gamePtr) gamePtr->getSpaceShipCoords(x, y, angle);
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while getting space ship coords, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while getting space ship coords, error type unknown");
  }
}

void FillPosEntityList(CaptainAsteroidCPP::Game *gamePtr, float *posEntities, int size, int *nbEntities, CaptainAsteroidCPP::Def::EntityType entityType)
{
  try
  {
    if (gamePtr) gamePtr->fillPosEntityList(posEntities, size, nbEntities, entityType);
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type unknown");
  }
}

CaptainAsteroidCPP::Def::GameState CurrentGameState(CaptainAsteroidCPP::Game *gamePtr)
{
  auto currentGameState = CaptainAsteroidCPP::Def::GameState::GS_GameOver;
  try
  {
    if (gamePtr) currentGameState = gamePtr->currentGameState();
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type unknown");
  }
  return currentGameState;
}

std::int32_t CurrentScore(CaptainAsteroidCPP::Game *gamePtr)
{
  std::int32_t currentScore = 0;
  try
  {
    if (gamePtr) currentScore = gamePtr->currentScore();
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type unknown");
  }
  return currentScore;
}

std::int32_t CurrentNbAsteroids(CaptainAsteroidCPP::Game *gamePtr)
{
  std::int32_t currentNbAsteroids = 0;
  try
  {
    if (gamePtr) currentNbAsteroids = gamePtr->currentNbAsteroids();
  }
  catch (const std::exception &e)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type : {}", e.what());
  }
  catch (...)
  {
    LOG_ERROR(" Run-time error while filling pos entity list, error type unknown");
  }
  return currentNbAsteroids;
}

}// namespace CaptainAsteroidCPP
