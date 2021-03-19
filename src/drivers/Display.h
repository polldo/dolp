#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Common.h>
#include "hardware/HwDisplay.h"

class Display {
public:
  Display();
  virtual ~Display();

  void setup();

  void send();

  void draw(int x, int y, DisplayColor color);
  void drawImage(int x, int y, uint8_t w, uint8_t h, const uint8_t* image);
  void drawImage(int x, int y, uint8_t w, uint8_t h, const uint8_t* image, const uint8_t* mask);
  void drawImage(int x, int y, uint8_t w, uint8_t h, const uint16_t* image);
  void drawRectangle(int x, int y, uint8_t width, uint8_t height, DisplayColor color);
  void fill(DisplayColor color);

  uint8_t width();
  uint8_t height();
};

#endif /* DISPLAY_H_ */
