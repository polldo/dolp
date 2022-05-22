#include "hardware/HwConfiguration.h"
#if defined(ARDUINO_ARDUINO_NANO33BLE)

#if defined(DISPLAY_SSD1306) || defined(DISPLAY_SH1106)

#include "hardware/HwDisplay.h"
#include "Arduino.h"

#define DISPLAY_ASCENDING_Y

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_LENGTH 1024

uint8_t displayBuffer[DISPLAY_LENGTH];

void hwDisplayDraw(uint8_t x, uint8_t y, DisplayColor color)
{
	// Check display boundaries
	if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT)
		return;

#if defined(DISPLAY_ASCENDING_Y)
	uint8_t row = (7 - (uint8_t)y / 8);
	if (color == WHITE_COLOR)
		displayBuffer[(row * 128) + (uint8_t)x] |= 1 << (7 - ((uint8_t)y % 8));
	else if (color == BLACK_COLOR)
		displayBuffer[(row * 128) + (uint8_t)x] &= ~(1 << (7 - (uint8_t)y % 8));
	else if (color == 2)
		displayBuffer[(row * 128) + (uint8_t)x] ^= (1 << (7 - (uint8_t)y % 8));
#else
	uint8_t row = (uint8_t)y / 8;
	if (color == WHITE_COLOR)
		displayBuffer[(row * 128) + (uint8_t)x] |= 1 << ((uint8_t)y % 8);
	else if (color == BLACK_COLOR)
		displayBuffer[(row * 128) + (uint8_t)x] &= ~(1 << ((uint8_t)y % 8));
#endif
}

void hwDisplayDrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, DisplayColor color)
{
	// Just a proof of concept (highly inefficient)
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			hwDisplayDraw((x - w / 2 + i), (y - h / 2 + j), color);
		}
	}
}

void hwDisplayDrawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *image)
{
	// TODO: check boundaries
#if defined(DISPLAY_ASCENDING_Y)
	uint16_t index = 0;
	w = image[index++];
	h = image[index++];
	uint8_t imageX = x - w / 2;
	uint8_t imageY = y + h / 2;

	for (uint8_t j = 0; j < h / 8; j++)
	{
		for (uint8_t i = 0; i < w; i++)
		{
			uint8_t vLine = image[index++];
			for (uint8_t k = 0; k < 8; k++)
			{
				DisplayColor pixel = vLine & (0x01 << k) ? WHITE_COLOR : BLACK_COLOR;
				hwDisplayDraw(imageX + i, imageY - k, pixel);
			}
		}
		imageY -= 8;
	}
#endif
}

void hwDisplayDrawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *image, const uint8_t *mask)
{
	// TODO: check boundaries
#if defined(DISPLAY_ASCENDING_Y)
	uint16_t index = 0;
	w = image[index++];
	h = image[index++];
	uint8_t imageX = x - w / 2;
	uint8_t imageY = y + h / 2;

	for (uint8_t j = 0; j < h / 8; j++)
	{
		for (uint8_t i = 0; i < w; i++)
		{
			uint8_t maskLine = mask[index];
			uint8_t vLine = image[index++];
			for (uint8_t k = 0; k < 8; k++)
			{
				bool maskPixel = maskLine & (0x01 << k);
				if (!maskPixel)
					continue;
				DisplayColor pixel = vLine & (0x01 << k) ? WHITE_COLOR : BLACK_COLOR;
				hwDisplayDraw(imageX + i, imageY - k, pixel);
			}
		}
		imageY -= 8;
	}
#endif
}

void hwDisplayDrawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint16_t *image)
{
	// Color images are not supported on monochrome displays
	w = *(image++);
	h = *(image++);
	hwDisplayDrawRectangle(x, y, w, h, WHITE_COLOR);
}

void hwDisplayFill(DisplayColor color)
{
	uint8_t pixels = 0x00;
	if (color == WHITE_COLOR)
		pixels = 0xFF;
	for (int index = 0; index < DISPLAY_LENGTH; index++)
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
#endif
