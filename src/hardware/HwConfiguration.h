#ifndef _HW_CONFIGURATION_H_
#define _HW_CONFIGURATION_H_

// Define the display you are using.
#define DISPLAY_SH1106
// #define DISPLAY_SSD1306
// #define DISPLAY_ST7735

// Define what kind of communication your display uses.
// #define DISPLAY_I2C
#define DISPLAY_SPI

// Define FPS you want to use. (and set the FRAME_MSEC accordingly)
#define FPS 60
#define FRAME_MSEC 16

// Uncomment this line to print at each loop the amount of milliseconds
// remained until the next end of frame.
// #define PROFILING

#endif