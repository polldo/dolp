#include "dolp.h"

const uint8_t arduinoImg[] = {0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c};
const uint8_t maskImg[] = {0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c};

void setup()
{
	dolp.begin();

	randomSeed(analogRead(0));

	for (int i = 0; i < 10; i++)
	{
		auto e = dolp.newEntity();
		e.configure(random(dolp.width()), random(dolp.height()), 10, 10);
		e.update(logoUpdate);
		e.setImage(arduinoImg, maskImg);
	}
}

void loop()
{
	dolp.loopBegin();

	dolp.loopEnd();
}

void logoUpdate(PEntity logo)
{
	if (!logo.isMoving())
	{
		logo.moveTo(random(dolp.width()), random(dolp.height()), 6);
	}
}
