/*
 * adc.c
 *
 *  Created on: May 16, 2026
 *      Author: wojci
 */

#include <stddef.h>

#include "adc.h"
#include "stm32f4xx.h"
#include "cmsis_helpers.h"

static void (*_adcCallback)(uint32_t*) = NULL;

HAL_Status_t halADCInit(void)
{
	/* Turn-on GPIOC and set PC10 as output with high level - for Analog Stick reference signal*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	FILL_REG(GPIOC->MODER, GPIO_MODER_MODER10, GPIO_MODER_OUTPUT);
	GPIOC->ODR |= (1<<10);

	/* Enable clock for GPIOA - connect clock to ADC */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/* Enable clock for ADC1 */
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	/* Set PA0, PA1, PC0 and PC1 as analog mode */
	FILL_REG(GPIOA->MODER, GPIO_MODER_MODER0, GPIO_MODER_ANALOG);
	FILL_REG(GPIOA->MODER, GPIO_MODER_MODER1, GPIO_MODER_ANALOG);
	FILL_REG(GPIOC->MODER, GPIO_MODER_MODER0, GPIO_MODER_ANALOG);
	FILL_REG(GPIOC->MODER, GPIO_MODER_MODER1, GPIO_MODER_ANALOG);

	/* Set ADC1 clock prescaler to 8 */
	FILL_REG(ADC->CCR, ADC_CCR_ADCPRE, 3);

	/* Set 12-bit resolution for ADC1*/
	FILL_REG(ADC1->CR1, ADC_CR1_RES, 0);

	/* Enable scan mode to be able to process data on 4 different channels */
	ADC1->CR1 |= ADC_CR1_SCAN;

	/* Set single conversion mode */
	ADC1->CR2 &= ~ADC_CR2_CONT;

	/* Set EOC after each conversion (bit EOC in status register) */
	ADC1->CR2 |= ADC_CR2_EOCS;

	/* Set sampling time for 15 cycles */
	FILL_REG(ADC1->SMPR2, ADC_SMPR2_SMP0, 1); // Channel 0
	FILL_REG(ADC1->SMPR2, ADC_SMPR2_SMP1, 1); // Channel 1
	FILL_REG(ADC1->SMPR1, ADC_SMPR1_SMP10, 1); // Channel 10
	FILL_REG(ADC1->SMPR1, ADC_SMPR1_SMP11, 1); // Channel 11

	/* Set number of channels in scan to 4 */
	FILL_REG(ADC1->SQR1, ADC_SQR1_L, 3);

	/* Configure sequence: PA0, PA1, PC0, PC1 */
	FILL_REG(ADC1->SQR3, ADC_SQR3_SQ1, 0);
	FILL_REG(ADC1->SQR3, ADC_SQR3_SQ2, 1);
	FILL_REG(ADC1->SQR3, ADC_SQR3_SQ3, 10);
	FILL_REG(ADC1->SQR3, ADC_SQR3_SQ4, 11);

	/* Enable ADC1 */
	ADC1->CR2 |= ADC_CR2_ADON;

	// for converter to get stable
	for (volatile int i = 0; i < 1000; i++);

	return HAL_OK;
}
HAL_Status_t halADCRead(uint32_t* data) // read data Analog -> DC (4 channels)
{
	if (data == NULL)
	{
		return HAL_ERROR;
	}

	/* Handle overrun */
	if (ADC1->SR & ADC_SR_OVR)
	{
		ADC1->SR &= ~ADC_SR_OVR;
	}

	/* Trigger conversion */
	ADC1->CR2 |= ADC_CR2_SWSTART;

	for (int i = 0; i < 4; i++) // 4 channels
	{
		while (!(ADC1->SR & ADC_SR_EOC)) //wait for conversion to end
		{

		}

		data[i] = ADC1->DR; // if EOC bit is set, store the data
	}

	return HAL_OK;
}
HAL_Status_t halADCTrigger(void)
{
// asynchronously trigger ADC conversion
	/* Handle overrun */
	if (ADC1->SR & ADC_SR_OVR)
	{
		ADC1->SR &= ~ADC_SR_OVR;
	}

	/* Trigger conversion */
	ADC1->CR2 |= ADC_CR2_SWSTART;

	return HAL_OK;
}

HAL_Status_t halADCRegisterCallback(void (*callback)(uint32_t*))
{
// callback for interrupt from ADC
	_adcCallback = callback;
	return HAL_OK;

}
HAL_Status_t halADCSetInterruptPriority(uint32_t priority)
{
	if (priority > 15)
	{
		return HAL_ERROR;
	}
	NVIC_SetPriority(ADC_IRQn, priority);
	return HAL_OK;
}
HAL_Status_t halADCStartInterruptMode(void)
{
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC_IRQn);
	__enable_irq();

	return HAL_OK;
}

void ADC_IRQHandler(void) // name from startup.c
{
	// Because ADC works in scane mode, each scan will call this handler
	// 4 times (4 channels). The static variables are here to store the
	// data between  all calls
	static uint32_t results[4];
	static int channelIndex = 0;

	if (ADC1->SR & ADC_SR_EOC)
	{
		results[channelIndex] = ADC1->DR;
		channelIndex++;

		if (channelIndex >= 4)
		{
			channelIndex = 0;
			if (_adcCallback != NULL) //callback registered
			{
				_adcCallback(results);
			}
		}
	}
}
