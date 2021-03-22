#pragma once

#include "Arduino.h"
#include "dolp.h"

extern World demo;

extern uint8_t syncValue;

enum GameState {
  SetupState,
  PlayState,
  GameOverState
};
extern GameState gameState;

enum EntityType {
  PaddleType,
  BallType,
  WallType
};
