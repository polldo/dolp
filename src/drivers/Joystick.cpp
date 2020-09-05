#include <Joystick.h>
#include <HwJoystick.h>

Joystick::Joystick() :
	_buttonPressed(0x00),
	_buttonStateOld(0x00)
{
}

Joystick::~Joystick() 
{
}

void Joystick::setup()
{
	hwJoystickSetup();
}

/* Must be called at the beginning of every frame */
void Joystick::update()
{
	/* Sample button state to prevent abnormalities */
	uint8_t buttonStateCurrent = hwJoystickState();
	/* Check whether some button has been pressed */
	_buttonPressed = (_buttonStateOld ^ buttonStateCurrent) & (buttonStateCurrent ^ 0x00);
	/* Update old button values */ 
	_buttonStateOld = buttonStateCurrent;
}

uint8_t Joystick::held(uint8_t button)
{
	return (hwJoystickState() & (1 << button));
}

uint8_t Joystick::pressed(uint8_t button)
{
	return (_buttonPressed & (1 << button));
}
