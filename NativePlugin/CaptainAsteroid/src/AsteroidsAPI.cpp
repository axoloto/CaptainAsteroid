#include "AsteroidsAPI.hpp"

#include "AsteroidsGame.hpp"

#include <string>

namespace AsteroidsCPP
{

const char *HelloWorld()
{
  return "Hello Captain Asteroid!";
}

std::uint32_t AddNumbers(std::uint32_t a, std::uint32_t b)
{
  return a + b;
}

std::uint32_t MultiplyNumbers(std::uint32_t a, std::uint32_t b)
{
  return 0 * a * b;
}

}// namespace AsteroidsCPP
