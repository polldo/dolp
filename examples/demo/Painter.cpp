#include "Painter.h"

Painter::Painter(uint8_t x, uint8_t y, PainterDirection direction) :
	_x(x),
	_y(y),
	_direction(direction)
{
}

void Painter::move()
{
    switch(_direction) {
    case PainterDirection::Right :
        if (_x == 127) {
            _x = 0;
        } else {
            _x += 1;
        }
        break;

    case PainterDirection::Up :
        if (_y == 63) {
            _y = 0;
        } else {
            _y += 1;
        }
        break;
        
    case PainterDirection::Left :
        if (_x == 0) {
            _x = 127;
        } else {
            _x -= 1;
        }
        break;

    case PainterDirection::Down :
        if (_y == 0) {
            _y = 63;
        } else {
            _y -= 1;
        }
        break;
    };
}

void Painter::changeDirection() {
    uint8_t numDir = static_cast<uint8_t>(_direction);
    numDir++;
    if (numDir > static_cast<uint8_t>(Left))
        numDir = 0;
    _direction = static_cast<PainterDirection>(numDir);
}

void Painter::draw() {
    display.draw(_x, _y, 2);
}
