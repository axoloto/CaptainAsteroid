#pragma once

#include <array>
#include <memory>

namespace AsteroidsCPP
{
constexpr float MAX_SPEED = 0.05f;
constexpr float THRUST_COEFF = 1.0f;
constexpr float ANGLE_COEFF = 0.7f;
constexpr float FRICTION_COEFF = 0.99f;

struct KeyState
{
  enum class Keys : std::uint32_t
  {
    Left = 1 << 0,
    Right = 1 << 1,
    Up = 1 << 2,
    Down = 1 << 3,
    Space = 1 << 4,
  };

  std::uint32_t State;

  inline bool pressed(Keys key) const
  {
    return (State & (std::uint32_t)key) != 0;
  }
};

class SpaceShip
{
public:
  SpaceShip() : m_x(0.0f), m_y(0.0f), m_vel(0.0f), m_thrust(0.0f), m_angleDeg(0.0f), m_rotDeg(0.0f){};
  ~SpaceShip() = default;

  std::array<float, 3> getCoords() const { return { m_x, m_y, m_rotDeg }; }

  void update(KeyState keyState, float deltaTime);

private:
  float m_x, m_y;
  float m_thrust;
  float m_vel;
  float m_angleDeg;
  float m_rotDeg;
};
}// namespace AsteroidsCPP