#pragma once

#include "entityx/Entity.h"

#include <cmath>

namespace AsteroidsCPP
{
struct PositionC : entityx::Component<PositionC>
{
  PositionC(float x = 0, float y = 0, float angle = 0);

  float dist2(const PositionC &other) const
  {
    return pow(other.x - x, 2) + pow(other.y - y, 2);
  }

  float dist(const PositionC &other) const
  {
    return sqrt(dist2(other));
  }

  float x, y;
  float angle;
};
}// namespace AsteroidsCPP