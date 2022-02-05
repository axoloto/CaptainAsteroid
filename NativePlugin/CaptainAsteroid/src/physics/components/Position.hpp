#pragma once

#include "entityx/Entity.h"

#include <cmath>

namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct Position : entityx::Component<Position>
  {
    Position(float _x = 0, float _y = 0, float _angle = 0) : x(_x), y(_y), angle(_angle){};

    float dist2(const Position &other) const
    {
      return pow(other.x - x, 2) + pow(other.y - y, 2);
    }

    float dist(const Position &other) const
    {
      return sqrt(dist2(other));
    }

    float x, y;
    float angle;
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP