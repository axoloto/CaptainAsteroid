#pragma once

#include "entityx/Entity.h"
namespace CaptainAsteroidCPP
{
struct LifeTimeC : public entityx::Component<LifeTimeC>
{
  LifeTimeC(float _lifeTime) : lifeTime(_lifeTime){};

  float lifeTime;//sec
};
}// namespace CaptainAsteroidCPP