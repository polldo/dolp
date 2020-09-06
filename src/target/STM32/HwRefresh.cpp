#include <hardware/HwRefresh.h>
#include "stm32_def.h"

volatile bool refreshFlag = false;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void TIM1_UP_TIM16_IRQHandler()
{
	TIM1->SR &= ~TIM_DIER_UIE;
	refreshFlag = true;
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplu

void hwRefreshSetup()
{
	/* TIM1 Clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
	/* TIM1 setup */
#ifdef REFRESH_60HZ
    /* Refresh set to 60 Hz */
	TIM1->ARR = 1666;
#else
    /* Refresh set to 30 Hz */
	TIM1->ARR = 3332;
#endif
	TIM1->PSC = 800;
	TIM1->DIER = TIM_DIER_UIE;
	/* TIM1 start */
	TIM1->CR1 =	TIM_CR1_CEN;
}

bool hwRefreshGet()
{
	return refreshFlag;
}

void hwRefreshReset()
{
	refreshFlag = false;
}
