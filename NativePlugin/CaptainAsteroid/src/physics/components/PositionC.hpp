#pragma once

#include "entityx/Entity.h"

namespace AsteroidsCPP
{
struct PositionC : entityx::Component<PositionC>
{
  PositionC(float x = 0, float y = 0, float angle = 0);

  float x, y;
  float angle;
};
}// namespace AsteroidsCPP