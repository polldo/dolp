#include <dolp.h>
#include "Painter.h"
#include "Sound.h"

Painter paint_1(0, 10, Down);

void setup()
{
    //Serial.begin(115200);

    GAME_ENGINE_SETUP();

    notePlayer.setVolume(1);
}

void loop()
{
    GAME_LOOP_BEGIN();

    static uint8_t frameCounter = 0;
    static uint64_t seconds = 0;
    static uint8_t color = 0x33;

    /* Demo song logic every 10 sec */
    if (! (seconds % 10) )
        notePlayer.play(song_1);

    if (joystick.pressed(ButtonA))
        paint_1.changeDirection();

    paint_1.move();
    paint_1.draw();

    frameCounter++;
    if (frameCounter == 30)
    {
        frameCounter = 0;
        seconds++;
    }

    GAME_LOOP_END();
}
