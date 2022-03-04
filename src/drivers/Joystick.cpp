#include <drivers/Joystick.h>
#include <hardware/HwJoystick.h>

Joystick::Joystick() : _buttonStateOld(0x00),
					   _buttonPressed(0x00)
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
	ButtonStateType buttonStateCurrent = hwJoystickState();
	/* Check whether some button has been pressed */
	_buttonPressed = (_buttonStateOld ^ buttonStateCurrent) & (buttonStateCurrent ^ 0x00);
	/* Update old button values */
	_buttonStateOld = buttonStateCurrent;
}

bool Joystick::held(JoystickButton button)
{
	return (hwJoystickState() & (1 << button));
}

bool Joystick::pressed(JoystickButton button)
{
	return (_buttonPressed & (1 << button));
}
