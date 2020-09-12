//#if 0
#include "hardware/HwDisplay.h"
#include <Wire.h>

#define I2C
#define DISPLAY_ADDRESS (0x78)
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

uint8_t addressConfig[] = {0x21, 0, 127, 0x22, 0, 7};

//TwoWire i2c = TwoWire(PB_9, PB_8);
//TwoWire i2c = TwoWire();

void hwDisplaySetup()
{
#ifdef I2C
	//i2c.begin();	
	Wire.begin();	

	delay(200);
	//HAL_Delay(200);
	/* Send display configuration through I2C */
	//HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, 1, INIT_COMMANDS, INIT_COMMANDS_SIZE, HAL_MAX_DELAY);
	//i2c.beginTransmission(DISPLAY_ADDRESS);
	Wire.beginTransmission(DISPLAY_ADDRESS);
	/* Clear the whole display */
	/* The screen is actually 130x64, so 2 more cols must be cleared */
	uint8_t tempBuff[130];
	for(int index = 0; index < 130; index++)
	{
		tempBuff[index] = 0;
	} 
	/* Send the black screen to clear the display */
	for(int page = 0; page < 8; page++) {
		uint8_t setPageCmd[] = {0xB0 + page, 0x00, 0x10};
		Wire.write(0x00);
		Wire.write(setPageCmd, 3);
		Wire.write(0x40);
		Wire.write(tempBuff, 130);
		//i2c.write(0x00);
		//i2c.write(setPageCmd, 3);
		//i2c.write(0x40);
		//i2c.write(tempBuff, 130);
		//HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, 1, setPageCmd, 3, HAL_MAX_DELAY);
		//HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, 1, tempBuff, 130, HAL_MAX_DELAY);
	}
	Wire.endTransmission();
#else

#endif
}

void hwDisplaySend(uint8_t* buffer)
{
#ifdef I2C
	Wire.beginTransmission(DISPLAY_ADDRESS);
	//while(!i2c.available());
	//i2c.write(buffer, 512);
	/* Transfer the screen to the display */
	for(int page = 0; page < 8; page++) {
		uint8_t setPageCmd[] = {0xB0 + page, 0x00, 0x10};
		Wire.write(0x00);
		Wire.write(setPageCmd, 3);
		Wire.write(0x40);
		Wire.write(buffer + (page * 128), 128);
		//HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x00, 1, setPageCmd, 3, HAL_MAX_DELAY);
		//HAL_I2C_Mem_Write(&hi2c1, 0x78, 0x40, 1, buffer + (page * 128), 128, HAL_MAX_DELAY);
	}
	Wire.endTransmission();
#else

#endif
}

//#endif
