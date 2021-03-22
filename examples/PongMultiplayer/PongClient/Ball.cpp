#include "Ball.h"
#include "Common.h"
#include "dolp.h"
#include <math.h>

#define BALL_WIDTH (2)
#define BALL_HEIGHT (2)

int ballSpeed = 22;

int ballAngle = 0;
int ballRange = 150;
int dirX = -1;
int dirY = 1;

Vect2 moveByAngle(int angle, int range, Vect2 dir) 
{
  float rad = (angle * 71) / 4068.;
  float pX = (float)(range) * cos(rad);
  float pY = (float)(range) * sin(rad);
  int destX = (int)pX * dir.x;
  int destY = (int)pY * dir.y;
  return Vect2(destX, destY);
}

void collisionBall(PEntity ball, PEntity other)
{
  if (other.getType() == WallType) {
    // check if the collision has been already resolved in the previous frame
    if (other.getY() > display.height()/2 && dirY < 0) return;
    if (other.getY() < display.height()/2 && dirY > 0) return;

    dirY *= -1;
    auto dest = moveByAngle(ballAngle, ballRange, Vect2(dirX, dirY));
    ball.moveTo(ball.getX() + dest.x, ball.getY() + dest.y, ballSpeed);

  } else if (other.getType() == PaddleType) {
    // check if the collision has been already resolved in the previous frame
    if (other.getX() < display.width()/2 && dirX > 0) return;
    if (other.getX() > display.width()/2 && dirX < 0) return;

    dirX *= -1;
    ballAngle = (random(50) + 20);
    if (ball.getY() < other.getY()) dirY = -1;
    else dirY = 1;

    auto dest = moveByAngle(ballAngle, ballRange, Vect2(dirX, dirY));
    ball.moveTo(ball.getX() + dest.x, ball.getY() + dest.y, ballSpeed);
  }
}

void updateBall(PEntity ball)
{

}

void spawnBall()
{
  PEntity ball = demo.newEntity();
  ball.setType(BallType);
  ball.configure(display.width()/2, display.height()/2, BALL_WIDTH, BALL_HEIGHT);
  ball.update(updateBall);
  ball.collision(collisionBall);

  ball.moveTo(0, display.height()/2, ballSpeed);
}
