#include "hardware/HwConfiguration.h"
#if defined(MICROPYTHON)

#if defined(DISPLAY_I2C)

#if defined(DISPLAY_SSD1306) || defined(DISPLAY_SH1106)

#include "hardware/HwDisplay.h"

extern "C"
{
#include <extmod/machine_i2c.h>
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

#define DISPLAY_ADDRESS (0x3C)

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

static mp_obj_base_t *i2c;
static mp_machine_i2c_p_t *i2cproto;
static unsigned int i2cFlags = 0x02; // write + stop

static mp_obj_base_t *resetPin;
static mp_pin_p_t *pinproto;
#define RESET_PIN 20

void hwDisplaySetup()
{
	mp_obj_t id = mp_obj_new_int(0);
	mp_obj_t freq = mp_obj_new_int(1000000);
	mp_obj_t args[] = {id, freq};
	mp_obj_t s = machine_hw_i2c_type.make_new(&machine_hw_i2c_type, 2, 0, args);
	i2c = (mp_obj_base_t *)MP_OBJ_TO_PTR(s);
	i2cproto = (mp_machine_i2c_p_t *)i2c->type->protocol;

	id = mp_obj_new_int(RESET_PIN);
	mp_obj_t mode = mp_obj_new_int(1);
	mp_obj_t pargs[] = {id, mode};
	mp_obj_t r = machine_pin_type.make_new(&machine_pin_type, 2, 0, pargs);
	resetPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(r);
	pinproto = (mp_pin_p_t *)machine_pin_type.protocol;

	// Reset display
	pinproto->ioctl(resetPin, 2, 0, NULL);
	mp_hal_delay_ms(1);
	pinproto->ioctl(resetPin, 2, 1, NULL);

	// Wire.begin();
	// Wire.setClock(10000000);
	// delay(200);

	/* Send display configuration through I2C */
	// Wire.beginTransmission(DISPLAY_ADDRESS);
	// Wire.write((uint8_t)0x00);
	// Wire.write(INIT_COMMANDS, INIT_COMMANDS_SIZE);
	// Wire.endTransmission();

	uint8_t pre[] = {0x00};
	i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 1, pre, 0x00);
	i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, INIT_COMMANDS_SIZE, INIT_COMMANDS, i2cFlags);
	// i2cproto->transfer(i2c, DISPLAY_ADDRESS, INIT_COMMANDS_SIZE, INIT_COMMANDS, i2cFlags);

	/* Clear the whole display */
	uint8_t tempBuff[DISPLAY_COLUMNS];
	for (int index = 0; index < DISPLAY_COLUMNS; index++)
	{
		tempBuff[index] = 0;
	}

	/* Send the black screen to clear the display */
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {uint8_t(0xB0 + page), 0x00, 0x10};
		uint8_t pre[] = {0x00};
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 1, pre, 0x00);
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 3, setPageCmd, i2cFlags);
		// Wire.beginTransmission(DISPLAY_ADDRESS);
		// Wire.write((uint8_t)0x00);
		// Wire.write(setPageCmd, 3);
		// Wire.endTransmission();

		uint8_t cmd[] = {0x40};
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 1, cmd, 0x00);
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, DISPLAY_COLUMNS, tempBuff, i2cFlags);
		// Wire.beginTransmission(DISPLAY_ADDRESS);
		// Wire.write((uint8_t)0x40);
		// Wire.write(tempBuff, DISPLAY_COLUMNS);
		// Wire.endTransmission();
	}
}

void hwDisplaySend()
{
	for (int page = 0; page < 8; page++)
	{
		uint8_t setPageCmd[] = {uint8_t(0xB0 + page), DISPLAY_STARTCOL, 0x10};
		uint8_t pre[] = {0x00};
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 1, pre, 0x00);
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 3, setPageCmd, i2cFlags);
		// Wire.beginTransmission(DISPLAY_ADDRESS);
		// Wire.write((uint8_t)0x00);
		// Wire.write(setPageCmd, 3);
		// Wire.endTransmission();

		uint8_t cmd[] = {0x40};
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, 1, cmd, 0x00);
		i2cproto->transfer_single(i2c, DISPLAY_ADDRESS, DISPLAY_COLUMNS, displayBuffer + (page * 128), i2cFlags);
		// Wire.beginTransmission(DISPLAY_ADDRESS);
		// Wire.write((uint8_t)0x40);
		// Wire.write(displayBuffer + (page * 128), 128);
		// Wire.endTransmission();
	}
}

#endif

#endif
#endif
