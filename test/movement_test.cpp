#include <stdio.h>
#include <iostream>

#include <math.h>

#define DECIMAL_SAVE 1024 // needed to avoid using float while preserving decimal digits
#define VELOCITY_RATE 8

struct Vect2 {
  Vect2() {}
  Vect2(int inputX, int inputY) : x(inputX), y(inputY) {}

  void set(int inputX, int inputY) 
  {
    x = inputX;
    y = inputY;
  }

  int x, y;
};

Vect2 _movement;
Vect2 _pos = Vect2(86, 4);

int _movedX, _movedY;

void configure(Vect2 destination, int velocity)
{
  if (velocity == 0) {
    _movement = Vect2(0, 0);
    return;
  }

  // vectorial operators could be implemented and used
  //Vect2& currentPosition = _bodyComponent->getPosition();
  Vect2& currentPosition = _pos;
  float distanceX = destination.x - currentPosition.x;
  float distanceY = destination.y - currentPosition.y;
  float len = sqrt(distanceX * distanceX + distanceY * distanceY);

  if ((int)len == 0) {
    _movement = Vect2(0, 0);
    return;
  }

  _movement = Vect2(distanceX * velocity * DECIMAL_SAVE / VELOCITY_RATE / len, 
                    distanceY * velocity * DECIMAL_SAVE / VELOCITY_RATE / len);

  _movedX = currentPosition.x * DECIMAL_SAVE;
  _movedY = currentPosition.y * DECIMAL_SAVE;

  std::cout << "_movementX: " << _movement.x << "  _movementY: " << _movement.y << "\n";

  //_destination = destination; 
}


int main() {
  Vect2 dest = Vect2(86, 54);
  configure(dest, 10);
}
