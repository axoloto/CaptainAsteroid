#include "MoveS.hpp"
using namespace AsteroidsCPP;

#include "utils.hpp"
#include "components/MotionC.hpp"
#include "components/PositionC.hpp"

void MoveS::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  MotionC::Handle motion;
  PositionC::Handle position;
  for (entityx::Entity entity : entities.entities_with_components(motion, position))
  {
    float x = position->x;
    float y = position->y;
    float angleDeg = position->angle;

    angleDeg += motion->rot;
    x += std::cos(angleDeg * Utils::PI / 180.0f) * motion->vel * (float)dt;
    y += std::sin(angleDeg * Utils::PI / 180.0f) * motion->vel * (float)dt;

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