#include "dolp.h"

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

Dolp dolp;
