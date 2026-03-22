#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"
#include "stm32f4xx.h"

/*
 * In this project, a custom functions were introduced in HAL
 * to allow sending data with serial port, utilizing timeout
 * functionality. In real case scenario, if some failure occurs
 * with sending data, the system could hang. To prevent this,
 * a timeout is introduced.
 */

static volatile uint32_t cnt1;
static volatile uint32_t err_cnt1;

void Task1()
{
	uint32_t freq = osKernelGetTickFreq();
	while(1)
	{
		HAL_Status_t status = halSerialSend_Timeout("Ping\r\n", 50);
		if (status == HAL_OK)
		{
			cnt1++;
		}
		else
		{
			err_cnt1++;
		}

		osDelay(freq);
	}
}

void Task2()
{
	uint32_t freq = osKernelGetTickFreq();
	osDelay(5*freq);

	/*
	 * In here we simulate some error on serial port
	 * so that the serial port will hang, simply by
	 * disabling it after 5 seconds. The goal is to
	 * showcase usage of timeout functionality
	 */

	USART2->CR1 &= ~(USART_CR1_UE);

	while(1)
	{

	}
}

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	osThreadNew(Task1, NULL, NULL);
	osThreadNew(Task2, NULL, NULL);

	osKernelStart();

	while(1)
	{
	}
}
