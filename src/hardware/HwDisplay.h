#ifndef HW_DISPLAY_H_
#define HW_DISPLAY_H_

#include "Common.h"

enum DisplayColor {
  BLACK_COLOR = 0,
  WHITE_COLOR = 1
};

void hwDisplaySetup();

void hwDisplaySend();

void hwDisplayDraw(uint8_t x, uint8_t y, DisplayColor color);
void hwDisplayDrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, DisplayColor color);
void hwDisplayDrawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t* image);
void hwDisplayFill(DisplayColor color);

uint8_t hwDisplayWidth();
uint8_t hwDisplayHeight();

#endif /* HW_DISPLAY_H_ */
