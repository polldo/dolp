#ifndef PAINTER_H_
#define PAINTER_H_

#include <dolp.h>

enum PainterDirection {
  Up,
  Right,
  Down,
  Left
};

class Painter {
public:
	Painter(){}
	Painter(uint8_t x, uint8_t y, PainterDirection direction); 
	virtual ~Painter(){}

	void move();
	void changeDirection(); 
	void draw(); 

private:
	uint8_t _x;
	uint8_t _y;
	PainterDirection _direction;
};

#endif /* PAINTER_H_ */
