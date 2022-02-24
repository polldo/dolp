#include "hardware/HwConfiguration.h"
#if defined (ARDUINO_NANO33BLE)

#include "hardware/HwJoystick.h"
#include "Arduino.h"

#define NO_DEBOUNCE

#ifdef SLOW_DEBOUNCE
#define DEBOUNCE_TOLERANCE 4
#define DEBOUNCE_MASK (0xFFU << DEBOUNCE_TOLERANCE)
#endif

static void pollButtons();
static inline void readButton(JoystickButton button, uint8_t buttonPin, uint8_t &buttonCount);

#define BUTTON_A_PIN 0
uint8_t buttonACount = 0;
#define BUTTON_B_PIN 1
uint8_t buttonBCount = 0;
#define BUTTON_UP_PIN 2
uint8_t buttonUpCount = 0;
#define BUTTON_DOWN_PIN 3
uint8_t buttonDownCount = 0;
#define BUTTON_RIGHT_PIN 4
uint8_t buttonRightCount = 0;
#define BUTTON_LEFT_PIN 5
uint8_t buttonLeftCount = 0;
//#define BUTTON_START_PIN 2
//uint8_t buttonStartCount = 0;
//#define BUTTON_SELECT_PIN 3
//uint8_t buttonSelectCount = 0;

ButtonStateType buttonState;

#ifndef NO_DEBOUNCE
using namespace std::chrono_literals;
using namespace std::chrono;
mbed::Ticker debounceTimer;
#endif

static void pollButtons()
{
	readButton(ButtonA, BUTTON_A_PIN, buttonACount);
	readButton(ButtonB, BUTTON_B_PIN, buttonBCount);
	readButton(ButtonUp, BUTTON_UP_PIN, buttonUpCount);
	readButton(ButtonDown, BUTTON_DOWN_PIN, buttonDownCount);
	readButton(ButtonRight, BUTTON_RIGHT_PIN, buttonRightCount);
	readButton(ButtonLeft, BUTTON_LEFT_PIN, buttonLeftCount);
	//readButton(ButtonStart, BUTTON_START_PIN, buttonStartCount);
	//readButton(ButtonSelect, BUTTON_SELECT_PIN, buttonSelectCount);
}

static inline void readButton(JoystickButton button, uint8_t buttonPin, uint8_t &buttonCount)
{
	ButtonStateType tempButtonState = digitalRead(buttonPin);
	//buttonCount = (buttonCount << 1) | tempButtonState;

#if defined (SLOW_DEBOUNCE)
	if ( (buttonCount | (uint8_t)(~DEBOUNCE_MASK)) == 0xFF)
		buttonState |= (1U << button);
	else if ( (buttonCount & (uint8_t)(DEBOUNCE_MASK)) == 0x00)
		buttonState &= ~ (1U << button);
#elif defined (FAST_DEBOUNCE) 
	if (buttonCount == 0xFF)
		buttonState |= (1U << button);
	else if (buttonCount == 0x00)
		buttonState &= ~ (1U << button);
#elif defined (NO_DEBOUNCE)
	if (tempButtonState)
		buttonState |= (1U << button);
	else
		buttonState &= ~ (1U << button);
#endif
}

void hwJoystickSetup()
{
  buttonState = 0x00;
	pinMode(BUTTON_A_PIN, INPUT);
	pinMode(BUTTON_B_PIN, INPUT);
	pinMode(BUTTON_UP_PIN, INPUT);
	pinMode(BUTTON_DOWN_PIN, INPUT);
	pinMode(BUTTON_RIGHT_PIN, INPUT);
	pinMode(BUTTON_LEFT_PIN, INPUT);
#if defined (SLOW_DEBOUNCE)
	debounceTimer.attach(pollButtons, 8ms);
#elif defined (FAST_DEBOUNCE)
  debounceTimer.attach(pollButtons, 4ms);
#endif
}

ButtonStateType hwJoystickState()
{
#if defined (NO_DEBOUNCE)
	pollButtons();
#endif
  return buttonState;
}

#endif
