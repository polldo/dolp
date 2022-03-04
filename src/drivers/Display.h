#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Common.h>
#include "hardware/HwDisplay.h"

class Display
{
public:
  Display();
  virtual ~Display();

  void setup();

  void send();

  void draw(uint8_t x, uint8_t y, DisplayColor color);
  void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *image);
  void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint16_t *image);
  void drawRectangle(uint8_t x, uint8_t y, uint8_t width, uint8_t height, DisplayColor color);
  void fill(DisplayColor color);

  uint8_t width();
  uint8_t height();
};

#endif /* DISPLAY_H_ */
