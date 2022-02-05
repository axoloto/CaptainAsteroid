#pragma once

#include "entityx/Entity.h"
namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct Laser : public entityx::Component<Laser>
  {
    Laser() : nextShotTimer(0.0f), isFiring(false){};

    const float initVel = 20.0f;
    const float coolDownTime = 0.1f;
    float nextShotTimer;
    bool isFiring;
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP