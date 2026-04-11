#include "led.h"
#include "stm32f4xx.h"
#include "cmsis_helpers.h"

HAL_Status_t halLEDInit(void)
{
	/*Turn-on GPIO clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/*Set PA5 as output*/
	FILL_REG(GPIOA->MODER, GPIO_MODER_MODER5, GPIO_MODER_OUTPUT);

	/*Configure PA5 output as push-pull*/
	FILL_REG(GPIOA->OTYPER, GPIO_OTYPER_OT5, GPIO_OTYPER_PUSH_PULL);

	/*Turn off LED*/
	FILL_REG(GPIOA->ODR, GPIO_ODR_OD5, 0);

	return HAL_OK;
}

HAL_Status_t halLEDOn(void)
{
	FILL_REG(GPIOA->ODR, GPIO_ODR_OD5, 1);

	return HAL_OK;
}

HAL_Status_t halLEDOff(void)
{
	FILL_REG(GPIOA->ODR, GPIO_ODR_OD5, 0);

	return HAL_OK;
}
