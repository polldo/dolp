#include "hardware/HwConfiguration.h"
#if defined(MICROPYTHON)

#if defined(DISPLAY_SPI)

#if defined(DISPLAY_SSD1306) || defined(DISPLAY_SH1106)

#include "hardware/HwDisplay.h"

extern "C"
{
#include <extmod/machine_spi.h>
#include <extmod/virtpin.h>
#include <ports/rp2/modmachine.h>
#include <py/obj.h>
#include <py/mphal.h>
}

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

static mp_obj_base_t *spi;
static mp_machine_spi_p_t *spiproto;

static mp_obj_base_t *dcPin;
static mp_obj_base_t *resetPin;
static mp_pin_p_t *pinproto;
#define DC_PIN 21
#define RESET_PIN 20
#define SPI_DATA_MODE() (pinproto->ioctl(dcPin, 2, 1, NULL))
#define SPI_COMMAND_MODE() (pinproto->ioctl(dcPin, 2, 0, NULL))

void hwDisplaySetup()
{
	mp_obj_t id = mp_obj_new_int(0);
	mp_obj_t s = machine_spi_type.make_new(&machine_spi_type, 1, 0, &id);
	spi = (mp_obj_base_t *)MP_OBJ_TO_PTR(s);
	spiproto = (mp_machine_spi_p_t *)spi->type->protocol;

	id = mp_obj_new_int(DC_PIN);
	mp_obj_t mode = mp_obj_new_int(1);
	mp_obj_t args[] = {id, mode};
	mp_obj_t d = machine_pin_type.make_new(&machine_pin_type, 2, 0, args);
	dcPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(d);
	pinproto = (mp_pin_p_t *)machine_pin_type.protocol;

	id = mp_obj_new_int(RESET_PIN);
	args[0] = id;
	mp_obj_t r = machine_pin_type.make_new(&machine_pin_type, 2, 0, args);
	resetPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(r);

	// Reset display
	pinproto->ioctl(resetPin, 2, 0, NULL);
	mp_hal_delay_ms(1);
	pinproto->ioctl(resetPin, 2, 1, NULL);

	// Send display configuration through SPI
	SPI_COMMAND_MODE();
	spiproto->transfer(spi, INIT_COMMANDS_SIZE, INIT_COMMANDS, NULL);

	// Clear the whole display
	uint8_t tempBuff[DISPLAY_COLUMNS];
	for (int index = 0; index < DISPLAY_COLUMNS; index++)
	{
		tempBuff[index] = 0;
	}
	/* Send the black screen to clear the display */
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {uint8_t(0xB0 + page), 0x00, 0x10};
		SPI_COMMAND_MODE();
		spiproto->transfer(spi, 3, setPageCmd, NULL);

		SPI_DATA_MODE();
		spiproto->transfer(spi, DISPLAY_COLUMNS, tempBuff, NULL);
	}
}

void hwDisplaySend()
{
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {uint8_t(0xB0 + page), DISPLAY_STARTCOL, 0x10};
		SPI_COMMAND_MODE();
		spiproto->transfer(spi, 3, setPageCmd, NULL);

		SPI_DATA_MODE();
		spiproto->transfer(spi, 128, displayBuffer + (page * 128), NULL);
	}
}

#endif

#endif
#endif
