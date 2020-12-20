#include "hardware/HwConfiguration.h"
#if defined (_STM32_DUINO_)

#include "hardware/HwDisplay.h"
#include <Wire.h>

#define DISPLAY_ADDRESS (0x3C)

#if defined (SSD1306)
#define DISPLAY_COLUMNS (128)
#define DISPLAY_STARTCOL (0)
#elif defined (SH1106)
/* The screen is actually 130x64, so 2 cols must be cleared */
#define DISPLAY_COLUMNS (130)
#define DISPLAY_STARTCOL (2)
#endif

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_LENGTH 1024

static uint8_t _buffer[DISPLAY_LENGTH];

#define INIT_COMMANDS_SIZE (28)
/*
 * Command sequence needed to correctly initialize the oled screen
 * Attention: display is initialize in OFF mode so that it can be cleared before its use
 */
static uint8_t INIT_COMMANDS[] = {0xAE, 0x20, 0x02, 0xB0, 0xC8, 0x00,
										0x10, 0x40, 0x81, 0xFF//0x3F testing contrast
										, 0xA1, 0xA6, 0xA8, 0x3F,
										0xA4, 0xD3, 0x00, 0xD5, 0xF0, 0xD9, 0x22, 0xDA, 0x12,
										0xDB, 0x20, 0x8D, 0x14, 0xAF};


void hwDisplaySetup()
{
#ifdef I2C
	Wire.begin();	
	Wire.setClock(1000000);
	delay(200);

	/* Send display configuration through I2C */
	Wire.beginTransmission(DISPLAY_ADDRESS);
    Wire.write(0x00);
    Wire.write(INIT_COMMANDS, INIT_COMMANDS_SIZE);
	Wire.endTransmission();
	/* Clear the whole display */
	uint8_t tempBuff[DISPLAY_COLUMNS];
	for(int index = 0; index < DISPLAY_COLUMNS; index++)
	{
		tempBuff[index] = 0;
	} 
	/* Send the black screen to clear the display */
	for(int page = 0; page < 8; page++) {
		uint8_t setPageCmd[] = {0xB0 + page, 0x00, 0x10};
		Wire.beginTransmission(DISPLAY_ADDRESS);
			Wire.write(0x00);
			Wire.write(setPageCmd, 3);
		Wire.endTransmission();

		Wire.beginTransmission(DISPLAY_ADDRESS);
			Wire.write(0x40);
			Wire.write(tempBuff, DISPLAY_COLUMNS);
		Wire.endTransmission();
	}
#else //I2C

#endif
}

void hwDisplaySend()
{
#ifdef I2C
	for(int page = 0; page < 8; page++) {
		uint8_t setPageCmd[] = {0xB0 + page, DISPLAY_STARTCOL, 0x10};
		Wire.beginTransmission(DISPLAY_ADDRESS);
			Wire.write(0x00);
			Wire.write(setPageCmd, 3);
		Wire.endTransmission();

		Wire.beginTransmission(DISPLAY_ADDRESS);
			Wire.write(0x40);
			Wire.write(_buffer + (page * 128), 128);
		Wire.endTransmission();
	}
#else

#endif //I2C
}

void hwDisplayDraw(uint8_t x, uint8_t y, DisplayColor color)
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

void hwDisplayFill(DisplayColor color)
{
	for(int index = 0; index < DISPLAY_LENGTH; index++)
	{
		_buffer[index] = color;
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

#endif // _STM32_DUINO_
