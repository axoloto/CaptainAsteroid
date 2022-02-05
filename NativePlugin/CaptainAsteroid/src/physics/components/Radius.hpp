#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct Radius : public entityx::Component<Radius>
  {
    Radius(float rad) : radius(rad){};

    float radius;
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP