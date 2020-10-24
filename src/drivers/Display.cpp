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
#if defined(DISPLAY_ASCENDING_Y)
	uint8_t row = (7 - (uint8_t)y / 8);
	if (color == 0)
		_buffer[(row*128) + (uint8_t)x] |= 1 << (7 - ((uint8_t)y % 8));
	else if (color == 1)
		_buffer[(row*128) + (uint8_t)x] &= ~ ( 1 << (7 - (uint8_t)y % 8) );
	else if (color == 2)
		_buffer[(row*128) + (uint8_t)x] ^=  ( 1 << (7 - (uint8_t)y % 8) );
#else 
	uint8_t row = (uint8_t)y / 8;
	if (color == 0)
		_buffer[(row*128) + (uint8_t)x] |= 1 << ((uint8_t)y % 8);
	else if (color == 1)
		_buffer[(row*128) + (uint8_t)x] &= ~ ( 1 << ((uint8_t)y % 8) );
	else if (color == 2)
		_buffer[(row*128) + (uint8_t)x] ^=  ( 1 << ((uint8_t)y % 8) );
#endif
}

void Display::drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
	// Just a proof of concept (highly inefficient)
	for (int i = 0 ; i < width; i++) {
		for (int j = 0; j < height; j++) {
			draw( (x - width / 2 + i), (y - height / 2 + j), 0);
		}
	}
}
