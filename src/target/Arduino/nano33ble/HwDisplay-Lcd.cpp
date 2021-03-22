#include "hardware/HwConfiguration.h"
#if defined (ARDUINO_NANO33BLE)

#if defined(DISPLAY_ST7735)

#include "hardware/HwDisplay.h"
#include "Arduino.h"

#define DISPLAY_ASCENDING_Y

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 160
#define DISPLAY_LENGTH (DISPLAY_WIDTH * DISPLAY_HEIGHT)

uint16_t displayBuffer[DISPLAY_LENGTH] = {0};

void hwDisplayDraw(int x, int y, DisplayColor color)
{
	if (color == BLACK_COLOR) return;
	// Check display boundaries
	if (x >= DISPLAY_WIDTH || x < 0 || y >= DISPLAY_HEIGHT || y < 0) return;

#if defined (DISPLAY_ASCENDING_Y)

	uint16_t index = ((DISPLAY_HEIGHT - 1 - y) * DISPLAY_WIDTH + x);
	displayBuffer[index] = color;

#else 
	uint16_t index = (y * DISPLAY_WIDTH + x);
	displayBuffer[index] = color;
#endif
}

void hwDisplayDrawRectangle(int x, int y, uint8_t w, uint8_t h, DisplayColor color)
{
	// Just a proof of concept (highly inefficient)
	for (int i = 0 ; i < w; i++) {
		for (int j = 0; j < h; j++) {
			hwDisplayDraw( (x - w / 2 + i), (y - h / 2 + j), color);
		}
	}
}

void hwDisplayDrawImage(int x, int y, uint8_t w, uint8_t h, const uint16_t* image)
{
	w = *(image++);
	h = *(image++);
	for (int j = 0; j < h; j++) {
		for (int i = 0 ; i < w; i++) {
#if defined (DISPLAY_ASCENDING_Y)
			hwDisplayDraw( (x - w / 2 + i), (y + h / 2 - j), *(image++));
#else
			hwDisplayDraw( (x - w / 2 + i), (y - h / 2 + j), *(image++));
#endif
		}
	}

#if 0 // This seems way faster, but profiler doesn't agree
			// TODO: perform more significative tests with many images rendered
#if defined (DISPLAY_ASCENDING_Y)
	// TODO: check boundaries and trim the image accordingly
	y = DISPLAY_HEIGHT - 1 - y;

	for (int i = 0; i < h; i++) {
		memcpy(&displayBuffer[(y + h / 2 - i) * 128 + x - w / 2], image, w*2);
		image += w;
	}
#endif
#endif
}

void hwDisplayDrawImage(int x, int y, uint8_t w, uint8_t h, const uint8_t* image)
{
#if defined (DISPLAY_ASCENDING_Y)
	w = *(image++);
	h = *(image++);
	uint8_t imageX = x - w / 2;
	uint8_t imageY = y + h / 2;

	for (uint8_t j = 0; j < h / 8; j++) {
		for (uint8_t i = 0; i < w; i++) {
			uint8_t vLine = *(image++);
			for (uint8_t k = 0; k < 8; k++) {
				DisplayColor pixel = vLine & (0x01 << k) ? WHITE_COLOR : BLACK_COLOR;
				hwDisplayDraw(imageX + i, imageY - k, pixel);			
			}
		}
		imageY -= 8;
	}
#endif
}

void hwDisplayDrawImage(int x, int y, uint8_t w, uint8_t h, const uint8_t* image, const uint8_t* mask)
{
	// TODO
}

void hwDisplayFill(DisplayColor color)
{
	for(int index = 0; index < DISPLAY_LENGTH; index++)
	{
		displayBuffer[index] = color;
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
