#ifndef BODY_COMPONENT_H
#define BODY_COMPONENT_H

#include "Common.h"

class Entity;

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

class BodyComponent {
  public:
    BodyComponent(Entity& entity);

    void configure(int x, int y, int width, int height);
    Vect2& getPosition();
    Vect2& getSize();

  protected:
    //void update();

  private:
    Entity* _entity;
    Vect2 _position;
    Vect2 _size;
};

#endif 
