#include <hardware/HwJoystick.h>
#include "stm32_def.h"

#define BUTTON_PORT GPIOC
#define BUTTON_A_PIN GPIO_PIN_1
#define BUTTON_B_PIN GPIO_PIN_0
#define BUTTON_A 0
#define BUTTON_B 1

volatile ButtonStateType button_state;

volatile uint8_t button_a_count = 0x10;
volatile uint8_t button_b_count = 0x10;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	/* Button A debounce */
	ButtonStateType temp_button_state = HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_A_PIN);
	button_a_count = (button_a_count << 1) | temp_button_state;
	if (button_a_count == 0xFF)
		button_state |= (1U << BUTTON_A);
	else if (!button_a_count)
		button_state &= ~ (1U << BUTTON_A);
	/* Button B debounce */
	temp_button_state = HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_B_PIN);
	button_b_count = (button_b_count << 1) | temp_button_state;
	if (button_b_count == 0xFF)
		button_state |= (1U << BUTTON_B);
	else if (!button_b_count)
		button_state &= ~ (1U << BUTTON_B);
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplu

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
	return button_state;
}
