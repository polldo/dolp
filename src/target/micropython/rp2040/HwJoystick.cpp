#include "hardware/HwConfiguration.h"
#if defined(MICROPYTHON)

#include "hardware/HwJoystick.h"
#include "Common.h"

#include <string>

extern "C"
{
#include <extmod/virtpin.h>
#include <ports/rp2/modmachine.h>
#include <py/obj.h>
#include <py/mphal.h>
}

static void pollButtons();
static inline void readButton(JoystickButton button, mp_obj_base_t *buttonPin);

static mp_pin_p_t *pinproto;
#define BUTTON_A_PIN 25
static mp_obj_base_t *aPin;
#define BUTTON_B_PIN 15
static mp_obj_base_t *bPin;
#define BUTTON_C_PIN 16
static mp_obj_base_t *cPin;
#define BUTTON_D_PIN 17
static mp_obj_base_t *dPin;

ButtonStateType buttonState;

static void pollButtons()
{
	readButton(ButtonA, aPin);
	readButton(ButtonB, bPin);
	readButton(ButtonC, cPin);
	readButton(ButtonD, dPin);
}

static inline void readButton(JoystickButton button, mp_obj_base_t *buttonPin)
{
	ButtonStateType tempButtonState = pinproto->ioctl(buttonPin, 1, 0, NULL);
	if (tempButtonState)
		buttonState |= (1U << button);
	else
		buttonState &= ~(1U << button);
}

void hwJoystickSetup()
{
	pinproto = (mp_pin_p_t *)machine_pin_type.protocol;
	mp_obj_t id = mp_obj_new_int(BUTTON_A_PIN);
	mp_obj_t mode = mp_obj_new_int(0);
	mp_obj_t args[] = {id, mode};
	mp_obj_t a = machine_pin_type.make_new(&machine_pin_type, 2, 0, args);
	aPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(a);

	args[0] = mp_obj_new_int(BUTTON_B_PIN);
	mp_obj_t b = machine_pin_type.make_new(&machine_pin_type, 2, 0, args);
	bPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(b);

	args[0] = mp_obj_new_int(BUTTON_C_PIN);
	mp_obj_t c = machine_pin_type.make_new(&machine_pin_type, 2, 0, args);
	cPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(c);

	args[0] = mp_obj_new_int(BUTTON_D_PIN);
	mp_obj_t d = machine_pin_type.make_new(&machine_pin_type, 2, 0, args);
	dPin = (mp_obj_base_t *)MP_OBJ_TO_PTR(d);

	buttonState = 0x00;
}

ButtonStateType hwJoystickState()
{
	pollButtons();
	return buttonState;
}

#endif
