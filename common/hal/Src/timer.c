#include "timer.h"
#include "stm32f4xx.h"
#include "cmsis_helpers.h"
#include <stddef.h>

static volatile void (*_timerCallback)(void) = NULL;

HAL_Status_t halTimerInit(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//          	   16000000 / 1000000
	TIM2->PSC = SystemCoreClock / 1000000 - 1; // increment timer by 1us
	TIM2->ARR = 999; // Auto-Reload: Generate interrupt after counting 1000 (0 to 999), means 1000us = 1ms

	TIM2->SR = 0;
	TIM2->EGR = TIM_EGR_UG; // Force timer to "reload"

	TIM2->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM2_IRQn, 15); // LOWEST* possible priority of Interrupt of this MCU
	NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupts

	return HAL_OK;
}

HAL_Status_t halTimerStart(void)
{
	TIM2->CR1 |= TIM_CR1_CEN;
	return HAL_OK;
}

HAL_Status_t halTimerSetInterruptPriority(uint32_t priority)
{
	NVIC_SetPriority(TIM2_IRQn, priority);
	return HAL_OK;
}
HAL_Status_t halTimerRegisterCallback(void (*callback) (void))
{
	_timerCallback = callback;
	return HAL_OK;
}

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF)
	{
		TIM2->SR &= ~TIM_SR_UIF;

		if (_timerCallback != NULL)
			_timerCallback();
	}
}
