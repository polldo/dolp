#ifndef _HW_CONFIGURATION_H_
#define _HW_CONFIGURATION_H_

// Lib defines
//#define _STM32_DUINO_
//#define _STM32_HAL_
//#include "stm32_def.h"
#if defined(ARDUINO_ARDUINO_NANO33BLE)
#define ARDUINO_NANO33BLE
#endif

// Display defines
// #define DISPLAY_ST7735
//#define DISPLAY_SSD1306
#define DISPLAY_SH1106
#define DISPLAY_I2C
// #define DISPLAY_SPI

// FPS defines
#define FPS 60
#define FRAME_MSEC 16

#define PROFILING

#endif