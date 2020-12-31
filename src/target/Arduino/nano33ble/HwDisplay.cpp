#include "hardware/HwConfiguration.h"
#if defined (ARDUINO_NANO33BLE)

#include "hardware/HwDisplay.h"
#include "Arduino.h"

#define DISPLAY_ASCENDING_Y

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_LENGTH 1024

uint8_t displayBuffer[DISPLAY_LENGTH];

void hwDisplayDraw(uint8_t x, uint8_t y, DisplayColor color)
{
#if defined (DISPLAY_ASCENDING_Y)
	uint8_t row = (7 - (uint8_t)y / 8);
	if (color == WHITE_COLOR)
		displayBuffer[(row*128) + (uint8_t)x] |= 1 << (7 - ((uint8_t)y % 8));
	else if (color == BLACK_COLOR)
		displayBuffer[(row*128) + (uint8_t)x] &= ~ ( 1 << (7 - (uint8_t)y % 8) );
	else if (color == 2)
		displayBuffer[(row*128) + (uint8_t)x] ^=  ( 1 << (7 - (uint8_t)y % 8) );
#else 
	uint8_t row = (uint8_t)y / 8;
	if (color == WHITE_COLOR)
		displayBuffer[(row*128) + (uint8_t)x] |= 1 << ((uint8_t)y % 8);
	else if (color == BLACK_COLOR)
		displayBuffer[(row*128) + (uint8_t)x] &= ~ ( 1 << ((uint8_t)y % 8) );
#endif
}

void hwDisplayFill(DisplayColor color)
{
	uint8_t pixels = 0x00;
	if (color == WHITE_COLOR) pixels = 0xFF;
	for(int index = 0; index < DISPLAY_LENGTH; index++)
	{
		displayBuffer[index] = pixels;
	}
}

uint8_t hwDisplayWidth()
{
  return DISPLAY_WIDTH;
}

uint8_t hwDisplayHeight()
{
  return DISPLAY_HEIGHT;
}

#endif
