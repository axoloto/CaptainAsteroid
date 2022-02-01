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

void DeleteInstance(AsteroidsCPP::Game *ptr)
{
  if (ptr)
  {
    LOG_INFO("Removing Asteroids Plugin instance");
    delete ptr;
    ptr = nullptr;
  }
}

std::uint32_t AddNumbers(std::uint32_t a, std::uint32_t b)
{
  return a + b;
}

std::uint32_t MultiplyNumbers(std::uint32_t a, std::uint32_t b)
{
  return a * b;
}

}// namespace AsteroidsCPP
