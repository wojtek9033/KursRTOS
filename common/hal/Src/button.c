#include "button.h"
#include "stm32f4xx.h"
#include "cmsis_helpers.h"

HAL_Status_t halButtonInit(void)
{
	/*Turn-on GPIO clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	/*Set PC13 as input*/
	FILL_REG(GPIOA->MODER, GPIO_MODER_MODER13, GPIO_MODER_INPUT);

	return HAL_OK;
}
HAL_Status_t halButtonGetState(uint32_t* state)
{
	uint32_t data;

	data = GPIOC->IDR & GPIO_IDR_ID13;

	if (data)
	{
		*state = 0;
	}
	else
	{
		*state = 1;
	}

	return HAL_OK;
}
