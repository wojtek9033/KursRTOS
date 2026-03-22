#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

/* EXAMPLE OF PREEMPTION & THREAD STARVING */

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
			// NOT releasing control
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
		osDelay(freq); // releasing control
	}
}

/*
 * Preemption (wywłaszczanie) works only for the tasks of the same priority!!!
 */

osThreadAttr_t task1_attr = {
		//.priority = osPriorityNormal both cnt1 and cnt2 get incremented (Task1 has  lower priority)
		.priority = osPriorityHigh // only cnt1 gets incremented - example of TASK(Task2) STARVING
};

osThreadAttr_t task2_attr = {
		//.priority = osPriorityHigh both cnt1 and cnt2 get incremented (Task2 has  higher priority)
		.priority = osPriorityNormal // only cnt1 gets incremented  - example of THREAD (Task2) STARVING
};

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	osThreadNew(Task1, NULL, &task1_attr);
	osThreadNew(Task2, NULL, &task2_attr);

	osKernelStart();

	while(1)
	{
	}
}
