#include <drivers/Display.h>
#include <hardware/HwDisplay.h>

Display::Display()
{
}

Display::~Display()
{
}

void Display::fill(uint8_t color)
{
	for(int index = 0; index < DISPLAY_LENGTH; index++)
	{
		_buffer[index] = color;
	}
}

void Display::setup()
{
	hwDisplaySetup();
}

void Display::send()
{
	hwDisplaySend(_buffer);
}

void Display::draw(uint8_t x, uint8_t y, uint8_t color)
{
	uint8_t row = (uint8_t)y / 8;
	if (color == 0)
		_buffer[(row*128) + (uint8_t)x] |= 1 << ((uint8_t)y % 8);
	else if (color == 1)
		_buffer[(row*128) + (uint8_t)x] &= ~ ( 1 << ((uint8_t)y % 8) );
	else if (color == 2)
		_buffer[(row*128) + (uint8_t)x] ^=  ( 1 << ((uint8_t)y % 8) );
}
