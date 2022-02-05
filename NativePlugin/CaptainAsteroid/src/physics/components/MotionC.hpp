#pragma once

#include "entityx/Entity.h"
namespace CaptainAsteroidCPP
{
struct MotionC : public entityx::Component<MotionC>
{
  MotionC(float _vel = 0, float _rot = 0) : vel(_vel), rot(_rot){};

  float vel;
  float rot;// deg
};
}// namespace CaptainAsteroidCPP