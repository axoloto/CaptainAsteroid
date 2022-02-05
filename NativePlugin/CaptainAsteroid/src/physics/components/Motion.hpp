#pragma once

#include "entityx/Entity.h"
namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct Motion : public entityx::Component<Motion>
  {
    Motion(float _vel = 0, float _rot = 0) : vel(_vel), rot(_rot){};

    float vel;
    float rot;// deg
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP