#pragma once

#include "entityx/System.h"

namespace AsteroidsCPP
{
class MovementS : public entityx::System<MovementS>
{
public:
  MovementS(float boundaryV, float boundaryH) : m_boundaryV(boundaryV), m_boundaryH(boundaryH){};

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  float m_boundaryV, m_boundaryH;
};
}// namespace AsteroidsCPP