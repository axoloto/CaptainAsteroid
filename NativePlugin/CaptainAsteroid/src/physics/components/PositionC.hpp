#pragma once

#include "entityx/Entity.h"

#include <cmath>

namespace CaptainAsteroidCPP
{
struct PositionC : entityx::Component<PositionC>
{
  PositionC(float _x = 0, float _y = 0, float _angle = 0) : x(_x), y(_y), angle(_angle){};

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
}// namespace CaptainAsteroidCPP