#include <dolp.h>
#include "Painter.h"
#include "Sound.h"

//Painter paint_1(50, 50, Up);
Painter paint_1(20, 30, Right);
//Painter paint_2(2, 10, Right);
Painter paint_2(127, 0, Up);
Painter paint_3(0, 0, Up);

void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Start");

    GAME_ENGINE_SETUP();

    notePlayer.setVolume(1);

    notePlayer.play(song_1, true);
}

void loop()
{
    GAME_LOOP_BEGIN();

    static uint8_t frameCounter = 0;
    static uint64_t seconds = 0;
    static uint8_t color = 0x33;

    /* Demo song logic every 10 sec */
    //if (! (seconds % 10) )
        //notePlayer.play(song_1);

    Serial.println(joystick.held(ButtonA));
    if (joystick.pressed(ButtonA))
        paint_1.changeDirection();

    paint_1.move();
    paint_1.draw();
    paint_2.move();
    paint_2.draw();
    paint_3.move();
    paint_3.draw();

    frameCounter++;
    if (frameCounter == 30)
    {
        frameCounter = 0;
        seconds++;
    }

    GAME_LOOP_END();
}
