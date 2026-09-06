/*
 * pwm.c
 *
 *  Created on: May 17, 2026
 *      Author: wojci
 */

#include "pwm.h"
#include "cmsis_helpers.h"
#include "stm32f4xx.h"
#include <stddef.h>

static void (*_pwmUpdateCallback)(void) = NULL;

HAL_Status_t halPWMInit()
{
	// PWM Signals are connected to port B in our setup
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	// PB.4 as alternate function - PWM
	FILL_REG(GPIOB->MODER, GPIO_MODER_MODE4, GPIO_MODER_AF); // alternate function
	FILL_REG(GPIOB->AFR[0], GPIO_AFRL_AFSEL4, 2); // choose alternate function for pin 4, 2 = PWM

	// PB.1 and PB.2 as output - motor direction
	FILL_REG(GPIOB->MODER, GPIO_MODER_MODE1, GPIO_MODER_OUTPUT);
	FILL_REG(GPIOB->OTYPER, GPIO_OTYPER_OT1, GPIO_OTYPER_PUSH_PULL);

	FILL_REG(GPIOB->MODER, GPIO_MODER_MODE2, GPIO_MODER_OUTPUT);
	FILL_REG(GPIOB->OTYPER, GPIO_OTYPER_OT2, GPIO_OTYPER_PUSH_PULL);

	/* Configure timer TIM3 */
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	/* Disable TIM3 during config */
	TIM3->CR1 = 0;

	/* Set timer frequency to 2 kHz */
	TIM3->PSC = SystemCoreClock / 1000000 / 2 - 1; // prescaler - set the timer to count each 0.5 us
	TIM3->ARR = 999;// auto-reload register - to what value timer has to count (setpoint): 1000 * 0.5 us = 500us
	// f = 1/T = 1/500us = 1/0.0005s = 2000Hz = 2kHz, where 1000 is the number of quantization levels

	/* PWM config */
	FILL_REG(TIM3->CCMR1, TIM_CCMR1_OC1M, 6); // timer counts to some setpoint (ARR = 999). If in Timer value < CCR1 (duty parameter) result is 0, else 1.
	// so the above is exactly the PWM generation needed. In function halPWMSetDutyCycle(int32_t duty) we set this duty parameter.
	FILL_REG(TIM3->CCMR1, TIM_CCMR1_OC1PE, 1); // preload: if CCR1 changes, it will be visible in next impulse
	FILL_REG(TIM3->CCER, TIM_CCER_CC1E, 1); // enable PWM on channel 1 PB.4.

	/* Initial Duty cycle = 0 */
	TIM3->CCR1 = 0;

	/* Interrupts */
	TIM3->SR &= ~TIM_SR_UIF; // for safety clear interrupt flag in SR register
	TIM3->DIER |= TIM_DIER_UIE; // enable interrupts on each timer pulse generation

	NVIC_SetPriority(TIM3_IRQn, 15);
	NVIC_EnableIRQ(TIM3_IRQn);

	TIM3->EGR = TIM_EGR_UG; // update timer parameters
	TIM3->CR1 |= TIM_CR1_CEN; // start timer

	return HAL_OK;
}
HAL_Status_t halPWMStop()
{
	FILL_REG(GPIOB->ODR, GPIO_ODR_OD1, 0);
	FILL_REG(GPIOB->ODR, GPIO_ODR_OD2, 0);
	return HAL_OK;
}

HAL_Status_t halPWMForward()
{
	FILL_REG(GPIOB->ODR, GPIO_ODR_OD1, 1);
	FILL_REG(GPIOB->ODR, GPIO_ODR_OD2, 0);
	return HAL_OK;
}
HAL_Status_t halPWMBackward()
{
	FILL_REG(GPIOB->ODR, GPIO_ODR_OD1, 0);
	FILL_REG(GPIOB->ODR, GPIO_ODR_OD2, 1);
	return HAL_OK;
}
HAL_Status_t halPWMSetDutyCycle(int32_t duty)
{
	if (duty < 0)
	{
		duty = -duty;
		halPWMBackward();
	}
	else
	{
		halPWMForward();
	}
	if (duty > 1000)
	{
		duty = 1000;
	}

	TIM3->CCR1 = duty;

	return HAL_OK;
}

HAL_Status_t halPWMSetInterruptCallback(void (*callback)(void))
{
	_pwmUpdateCallback = callback;
	return HAL_OK;
}

void TIM3_IRQHandler(void)
{
	if (TIM3->SR & TIM_SR_UIF) // check if interrupt is from TIM3
	{
		TIM3->SR &= ~TIM_SR_UIF;  // if in register SR flag UIF is set (it is, if it is TIM3 interrupt), reset it.
		if (_pwmUpdateCallback != NULL)
		{
			_pwmUpdateCallback();
		}
	}
}
