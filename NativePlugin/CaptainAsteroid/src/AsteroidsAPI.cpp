#include "AsteroidsAPI.hpp"

#include "AsteroidsGame.hpp"
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

}// namespace AsteroidsCPP
