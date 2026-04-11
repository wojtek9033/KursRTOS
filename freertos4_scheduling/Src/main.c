#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks

/*
 * 1) Time Slicing - is a scheduling technique that divides CPU time into small,
 * equal intervals to share processor resources among multiple tasks of THE SAME
 * PRIORITY
 *
 * 2) Context switch can happen only between tasks of the same priority.
 * This means, if a higher priority task is not blocked, the lower priority
 * task will get starved (as long as the higher priority task is not finished).
 * If the higher priority task is blocked (ex. using vTaskDelay), then, lower
 * priority task will also get CPU time.
 *
 * 3) Preemption is the ability of the SCHEDULER to interrupt a currently
 * running task to allow a higher-priority task to execute immediately
 */

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

void vDelay1(UBaseType_t xDelayMs)
{
	vTaskDelay(pdMS_TO_TICKS(xDelayMs));
}


void vDelay2(UBaseType_t xDelayMs)
{
	BaseType_t xTicksStart = xTaskGetTickCount();
	BaseType_t xTicksStop = xTicksStart + pdMS_TO_TICKS(xDelayMs);

	while (xTaskGetTickCount() < xTicksStop)
	{

	}
}

void vTask1(void* pvParameters)
{	while(1)
	{
		cnt1++;
		vDelay1(10);
	}
}

void vTask2(void* pvParameters)
{	while(1)
	{
		cnt2++;
		vDelay2(10);
	}
}

void Loop()
{
	while(1)
	{
	}
}

int main(void)
{
	xTraceEnable(TRC_START);

	halSerialInit();

	xTaskCreate(vTask1, "Task1", 512, NULL, 2u, NULL);
	xTaskCreate(vTask2, "Task2", 512, NULL, 1u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	Loop();
}
