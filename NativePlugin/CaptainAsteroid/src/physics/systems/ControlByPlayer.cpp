#include "ControlByPlayer.hpp"

#include "components/Motion.hpp"
#include "components/Laser.hpp"
#include "components/PlayerControl.hpp"

#include <algorithm>
#include <cmath>

using namespace CaptainAsteroidCPP::Sys;

ControlByPlayer::ControlByPlayer(){};

void ControlByPlayer::update(
  entityx::EntityManager &entities,
  entityx::EventManager &events,
  double dt)
{
  constexpr float maxAcc = 0.05f;
  constexpr float maxSpeed = 10.0f;
  constexpr float thrustCoeff = 20.0f;
  constexpr float angleCoeff = 0.5f;
  constexpr float frictionCoeff = 0.997f;

  Comp::Motion::Handle motion;
  Comp::Laser::Handle laser;
  Comp::PlayerControl::Handle playerControl;
  for (entityx::Entity entity : entities.entities_with_components(playerControl, motion, laser))
  {
    float acc = 0.0f;
    if (m_keyState.pressed(Def::KeyState::Keys::Down))
    {
      acc = -thrustCoeff;
    }
    if (m_keyState.pressed(Def::KeyState::Keys::Up))
    {
      acc = thrustCoeff;
    }

    motion->rot = 0.0f;
    if (m_keyState.pressed(Def::KeyState::Keys::Left))
    {
      motion->rot = angleCoeff;
    }
    if (m_keyState.pressed(Def::KeyState::Keys::Right))
    {
      motion->rot = -angleCoeff;
    }

    motion->vel += acc * (float)dt;
    motion->vel *= frictionCoeff;
    motion->vel = std::max(0.0f, std::min(motion->vel, maxSpeed));

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
