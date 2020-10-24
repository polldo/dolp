#include <dolp.h>

World demo;

PEntity monster = demo.newEntity(); 

void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Start");

    GAME_ENGINE_SETUP();

    engine.setWorld(demo);
    monster.configure(50, 20, 8, 8);
}

void loop()
{
    GAME_LOOP_BEGIN();

    static uint8_t frameCounter = 0;
    static uint64_t seconds = 0;
    static uint8_t color = 0x33;

    if (joystick.pressed(ButtonA)) {

    }

    frameCounter++;
    if (frameCounter == 30)
    {
        frameCounter = 0;
        seconds++;
    }

    GAME_LOOP_END();
}
