#pragma once

#include "entityx/Entity.h"
namespace AsteroidsCPP
{
struct MotionC : public entityx::Component<MotionC>
{
  MotionC();

  float acc;
  float vel;
  float rot;// deg
};
}// namespace AsteroidsCPP