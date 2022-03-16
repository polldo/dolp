#include "hardware/HwConfiguration.h"
#if defined(ARDUINO_NANO33BLE)

#if defined(DISPLAY_ST7735)

#include "hardware/HwDisplay.h"
#include "Arduino.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 160
#define DISPLAY_LENGTH (DISPLAY_WIDTH * DISPLAY_HEIGHT)

#define CS 9
#define DC 10

#define SPI_DATA_MODE() (digitalWrite(DC, HIGH))
#define SPI_COMMAND_MODE() (digitalWrite(DC, LOW))

#include <hal/nrf_spim.h>
#define NRF_SPIM (NRF_SPIM_Type *)NRF_SPIM3

struct Command
{
  uint8_t opcode;
  uint8_t dataLength;
  uint8_t *data;
  uint16_t delay;
};

static uint16_t INIT_COMMANDS[] =
    {
        0x3a, 1, 0x05, 0, // pixel format RGB565
        0xe0, 16,         // Gamma Adjustments
        0x09, 0x16, 0x09, 0x20,
        0x21, 0x1B, 0x13, 0x19,
        0x17, 0x15, 0x1E, 0x2B,
        0x04, 0x05, 0x02, 0x0E,
        0,
        0xe1, 16, // Gamma Adjustments
        0x0B, 0x14, 0x08, 0x1E,
        0x22, 0x1D, 0x18, 0x1E,
        0x1B, 0x1A, 0x24, 0x2B,
        0x06, 0x06, 0x02, 0x0F,
        10,
        0x36, 1, 0xc8, 0, // Memory data access control
        0x11, 0, 120,     // Sleep out
        0x29, 0, 10,      // Display on
        0x2a, 1, 0x00, 0, // Column address set
        0x2b, 1, 0x00, 0, // Row address set
        0x2c, 0, 0        // Memory write
};
static uint8_t INIT_COMMANDS_LENGTH = 9;

extern uint16_t displayBuffer[DISPLAY_LENGTH];

static void sendCommand(Command &cmd);

void spiInit(uint32_t sck, uint32_t mosi, uint32_t miso)
{
  nrf_gpio_pin_clear(mosi);

  nrf_gpio_cfg(mosi,
               NRF_GPIO_PIN_DIR_OUTPUT,
               NRF_GPIO_PIN_INPUT_DISCONNECT,
               NRF_GPIO_PIN_NOPULL,
               // Use High Drive because SPIM3 is used
               NRF_GPIO_PIN_H0H1,
               NRF_GPIO_PIN_NOSENSE);

  nrf_gpio_cfg(sck,
               NRF_GPIO_PIN_DIR_OUTPUT,
               NRF_GPIO_PIN_INPUT_CONNECT,
               NRF_GPIO_PIN_NOPULL,
               // Use High Drive because SPIM3 is used
               NRF_GPIO_PIN_H0H1,
               NRF_GPIO_PIN_NOSENSE);

  nrf_spim_pins_set(NRF_SPIM, sck, mosi, 0xFF);
  nrf_spim_frequency_set(NRF_SPIM, NRF_SPIM_FREQ_32M);
  nrf_spim_configure(NRF_SPIM, NRF_SPIM_MODE_0, NRF_SPIM_BIT_ORDER_MSB_FIRST);
  nrf_spim_orc_set(NRF_SPIM, 0xFF);
  nrf_spim_int_disable(NRF_SPIM, NRF_SPIM_ALL_INTS_MASK);
  nrf_spim_enable(NRF_SPIM);
}

void spiTransfer(const uint8_t *data, uint32_t len)
{
  nrf_spim_event_clear(NRF_SPIM, NRF_SPIM_EVENT_ENDTX);
  nrf_spim_tx_buffer_set(NRF_SPIM, data, len);
  nrf_spim_task_trigger(NRF_SPIM, NRF_SPIM_TASK_START);
  while (!nrf_spim_event_check(NRF_SPIM, NRF_SPIM_EVENT_ENDTX))
    ;
}

void sendCommand(Command &cmd)
{
  SPI_COMMAND_MODE();
  spiTransfer(&cmd.opcode, 1);
  SPI_DATA_MODE();
  spiTransfer(cmd.data, cmd.dataLength);
  if (cmd.delay)
    delay(cmd.delay);
}

void hwDisplaySetup()
{
  pinMode(CS, OUTPUT);
  pinMode(DC, OUTPUT);
  digitalWrite(CS, LOW); // Enable slave

  spiInit(P0_13, P1_1, P1_8);

  Command cmd;
  // copy command arguments in RAM as per easydma transfer requirements
  uint8_t ramData[32];
  cmd.data = ramData;

  uint8_t index = 0;
  for (uint8_t i = 0; i < INIT_COMMANDS_LENGTH; i++)
  {
    cmd.opcode = INIT_COMMANDS[index++];
    cmd.dataLength = INIT_COMMANDS[index++];
    if (cmd.dataLength)
    {
      memcpy(ramData, &INIT_COMMANDS[index], cmd.dataLength);
      index += cmd.dataLength;
    }
    cmd.delay = INIT_COMMANDS[index++];
    sendCommand(cmd);
  }

  hwDisplaySend();
}

void hwDisplaySend()
{
  spiTransfer((uint8_t *)displayBuffer, DISPLAY_LENGTH * 2);
}

#endif

#endif
