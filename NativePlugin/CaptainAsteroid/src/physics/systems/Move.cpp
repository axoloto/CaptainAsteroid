#include "Move.hpp"

#include "Define.hpp"

#include "components/Motion.hpp"
#include "components/Position.hpp"

using namespace CaptainAsteroidCPP::Sys;

void Move::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  Comp::Motion::Handle motion;
  Comp::Position::Handle position;
  for (entityx::Entity entity : entities.entities_with_components(motion, position))
  {
    float x = position->x;
    float y = position->y;
    float angleDeg = position->angle;

    x += std::cos(angleDeg * Def::PI / 180.0f) * motion->vel * (float)dt;
    y += std::sin(angleDeg * Def::PI / 180.0f) * motion->vel * (float)dt;

    if (x > m_boundaryH || x < -m_boundaryH)
    {
      x = std::max(-m_boundaryH, std::min(x, m_boundaryH));
      x *= -1.0f;
    }
    if (y > m_boundaryV || y < -m_boundaryV)
    {
      y = std::max(-m_boundaryV, std::min(y, m_boundaryV));
      y *= -1.0f;
    }

    position->x = x;
    position->y = y;
    position->angle = angleDeg;
  }
}