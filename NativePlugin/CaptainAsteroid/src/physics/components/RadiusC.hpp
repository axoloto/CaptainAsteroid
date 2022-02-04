#pragma once

#include "entityx/Entity.h"

namespace AsteroidsCPP
{
struct RadiusC : public entityx::Component<RadiusC>
{
  RadiusC(float rad) : radius(rad){};

  float radius;
};
}// namespace AsteroidsCPP