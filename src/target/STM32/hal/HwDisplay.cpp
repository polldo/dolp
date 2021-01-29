#include "hardware/HwConfiguration.h"
#if defined (_STM32_HAL_)

#include "hardware/HwDisplay.h"

#ifdef DISPLAY_I2C
I2C_HandleTypeDef hi2c1;
#endif

#if defined (DISPLAY_SSD1306)
#define DISPLAY_COLUMNS (128)
#define DISPLAY_STARTCOL (0)
#elif defined (DISPLAY_SH1106)
/* The screen is actually 130x64, so 2 cols must be cleared */
#define DISPLAY_COLUMNS (130)
#define DISPLAY_STARTCOL (2)
#endif

#define DISPLAY_ADDRESS (0x3C)
#define DISPLAY_ADDRESS_SHIFTED (0x78)

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_LENGTH 1024

static uint8_t buffer[DISPLAY_LENGTH];

#define INIT_COMMANDS_SIZE 28
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

void hwDisplaySetup()
{
#ifdef DISPLAY_I2C
	/* I2C Master mode
 	 * Write transfer
 	 * Fast mode (1 MHz)
	 *
	 */
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
    /* I2C1 GPIO Configuration    
     * PB8     ------> I2C1_SCL
     * PB9     ------> I2C1_SDA
     */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00301238;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
	}
	/** Configure Analogue filter 
	*/
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_DISABLE) != HAL_OK)
	{
	}
	/** Configure Digital filter 
	*/
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	{
	}
	/** I2C Fast mode Plus enable 
	*/
	HAL_I2CEx_EnableFastModePlus(I2C_FASTMODEPLUS_I2C1);
	/* Wait display initialization */
	HAL_Delay(200);
	/* Send display configuration through I2C */
	HAL_I2C_Mem_Write(&hi2c1, DISPLAY_ADDRESS_SHIFTED, 0x00, 1, INIT_COMMANDS, INIT_COMMANDS_SIZE, HAL_MAX_DELAY);
	/* Clear the whole display */
	uint8_t tempBuff[DISPLAY_COLUMNS];
	for(int index = 0; index < DISPLAY_COLUMNS; index++)
	{
		tempBuff[index] = 0;
	} 
	/* Send the black screen to clear the display */
	for(int page = 0; page < 8; page++) {
		uint8_t setPageCmd[] = {0xB0 + page, 0x00, 0x10};
		HAL_I2C_Mem_Write(&hi2c1, DISPLAY_ADDRESS_SHIFTED, 0x00, 1, setPageCmd, 3, HAL_MAX_DELAY);
		HAL_I2C_Mem_Write(&hi2c1, DISPLAY_ADDRESS_SHIFTED, 0x40, 1, tempBuff, DISPLAY_COLUMNS, HAL_MAX_DELAY);
	}
#else
	/* SPI2 and GPIO clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/* SPI2 GPIO Configuration
	    PC3     ------> SPI2_MOSI
	    PB10     ------> SPI2_SCK
	    PC12	------> SPI_SS
	*/
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	/* SPI2 Configuration
	 	Transmit-only mode
	 	MSB first
	 	Baudrate 
		Master configuration
		Datasize 8 bit
	*/
	SPI2->CR2 = (SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2 | SPI_CR2_NSSP);
	SPI2->CR1 =
	(
			SPI_CR1_SPE
			| SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE
			| SPI_CR1_BR_1 /* /8 */
			//| SPI_CR1_BR_0 | SPI_CR1_BR_2 /* /64 */
			| SPI_CR1_MSTR
	);
	/* SPI SS enable */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
#endif
}

void hwDisplaySend()
{
#ifdef DISPLAY_I2C
	/* Transfer the screen to the display */
	for(int page = 0; page < 8; page++) {
		uint8_t setPageCmd[] = {0xB0 + page, DISPLAY_STARTCOL, 0x10};
		HAL_I2C_Mem_Write(&hi2c1, DISPLAY_ADDRESS_SHIFTED, 0x00, 1, setPageCmd, 3, HAL_MAX_DELAY);
		HAL_I2C_Mem_Write(&hi2c1, DISPLAY_ADDRESS_SHIFTED, 0x40, 1, buffer + (page * 128), 128, HAL_MAX_DELAY);
	}
#else
	/* Send init cmd */
	for (uint8_t initCount = 0; initCount < 2; initCount++)
	{
		while (! (SPI2->SR & SPI_SR_TXE) );
		*((__IO uint8_t *)&SPI2->DR) = 0x01;
	}
	/* Send the display buffer */
	for (uint16_t transferCount = 0; transferCount < DISPLAY_LENGTH; transferCount++)
	{
		while (! (SPI2->SR & SPI_SR_TXE) );
		*((__IO uint8_t *)&SPI2->DR) = displayBuffer[transferCount];
	}
#endif
}

void hwDisplayDraw(uint8_t x, uint8_t y, DisplayColor color)
{
#if defined(DISPLAY_ASCENDING_Y)
	uint8_t row = (7 - (uint8_t)y / 8);
	if (color == 0)
		buffer[(row*128) + (uint8_t)x] |= 1 << (7 - ((uint8_t)y % 8));
	else if (color == 1)
		buffer[(row*128) + (uint8_t)x] &= ~ ( 1 << (7 - (uint8_t)y % 8) );
	else if (color == 2)
		buffer[(row*128) + (uint8_t)x] ^=  ( 1 << (7 - (uint8_t)y % 8) );
#else 
	uint8_t row = (uint8_t)y / 8;
	if (color == 0)
		buffer[(row*128) + (uint8_t)x] |= 1 << ((uint8_t)y % 8);
	else if (color == 1)
		buffer[(row*128) + (uint8_t)x] &= ~ ( 1 << ((uint8_t)y % 8) );
	else if (color == 2)
		buffer[(row*128) + (uint8_t)x] ^=  ( 1 << ((uint8_t)y % 8) );
#endif
}

void hwDisplayFill(DisplayColor color)
{
	for(int index = 0; index < DISPLAY_LENGTH; index++)
	{
		buffer[index] = color;
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
