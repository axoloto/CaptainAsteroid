#include "ControlByPlayer.hpp"

#include "components/Motion.hpp"
#include "components/Laser.hpp"
#include "components/PlayerControl.hpp"
#include "components/Position.hpp"

#include <algorithm>
#include <cmath>

using namespace CaptainAsteroidCPP::Sys;

ControlByPlayer::ControlByPlayer(){};

void ControlByPlayer::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  constexpr float maxSpeed = 6.0f;
  constexpr float thrustCoeff = 8.0f;
  constexpr float angleCoeff = 210.0f;
  constexpr float frictionCoeff = 0.995f;

  Comp::Laser::Handle laser;
  Comp::Motion::Handle motion;
  Comp::Position::Handle position;
  Comp::PlayerControl::Handle playerControl;
  for (entityx::Entity entity : entities.entities_with_components(playerControl, motion, laser, position))
  {
    float acc = 0.0f;
    if (m_keyState.pressed(Def::KeyState::Keys::Down))
    {
      acc = -thrustCoeff;
      position->angle = motion->rot;
    }
    if (m_keyState.pressed(Def::KeyState::Keys::Up))
    {
      acc = thrustCoeff;
      position->angle = motion->rot;
    }
    motion->vel += acc * (float)dt;
    motion->vel *= frictionCoeff;
    motion->vel = std::max(0.0f, std::min(motion->vel, maxSpeed));

    float rot = 0.0f;
    if (m_keyState.pressed(Def::KeyState::Keys::Left))
    {
      rot += angleCoeff;
    }
    if (m_keyState.pressed(Def::KeyState::Keys::Right))
    {
      rot -= angleCoeff;
    }
    motion->rot += rot * (float)dt;

    laser->isFiring = m_keyState.pressed(Def::KeyState::Keys::Space);
  }
}

void ControlByPlayer::configure(entityx::EventManager &eventManager)
{
  eventManager.subscribe<Ev::PlayerInput>(*this);
}

void ControlByPlayer::receive(const Ev::PlayerInput &event)
{
  m_keyState = event.keyState;
}
