#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

void vTask(void* pvParameters)
{
	UBaseType_t* puxPtr = (UBaseType_t*)pvParameters; // BaseType_t gives software independence of different MCUs
	while(1)
	{
		(*puxPtr)++;
	}
}

void Task2(void* args)
{
	while(1)
	{
		cnt2++;
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
	HeapStats_t xHeapStats;
	halSerialInit();

	vPortGetHeapStats(&xHeapStats);
	if (xTaskCreate(vTask, "Task1", 2048, &cnt1, 1u, NULL) != pdPASS)
	{
		// This will execute only if system failed to allocate enough memory (2048 * 4 bytes = 8kB)
		printf("Error while creating Task1\r\n");
		Loop();
	}
	vPortGetHeapStats(&xHeapStats);

	if (xTaskCreate(vTask, "Task2", 2048, &cnt2, 1u, NULL) != pdPASS)
	{
		// This will execute only if system failed to allocate enough memory (2048 * 4 bytes = 8kB)
		printf("Error while creating Task2\r\n");
		Loop();
	}
	vPortGetHeapStats(&xHeapStats);

	printf("System ready \r\n");

	vTaskStartScheduler();

	Loop();
}
