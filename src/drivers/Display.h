#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Common.h>

#define DISPLAY_LENGTH 1024

class Display {

public:
    Display();
    virtual ~Display();

    void fill(uint8_t color);

    void setup();

    void send();

    void draw(uint8_t x, uint8_t y, uint8_t color);

private:
    uint8_t _buffer[DISPLAY_LENGTH];
};

#endif /* DISPLAY_H_ */
