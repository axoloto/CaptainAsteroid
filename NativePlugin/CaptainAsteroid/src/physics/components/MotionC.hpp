#pragma once

#include "entityx/Entity.h"
namespace AsteroidsCPP
{
struct MotionC : public entityx::Component<MotionC>
{
  MotionC(float vel = 0, float rot = 0);

  float vel;
  float rot;// deg
};
}// namespace AsteroidsCPP