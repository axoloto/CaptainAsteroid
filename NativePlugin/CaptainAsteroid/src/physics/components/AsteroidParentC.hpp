#pragma once

#include "entityx/Entity.h"

namespace CaptainAsteroidCPP
{
struct AsteroidParentC : public entityx::Component<AsteroidParentC>
{
  AsteroidParentC(){};
};
}// namespace CaptainAsteroidCPP