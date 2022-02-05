#pragma once

#include "entityx/System.h"

namespace CaptainAsteroidCPP
{
class MoveS : public entityx::System<MoveS>
{
public:
  MoveS(float boundaryV, float boundaryH) : m_boundaryV(boundaryV), m_boundaryH(boundaryH){};

  void update(entityx::EntityManager &entities,
    entityx::EventManager &events,
    double dt);

private:
  float m_boundaryV, m_boundaryH;
};
}// namespace CaptainAsteroidCPP