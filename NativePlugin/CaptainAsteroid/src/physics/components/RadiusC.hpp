#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
struct RadiusC : public entityx::Component<RadiusC>
{
  RadiusC(float rad) : radius(rad){};

  float radius;
};
}// namespace CaptainAsteroidCPP