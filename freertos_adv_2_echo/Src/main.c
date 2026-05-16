#include <stdint.h>
#include <stdio.h>

#include "serial.h"
#include "timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

static volatile QueueHandle_t xQueue;

void vEchoTask(void* pvArguments)
{
	char c;
	while (1)
	{
		xQueueReceive(xQueue, &c, portMAX_DELAY);
		halSerialPut(c);
	}
}

void rxCallback(char c)
{
	BaseType_t xHigherTaskWoken = pdFALSE;
	xQueueSendFromISR(xQueue, &c, &xHigherTaskWoken);
	portYIELD_FROM_ISR(xHigherTaskWoken); // give control to higher priority task
}

int main(void)
{
	halSerialInit();

	halSerialRegisterCallback(rxCallback);

	xQueue = xQueueCreate(10, sizeof(char));
	xTaskCreate(vEchoTask, "EchoTask", 128, NULL, 1, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
