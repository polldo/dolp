#include "hardware/HwConfiguration.h"
#if defined (ARDUINO_NANO33BLE)

#if defined(DISPLAY_ST7735)

#include "hardware/HwDisplay.h"
#include "Arduino.h"

#define DISPLAY_ASCENDING_Y

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 160
#define DISPLAY_LENGTH (128 * 160 * 2)

uint8_t displayBuffer[DISPLAY_LENGTH] = {0};

void hwDisplayDraw(uint8_t x, uint8_t y, DisplayColor color)
{
	// Check display boundaries
	if (x >= DISPLAY_WIDTH || y > DISPLAY_HEIGHT) return;

#if defined (DISPLAY_ASCENDING_Y)

	uint16_t index = ((DISPLAY_HEIGHT - 1 - y) * 128 * 2 + x * 2);
	//displayBuffer[index] = color & 0xFF;
	//displayBuffer[index + 1] = (color >> 8) & 0xFF;
	memcpy(&displayBuffer[index], &color, sizeof(uint16_t));

#else 
	uint16_t index = (y * 128 * 2 + x * 2);
	//displayBuffer[index] = color & 0xFF;
	//displayBuffer[index + 1] = (color >> 8) & 0xFF;
	memcpy(&displayBuffer[index], &color, sizeof(uint16_t));
#endif
}

void hwDisplayDrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, DisplayColor color)
{
	// Just a proof of concept (highly inefficient)
	for (int i = 0 ; i < w; i++) {
		for (int j = 0; j < h; j++) {
			hwDisplayDraw( (x - w / 2 + i), (y - h / 2 + j), color);
		}
	}
}

void hwDisplayDrawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* image)
{
	// TODO: check boundaries
#if defined (DISPLAY_ASCENDING_Y)
	const uint8_t startIndex = 2;
	uint8_t imageX = x - w / 2;
	uint8_t imageY = y + h / 2;
	uint16_t index = startIndex;

	for (uint8_t j = 0; j < h / 8; j++) {
		for (uint8_t i = 0; i < w; i++) {
			uint8_t vLine = image[index++];
			for (uint8_t k = 0; k < 8; k++) {
				DisplayColor pixel = vLine & (0x01 << k) ? WHITE_COLOR : BLACK_COLOR;
				hwDisplayDraw(imageX + i, imageY - k, pixel);			
			}
		}
		imageY -= 8;
	}
#endif
}

void hwDisplayFill(DisplayColor color)
{
	static const uint8_t incr = sizeof(color);
	for(int index = 0; index < DISPLAY_LENGTH / incr; index++)
	{
		//displayBuffer[index++] = color;
		//displayBuffer[index] = pixels;
		memcpy(&displayBuffer[index * incr], &color, incr);
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

#endif
