#include "dolp.h"
#include "Common.h"
#include "Paddle.h"

int PADDLE_WIDTH = 4;
int PADDLE_HEIGHT = 16;

int paddleSpeed = 2;

void updatePaddle(PEntity paddle)
{
  auto pos = paddle.getPosition();
  int newY = pos.y;
  if (joystick.held(ButtonA)) {
    // TODO: implement set position API
    if (pos.y + paddleSpeed + PADDLE_HEIGHT / 2 < display.height()) 
      newY = pos.y + paddleSpeed;
  } else {
    if (pos.y - paddleSpeed - PADDLE_HEIGHT / 2 >= 0)
      newY = pos.y - paddleSpeed;
  }
  paddle.configure(pos.x, newY, PADDLE_WIDTH, PADDLE_HEIGHT);
}

void syncPaddle(PEntity paddle)
{
  auto pos = paddle.getPosition();
  int newY = pos.y;
  if (syncValue) {
    // TODO: implement set position API
    if (pos.y + paddleSpeed + PADDLE_HEIGHT / 2 < display.height()) 
      newY = pos.y + paddleSpeed;
  } else {
    if (pos.y - paddleSpeed - PADDLE_HEIGHT / 2 >= 0)
      newY = pos.y - paddleSpeed;
  }
  paddle.configure(pos.x, newY, PADDLE_WIDTH, PADDLE_HEIGHT);
}

void spawnPaddle()
{
  PEntity paddle = demo.newEntity();
  paddle.setType(PaddleType);
  // TODO: hitbox should consider odd parameters
  paddle.configure(1, display.height()/2, PADDLE_WIDTH, PADDLE_HEIGHT);
  paddle.update(updatePaddle);
  paddle.collision();

  paddle = demo.newEntity();
  paddle.setType(PaddleType);
  paddle.configure(127, display.height()/2, PADDLE_WIDTH, PADDLE_HEIGHT);
  paddle.update(syncPaddle);
  paddle.collision();
}