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
        _x += 1;
        break;
    case PainterDirection::Up :
        _y += 1;
        break;
    case PainterDirection::Left :
        _x -= 1;
        break;
    case PainterDirection::Down :
        _y -= 1;
        break;
    };
    if (_x == 128)
        _x = 1;
    else if (_x == 0)
        _x = 127;
    if (_y == 64)
        _y = 1;
    else if (_y == 1)
        _y = 63;
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
