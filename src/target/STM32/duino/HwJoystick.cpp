#include "hardware/HwConfiguration.h"
#if defined (_STM32_DUINO_)

#include <hardware/HwJoystick.h>
#include <Arduino.h>
#include <HardwareTimer.h>

#define BUTTON_PORT (GPIOC)
#define BUTTON_A_PIN (PC0)
#define BUTTON_B_PIN (PC1)
#define BUTTON_A 0
#define BUTTON_B 1

#define DEBOUNCE_TIMER (TIM6)
HardwareTimer _debounceTimer (DEBOUNCE_TIMER);

void debounceCallback();

volatile ButtonStateType buttonState;
volatile uint8_t buttonACount = 0x10;
volatile uint8_t buttonBCount = 0x10;

void debounceCallback()
{
	/* Button A debounce */
	ButtonStateType tempButtonState = digitalRead(BUTTON_A_PIN);
	buttonACount = (buttonACount << 1) | tempButtonState;
	if (buttonACount == 0xFF)
		buttonState |= (1U << BUTTON_A);
	else if (!buttonACount)
		buttonState &= ~ (1U << BUTTON_A);
	/* Button B debounce */
	tempButtonState = digitalRead(BUTTON_B_PIN);
	buttonBCount = (buttonBCount << 1) | tempButtonState;
	if (buttonBCount == 0xFF)
		buttonState |= (1U << BUTTON_B);
	else if (!buttonBCount)
		buttonState &= ~ (1U << BUTTON_B);
}

void hwJoystickSetup()
{
    _debounceTimer.setMode(1, TIMER_OUTPUT_COMPARE);  
    _debounceTimer.attachInterrupt(debounceCallback);
	_debounceTimer.setPrescaleFactor(8000);
	_debounceTimer.setOverflow(10, TICK_FORMAT); 
	_debounceTimer.resume();

	pinMode(BUTTON_A_PIN, INPUT);
	pinMode(BUTTON_B_PIN, INPUT);
}

ButtonStateType hwJoystickState()
{
	return buttonState;
}

#endif
