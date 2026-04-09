#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks

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

void vTask(void* pvParameters)
{
	UBaseType_t* puxPtr = (UBaseType_t*)pvParameters; // BaseType_t gives software independence of different MCUs
	while(1)
	{
		(*puxPtr)++;
		//vDelay1(10); Task Blocking
		vDelay2(10); // Busy wait - polling
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

	xTaskCreate(vTask, "Task1", 512, &cnt1, 1u, NULL);
	xTaskCreate(vTask, "Task2", 512, &cnt2, 1u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	Loop();
}
