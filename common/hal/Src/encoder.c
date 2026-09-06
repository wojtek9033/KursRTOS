/*
 * encoder.c
 *
 *  Created on: May 20, 2026
 *      Author: wojci
 */


#include "encoder.h"
#include "stm32f4xx.h"
#include "cmsis_helpers.h"
#include <stddef.h>

static void (*_encoderCallback)(int32_t) = NULL;
static volatile uint8_t _prevAB;

/*
 * A B ret
 * 0 0 0
 * 0 1 1
 * 1 0 2
 * 1 1 3
 */

static uint8_t _readAB()
{
	uint32_t idr = GPIOC->IDR; // read GPIOC register
	uint8_t ab = 0;

	if (idr & (1<<11))
	{
		ab |= 0x2;
	}
	if (idr & (1<<12))
	{
		ab |= 0x1;
	}

	return ab;
}

HAL_Status_t halEncoderInit()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* PC.11 and PC.12 as input pull-up */
	FILL_REG(GPIOC->MODER, GPIO_MODER_MODER11, GPIO_MODER_INPUT); // pin as input
	FILL_REG(GPIOC->PUPDR, GPIO_PUPDR_PUPD11, GPIO_PUPDR_PUP); // pull up

	FILL_REG(GPIOC->MODER, GPIO_MODER_MODER12, GPIO_MODER_INPUT); // pin as input
	FILL_REG(GPIOC->PUPDR, GPIO_PUPDR_PUPD12, GPIO_PUPDR_PUP); // pull up

	/* this MCU has multiplexed interrupt system to which we can connect
	 * multiple pins, so we need to Map EXTI11 and EXTI12 to GPIOC*/
	FILL_REG(SYSCFG->EXTICR[2], SYSCFG_EXTICR3_EXTI11, SYSCFG_EXTI_PC);
	FILL_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI12, SYSCFG_EXTI_PC);

	/* Clear interrupt flags */
	EXTI->PR = (EXTI_PR_PR11 | EXTI_PR_PR12);

	/* Turn-on EXTI11 and EXTI12 on both slopes */
	EXTI->IMR |= (EXTI_IMR_IM11 | EXTI_IMR_IM12);
	EXTI->RTSR |= (EXTI_RTSR_TR11 | EXTI_RTSR_TR12); // rising edge
	EXTI->FTSR |= (EXTI_FTSR_TR11 | EXTI_FTSR_TR12); // falling edge

	NVIC_SetPriority(EXTI15_10_IRQn, 15);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	_prevAB = _readAB();

	return HAL_OK;
}

HAL_Status_t halEncoderRegisterCallback(void (*callback)(int32_t))
{
	_encoderCallback = callback;
	return HAL_OK;
}

/*
 * example rotation:
 * A B
 * 0 0 0
 * 0 1 1
 * 1 1 3
 * 1 0 2
 * 0 0 0
 * 0 1 1
 * 1 1 3
 * 1 0 2
 */

void EXTI15_10_IRQHandler(void)
{
	// interrupt can be from different source, so check if its the right one:
	if (EXTI->PR & (EXTI_PR_PR11 | EXTI_PR_PR12))
	{
		EXTI->PR = (EXTI_PR_PR11 | EXTI_PR_PR12);

		uint8_t newAB = _readAB();

		int32_t dir = 0;
		if (_prevAB == 0 && newAB == 1)
		{
			dir = 1;
		}
		else if (_prevAB == 1 && newAB == 3)
		{
			dir = 1;
		}
		else if (_prevAB == 3 && newAB == 2)
		{
			dir = 1;
		}
		else if (_prevAB == 2 && newAB == 0)
		{
			dir = 1;
		}

		else if (_prevAB == 0 && newAB == 2)
		{
			dir = -1;
		}
		else if (_prevAB == 2 && newAB == 3)
		{
			dir = -1;
		}
		else if (_prevAB == 3 && newAB == 1)
		{
			dir = -1;
		}
		else if (_prevAB == 1 && newAB == 0)
		{
			dir = -1;
		}

		_prevAB = newAB;


		if (_encoderCallback != NULL)
		{
			_encoderCallback(dir);
		}
	}
}

