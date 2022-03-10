#include <drivers/Display.h>
#include <hardware/HwDisplay.h>

Display::Display()
{
}

Display::~Display()
{
}

void Display::setup()
{
	hwDisplaySetup();
}

void Display::send()
{
	hwDisplaySend();
}

void Display::draw(uint8_t x, uint8_t y, DisplayColor color)
{
	hwDisplayDraw(x, y, color);
}

void Display::drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *image)
{
	hwDisplayDrawImage(x, y, w, h, image);
}

void Display::drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint16_t *image)
{
	hwDisplayDrawImage(x, y, w, h, image);
}

void Display::drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, DisplayColor color)
{
	hwDisplayDrawRectangle(x, y, width, height, color);
}

void Display::fill(DisplayColor color)
{
	hwDisplayFill(color);
}

int Display::width()
{
	return hwDisplayWidth();
}

int Display::height()
{
	return hwDisplayHeight();
}
