#include "AsteroidsAPI.hpp"

#include "Game.hpp"
#include "Logging.hpp"

#include <string>

namespace AsteroidsCPP
{

const char *HelloWorld()
{
  return "Hello Captain Asteroid!";
}

AsteroidsCPP::Game *CreateInstance()
{
  LOG_INFO("Creating an instance of Asteroids Plugin");
  return new AsteroidsCPP::Game();
}

void DeleteInstance(AsteroidsCPP::Game *instance)
{
  if (instance)
  {
    LOG_INFO("Removing Asteroids Plugin instance");
    delete instance;
    instance = nullptr;
  }
}

void Init(AsteroidsCPP::Game *gamePtr, float boundaryV, float boundaryH)
{
  if (gamePtr) gamePtr->init(boundaryV, boundaryH);
}

void GetSpaceShipCoords(AsteroidsCPP::Game *gamePtr, float &x, float &y, float &angle)
{
  if (gamePtr) gamePtr->getSpaceShipCoords(x, y, angle);
}

void Update(AsteroidsCPP::Game *gamePtr, AsteroidsCPP::Utils::KeyState keyState, float deltaTime)
{
  if (gamePtr) gamePtr->update(keyState, deltaTime);
}

}// namespace AsteroidsCPP
