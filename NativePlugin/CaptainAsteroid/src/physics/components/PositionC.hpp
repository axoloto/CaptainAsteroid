#pragma once

#include "entityx/Entity.h"

namespace AsteroidsCPP
{
struct PositionC : entityx::Component<PositionC>
{
  PositionC();

  float x, y;
  float angle;
};
}// namespace AsteroidsCPP