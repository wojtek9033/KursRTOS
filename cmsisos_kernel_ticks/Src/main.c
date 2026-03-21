#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

void Task1()
{
	/* AVOID
	 * In this approach, we do not "release control" - we are NOT blocking this task
	 * from execution, so we just "waste" time in the loop.
	 */
	uint32_t freq = osKernelGetTickFreq();
	while(1)
	{
		cnt1++;
		uint32_t ticks_start = osKernelGetTickCount();

		// "+ freq [Hz]" is the configured SysTick frequency.
		// This results in waiting full second
		while(osKernelGetTickCount() < ticks_start + freq)
		{

		}
	}
}

void Task2()
{
	/* USE THIS APPROACH
	 * In this approach, we BLOCK the task, meaning the OS gives control to other
	 * tasks that can "do work while we wait here"
	 */
	uint32_t freq = osKernelGetTickFreq();
	while(1)
	{
		cnt2++;
		osDelay(freq);
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
