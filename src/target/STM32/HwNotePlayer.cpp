#include <hardware/HwNotePlayer.h>
#include "stm32_def.h"

#define FREQUENCY_TIMER TIM3
#define DURATION_TIMER TIM4

static void frequencyTimerSetup();
static void durationTimerSetup();

uint8_t vol;
uint16_t currentSongSize;
Note *currentSongNotes;
volatile uint16_t currentSongIndex;
uint16_t currentSongStartIndex;
bool currentSongLoop;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
void TIM4_IRQHandler(void)
{
	FREQUENCY_TIMER->CR1 &= ~TIM_CR1_CEN;
	DURATION_TIMER->CR1 &= ~TIM_CR1_CEN;
	DURATION_TIMER->SR &= ~TIM_SR_UIF;
	/* Configure frequency and duration timer according to the next note */
	if (currentSongIndex < currentSongSize)
	{
		Note tempNote = currentSongNotes[currentSongIndex];
		if (tempNote.frequency)
		{
			/* Setup and restart frequency timer */
			FREQUENCY_TIMER->ARR = tempNote.frequency;
			FREQUENCY_TIMER->CCR2 = (tempNote.frequency / 2) * vol / 100 ;
			FREQUENCY_TIMER->CR1 |= TIM_CR1_CEN;
		}
		/* Setup and restart duration timer */
		DURATION_TIMER->CNT = 0;
		DURATION_TIMER->ARR = tempNote.duration * 10; /* period = duration ms */
		DURATION_TIMER->CR1 |= TIM_CR1_CEN;
		/* Update note index */
		currentSongIndex++;
	} else if(currentSongLoop)
	{
		currentSongIndex = currentSongStartIndex;
		DURATION_TIMER->CNT = 0;
		DURATION_TIMER->ARR = 1;
		DURATION_TIMER->CR1 |= TIM_CR1_CEN;
	}
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

static void frequencyTimerSetup()
{
	/* Enable FREQUENCY_TIMER clock -> FREQUENCY TIMER */
	__HAL_RCC_TIM3_CLK_ENABLE();
	/* FREQUENCY_TIMER GPIO Configuration
    	PA7     ------> TIM3_CH2
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	/* FREQUENCY_TIMER base setup */
	FREQUENCY_TIMER->PSC = 40;   /* Prescaler 40 -> timer clock =  2MHz*/
	FREQUENCY_TIMER->ARR = 3974; /* Period = CLK/(ARR*PSC) */
	FREQUENCY_TIMER->DIER = TIM_DIER_UIE;
	/* FREQUENCY_TIMER PWM ch2 setup */
	FREQUENCY_TIMER->CCER &= ~TIM_CCER_CC2E;
	FREQUENCY_TIMER->CCMR1 &= ~ (TIM_CCMR1_OC2M | TIM_CCMR1_CC2S);
	FREQUENCY_TIMER->CCMR1 |= ((TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1) << 8U);//(TIM_OCMODE_PWM1 << 8U);
	FREQUENCY_TIMER->CCER &= ~TIM_CCER_CC2P;
	FREQUENCY_TIMER->CCER |= (0x00000000U << 4U);//(TIM_OCPOLARITY_HIGH << 4U);
	FREQUENCY_TIMER->CCR2 = 1800; /* Duty Cycle */
	/* Set the Preload enable bit for channel2 */
	FREQUENCY_TIMER->CCMR1 |= TIM_CCMR1_OC2PE;
	/* Configure the Output Fast mode */
	FREQUENCY_TIMER->CCMR1 &= ~TIM_CCMR1_OC2FE;
	FREQUENCY_TIMER->CCMR1 |= 0x00000000U << 8U;//TIM_OCFAST_DISABLE << 8U;
	/* Reset the CCxE Bit and activate the channel */
	FREQUENCY_TIMER->CCER &= ~(TIM_CCER_CC1E << (0x00000004U & 0x1FU)); // TIM_CHANNEL_2 == 0x00000004U
	FREQUENCY_TIMER->CCER |= (uint32_t)(0x00000001U << (0x00000004U & 0x1FU)); // TIM_CHANNEL_2 == 0x00000004U -- TIM_CCx_ENABLE == 0x00000001U
}

static void durationTimerSetup()
{
	/* DURATION_TIMER Clock enable */
	__HAL_RCC_TIM4_CLK_ENABLE();
	/* DURATION_TIMER interrupt Init */
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	/* DURATION_TIMER setup */
	DURATION_TIMER->ARR = 10;
	DURATION_TIMER->PSC = 8000; /* clk@80MHz -> 100 us per tick */
	DURATION_TIMER->DIER = TIM_DIER_UIE;
	/* DURATION_TIMER start */
	//DURATION_TIMER->CR1 =	TIM_CR1_CEN;
}

void hwNotePlayerSetup()
{
	frequencyTimerSetup();
	durationTimerSetup();
}

void hwNotePlayerStart()
{
	DURATION_TIMER->CNT = 0;
	DURATION_TIMER->ARR = 1;
	DURATION_TIMER->CR1 |= TIM_CR1_CEN;
}

void hwNotePlayerStop()
{
	FREQUENCY_TIMER->CR1 &= ~TIM_CR1_CEN;
	DURATION_TIMER->CR1 &= ~TIM_CR1_CEN;
}

void hwNotePlayerVolume(uint8_t volume)
{
	vol = volume;
}

void hwNotePlayerSong(Note* notes, uint16_t size, uint16_t startIndex, bool loopEn)
{
	currentSongNotes = notes;
	currentSongSize = size;
	currentSongIndex = startIndex;
	currentSongStartIndex = startIndex;
	currentSongLoop = loopEn;
}
