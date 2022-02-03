#pragma once

#include <string>

namespace AsteroidsCPP
{
namespace Utils
{
  enum EntityType : std::uint32_t
  {
    Asteroid_XXL = 1 << 0,
    Asteroid_M = 1 << 1,
    Asteroid_S = 1 << 2,
    LaserShot = 1 << 3,
  };

  struct KeyState
  {
    enum class Keys : std::uint32_t
    {
      Left = 1 << 0,
      Right = 1 << 1,
      Up = 1 << 2,
      Down = 1 << 3,
      Space = 1 << 4,
    };


    std::uint32_t State;

    inline bool pressed(Keys key) const
    {
      return (State & (std::uint32_t)key) != 0;
    }
  };

  constexpr float PI = 3.14159274101257324219;

  const std::string GetSrcDir();
  const std::string GetInstallDir();
  const std::string GetVersions();
  const std::string FloatToStr(float val, size_t precision = 10);
}// namespace Utils
}// namespace AsteroidsCPP
