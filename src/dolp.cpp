#include "dolp.h"
#include "drivers/DriverLayer.h"

void Dolp::begin()
{
  driverLayer.setup();
  engine.setup();
  engine.setWorld(_world);
}

void Dolp::loopBegin()
{
  joystick.update();
  engine.loopBegin();
}

void Dolp::loopEnd()
{
  engine.loopEnd();
  display.send();
  timer.waitEndFrame();
}

PEntity Dolp::newEntity()
{
  return _world.newEntity();
}

void Dolp::deleteEntity(PEntity entity)
{
  _world.deleteEntity(entity);
}

// TODO
// void Dolp::clear()
//{
//// Clear the world
//// Clear all the drivers' state: timeouts, notes...
//}

TimeoutId Dolp::newTimeout()
{
  return timer.newTimeout();
}

void Dolp::deleteTimeout(TimeoutId id)
{
  timer.deleteTimeout(id);
}

void Dolp::setTimeout(TimeoutId id, uint64_t millis, bool repeat)
{
  timer.setTimeout(id, millis, repeat);
}

bool Dolp::checkTimeout(TimeoutId id)
{
  return timer.checkTimeout(id);
}

uint64_t Dolp::millis()
{
  return timer.getMilliseconds();
}

bool Dolp::held(JoystickButton button)
{
  return joystick.held(button);
}

bool Dolp::pressed(JoystickButton button)
{
  return joystick.pressed(button);
}

int Dolp::width()
{
  return display.width();
}

int Dolp::height()
{
  return display.height();
}

Dolp dolp;
