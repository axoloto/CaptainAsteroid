#pragma once

#include "entityx/Entity.h"
namespace CaptainAsteroidCPP
{
namespace Comp
{
  struct LifeTime : public entityx::Component<LifeTime>
  {
    LifeTime(float _lifeTime) : lifeTime(_lifeTime){};

    float lifeTime;//sec
  };
}// namespace Comp
}// namespace CaptainAsteroidCPP