#include <stdint.h>
#include <stdio.h>

#include "serial.h"
#include "timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;
static volatile uint32_t err_cnt1;
static volatile uint32_t err_cnt2;

static volatile QueueHandle_t xQueue;

void vConsumerTask(void* pvParameters)
{
	uint32_t buffer;
	while(1)
	{
		xQueueReceive(xQueue, &buffer, portMAX_DELAY);
	}
}

void vProducerTask1(void *pvParameters)
{
	while(1)
	{
		cnt1++;
		if (xQueueSend(xQueue, &cnt1, 0) != pdPASS)
		{
			err_cnt1++;
		}
	}
}

void vProducerTask2(void *pvParameters)
{
	while(1)
	{
		cnt2++;
		if (xQueueSend(xQueue, &cnt2, 0) != pdPASS)
		{
			err_cnt2++;
		}
	}
}

void vTimerCallback(void)
{
	BaseType_t xHigherTaskWoken = pdFALSE; // to notify task with higher priority than the one "being interrupted"
	cnt2++;
	// xQueueSendFromISR does not check if there is higher priority task waiting!
	// functions ending with "FromISR" are special functions to be used only and
	// always* in Interrupt callback's. They do not yield
	// 1) Do not call scheduler automatically
	// 2) They do not block, no timeout
	// 3) If want to call scheduler, need to do it manually
	if(xQueueSendFromISR(xQueue, &cnt2, &xHigherTaskWoken) != pdPASS)
	{
		err_cnt2++;
	}

	portYIELD_FROM_ISR(xHigherTaskWoken);
}

int main(void)
{
	halSerialInit();
	halTimerInit();
	halTimerRegisterCallback(vTimerCallback);
	xQueue = xQueueCreate(1, sizeof(uint32_t));

	xTaskCreate(vConsumerTask, "ConsumerTask", 512, NULL, 2, NULL);
	xTaskCreate(vProducerTask1, "ProducerTask1", 512, NULL, 1, NULL);
	//xTaskCreate(vProducerTask2, "ProducerTask2", 512, NULL, 1, NULL);

	printf("System ready \r\n");

	halTimerStart();
	vTaskStartScheduler();

	while(1)
	{
	}
}
