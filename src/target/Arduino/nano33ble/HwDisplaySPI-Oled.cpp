#include "hardware/HwConfiguration.h"
#if defined(ARDUINO_NANO33BLE)

#if defined(DISPLAY_SPI)

#if defined(DISPLAY_SSD1306) || defined(DISPLAY_SH1106)

#include "hardware/HwDisplay.h"
#include "Arduino.h"
#include "SPI.h"
//#undef SPI

// arduino::MbedSPI SPI(SPI_MISO, SPI_MOSI, SPI_SCK);

#if defined(DISPLAY_SSD1306)
#define DISPLAY_COLUMNS (128)
#define DISPLAY_STARTCOL (0)
#elif defined(DISPLAY_SH1106)
/* The screen is actually 130x64, so 2 cols must be cleared */
#define DISPLAY_COLUMNS (130)
#define DISPLAY_STARTCOL (2)
#endif

#define CS_PIN 10
#define DC_PIN 9	// P0_25
#define RESET_PIN 8 // P0_24
#define SPI_DATA_MODE() (digitalWrite(DC_PIN, HIGH))
#define SPI_COMMAND_MODE() (digitalWrite(DC_PIN, LOW))

SPISettings spiConfig = SPISettings(8000000, MSBFIRST, SPI_MODE0);

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
								  0x10, 0x40, 0x81, 0xFF // 0x3F testing contrast
								  ,
								  0xA1, 0xA6, 0xA8, 0x3F,
								  0xA4, 0xD3, 0x00, 0xD5, 0xF0, 0xD9, 0x22, 0xDA, 0x12,
								  0xDB, 0x20, 0x8D, 0x14, 0xAF};

void hwDisplaySetup()
{
	digitalWrite(CS_PIN, LOW);
	SPI.begin();
	delay(100);
	SPI.beginTransaction(spiConfig);

	// Reset display
	digitalWrite(RESET_PIN, LOW);
	digitalWrite(RESET_PIN, HIGH);

	// Send display configuration through SPI
	SPI_COMMAND_MODE();
	SPI.transfer(INIT_COMMANDS, INIT_COMMANDS_SIZE);

	// Clear the whole display
	uint8_t tempBuff[DISPLAY_COLUMNS];
	for (int index = 0; index < DISPLAY_COLUMNS; index++)
	{
		tempBuff[index] = 0;
	}
	/* Send the black screen to clear the display */
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {0xB0 + page, 0x00, 0x10};
		SPI_COMMAND_MODE();
		SPI.transfer(setPageCmd, 3);

		SPI_DATA_MODE();
		SPI.transfer(tempBuff, DISPLAY_COLUMNS);
	}
}

void hwDisplaySend()
{
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {0xB0 + page, DISPLAY_STARTCOL, 0x10};
		SPI_COMMAND_MODE();
		SPI.transfer(setPageCmd, 3);

		SPI_DATA_MODE();
		SPI.transfer(displayBuffer + (page * 128), 128);
	}
}

#endif

#endif
#endif
