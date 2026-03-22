#include "serial.h"
#include "timebase.h"
#include "stm32f4xx.h"
#include "cmsis_helpers.h"

HAL_Status_t halSerialInit(void)
{
	/*Turn-on GPIO clock*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/*Configure GPIO pins for UART function*/

	/*Set PA2 and PA3 as alternate function*/
	FILL_REG(GPIOA->MODER, GPIO_MODER_MODER2, GPIO_MODER_AF);
	FILL_REG(GPIOA->MODER, GPIO_MODER_MODER3, GPIO_MODER_AF);

	/*Set alternate function type to AF7 for PA2 (USART2_TX) and PA3 (USART2_RX)*/
	FILL_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL2, 7);
	FILL_REG(GPIOA->AFR[0], GPIO_AFRL_AFSEL3, 7);

	/*Turn-on clock for UART module*/
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/*Configure UART module*/
	/*Configure UART baud rate*/
	uint32_t uart_div = (CONFIG_APB1_CLOCK + CONFIG_SERIAL_CLOCK/2)/CONFIG_SERIAL_CLOCK;
	USART2->BRR = uart_div;

	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);

	/*Turn-on UART module*/
	USART2->CR1 |= USART_CR1_UE;

	return HAL_OK;
}

HAL_Status_t halSerialPut(const char data)
{
	while(!(USART2->SR & USART_SR_TXE))
	{
	}
	USART2->DR = (data & 0xFF);

	return HAL_OK;
}

HAL_Status_t halSerialPut_Timeout(const char data, uint32_t timeout)
{
	uint32_t ticks_start = halGetTicks();
	while(!(USART2->SR & USART_SR_TXE))
	{
		/*
		 * While Serial Port is busy, count system ticks to check for timeout
		 */
		if (halGetTicks() > ticks_start + timeout)
		{
			return HAL_TIMEOUT;
		}
	}
	USART2->DR = (data & 0xFF);

	return HAL_OK;
}

HAL_Status_t halSerialSend(const char* txt)
{
	while (*txt != 0)
	{
		HAL_Status_t status = halSerialPut(*txt);
		if (status == HAL_TIMEOUT)
		{
			return HAL_TIMEOUT;
		}
		txt++;
	}
	return HAL_OK;
}

HAL_Status_t halSerialSend_Timeout(const char* txt, uint32_t timeout)
{
	while (*txt != 0)
	{
		HAL_Status_t status = halSerialPut_Timeout(*txt, timeout);
		if (status == HAL_TIMEOUT)
		{
			return HAL_TIMEOUT;
		}
		txt++;
	}
	return HAL_OK;
}

int __io_putchar(int ch)
{
	halSerialPut(ch);
	return ch;
}
