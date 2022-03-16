#include "hardware/HwConfiguration.h"
#if defined(ARDUINO_NANO33BLE)

#if defined(DISPLAY_SSD1306) || defined(DISPLAY_SH1106)

#if defined(DISPLAY_I2C)

#include "hardware/HwDisplay.h"
#include "Arduino.h"
#include "Wire.h"

#define DISPLAY_ADDRESS (0x3C)

#if defined(DISPLAY_SSD1306)
#define DISPLAY_COLUMNS (128)
#define DISPLAY_STARTCOL (0)
#elif defined(DISPLAY_SH1106)
/* The screen is actually 130x64, so 2 cols must be cleared */
#define DISPLAY_COLUMNS (130)
#define DISPLAY_STARTCOL (2)
#endif

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_LENGTH 1024

extern uint8_t displayBuffer[DISPLAY_LENGTH];

#define INIT_COMMANDS_SIZE (28)
/*
 * Command sequence needed to correctly initialize the oled screen
 * Attention: display is initialize in OFF mode so that it can be cleared before its use
 */
static uint8_t INIT_COMMANDS[] = {0xAE, 0x20, 0x02, 0xB0, 0xC8, 0x00,
								  0x10, 0x40, 0x81, 0xFF, // 0x3F testing contrast
								  0xA1, 0xA6, 0xA8, 0x3F,
								  0xA4, 0xD3, 0x00, 0xD5, 0xF0, 0xD9, 0x22, 0xDA, 0x12,
								  0xDB, 0x20, 0x8D, 0x14, 0xAF};

void hwDisplaySetup()
{
	Wire.begin();
	Wire.setClock(10000000);
	delay(200);

	/* Send display configuration through I2C */
	Wire.beginTransmission(DISPLAY_ADDRESS);
	Wire.write((uint8_t)0x00);
	Wire.write(INIT_COMMANDS, INIT_COMMANDS_SIZE);
	Wire.endTransmission();

	/* Clear the whole display */
	uint8_t tempBuff[DISPLAY_COLUMNS];
	for (int index = 0; index < DISPLAY_COLUMNS; index++)
	{
		tempBuff[index] = 0;
	}

	/* Send the black screen to clear the display */
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {0xB0 + page, 0x00, 0x10};
		Wire.beginTransmission(DISPLAY_ADDRESS);
		Wire.write((uint8_t)0x00);
		Wire.write(setPageCmd, 3);
		Wire.endTransmission();

		Wire.beginTransmission(DISPLAY_ADDRESS);
		Wire.write((uint8_t)0x40);
		Wire.write(tempBuff, DISPLAY_COLUMNS);
		Wire.endTransmission();
	}
}

void hwDisplaySend()
{
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {0xB0 + page, DISPLAY_STARTCOL, 0x10};
		Wire.beginTransmission(DISPLAY_ADDRESS);
		Wire.write((uint8_t)0x00);
		Wire.write(setPageCmd, 3);
		Wire.endTransmission();

		Wire.beginTransmission(DISPLAY_ADDRESS);
		Wire.write((uint8_t)0x40);
		Wire.write(displayBuffer + (page * 128), 128);
		Wire.endTransmission();
	}
}

#endif

#endif
#endif
