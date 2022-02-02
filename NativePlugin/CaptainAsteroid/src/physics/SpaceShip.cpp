#include "SpaceShip.hpp"

#include "Utils.hpp"

#include <algorithm>
#include <cmath>

using namespace AsteroidsCPP;

void SpaceShip::update(KeyState keyState, float deltaTime)
{
  if (keyState.pressed(KeyState::Keys::Down))
  {
    m_thrust -= THRUST_COEFF;
  }
  if (keyState.pressed(KeyState::Keys::Up))
  {
    m_thrust += THRUST_COEFF;
  }
  m_thrust *= FRICTION_COEFF;

  m_rotDeg = 0.0f;
  if (keyState.pressed(KeyState::Keys::Left))
  {
    m_angleDeg += ANGLE_COEFF;
    m_rotDeg = ANGLE_COEFF;
  }
  if (keyState.pressed(KeyState::Keys::Right))
  {
    m_angleDeg -= ANGLE_COEFF;
    m_rotDeg = -ANGLE_COEFF;
  }

  m_vel += std::max(0.0f, std::min(m_thrust * deltaTime, MAX_SPEED));
  m_vel *= FRICTION_COEFF;

  m_x += std::cos(m_angleDeg * Utils::PI / 180.0f) * m_vel * deltaTime;
  m_y += std::sin(m_angleDeg * Utils::PI / 180.0f) * m_vel * deltaTime;
}
