#ifdef _STM32_HAL_

#include <hardware/HwJoystick.h>

#define BUTTON_PORT GPIOC
#define BUTTON_A_PIN GPIO_PIN_1
#define BUTTON_B_PIN GPIO_PIN_0
#define BUTTON_A 0
#define BUTTON_B 1

volatile ButtonStateType buttonState;

volatile uint8_t buttonACount = 0x10;
volatile uint8_t buttonBCount = 0x10;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	/* Button A debounce */
	ButtonStateType tempButtonState = HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_A_PIN);
	buttonACount = (buttonACount << 1) | tempButtonState;
	if (buttonACount == 0xFF)
		buttonState |= (1U << BUTTON_A);
	else if (!buttonACount)
		buttonState &= ~ (1U << BUTTON_A);
	/* Button B debounce */
	tempButtonState = HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_B_PIN);
	buttonBCount = (buttonBCount << 1) | tempButtonState;
	if (buttonBCount == 0xFF)
		buttonState |= (1U << BUTTON_B);
	else if (!buttonBCount)
		buttonState &= ~ (1U << BUTTON_B);
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

void hwJoystickSetup()
{
	/* GPIO Port C clock enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	/* TIM2 Clock enable */
	__HAL_RCC_TIM2_CLK_ENABLE();
	/* TIM2 interrupt Init */
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	/* TIM2 setup */
	TIM2->ARR = 10;
	TIM2->PSC = 8000;
	TIM2->DIER = TIM_DIER_UIE;
	/* TIM2 start */
	TIM2->CR1 =	TIM_CR1_CEN;
	/* Configure GPIO pins */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = BUTTON_A_PIN|BUTTON_B_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
}

ButtonStateType hwJoystickState()
{
	return buttonState;
}

#endif
