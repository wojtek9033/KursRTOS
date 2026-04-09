#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

void vTask(void* pvParameters)
{
	//uint32_t *pulPtr = (uint32_t*)pvArgs;
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

int main(void)
{
	halSerialInit();

	// "x" stands for BaseType_t
	// configSTACK_DEPTH_TYPE as 512 means, 512 MCU Words - FR411RE is
	// 32 bit (data bus width is 32 bit) so its word is 4 bytes
	// uxPriority should be used for Idle task. Priority grows as the numbers grow,
	// max up to configMAX_PRIORITIES from FreeRTOSConfig.h
	xTaskCreate(vTask, "Task1", 512, &cnt1, 1u, NULL);
	xTaskCreate(vTask, "Task2", 512, &cnt2, 1u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
