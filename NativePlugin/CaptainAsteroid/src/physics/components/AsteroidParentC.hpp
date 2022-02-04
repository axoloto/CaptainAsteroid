#pragma once

#include "entityx/Entity.h"

namespace AsteroidsCPP
{
struct AsteroidParentC : public entityx::Component<AsteroidParentC>
{
  AsteroidParentC(){};
};
}// namespace AsteroidsCPP