#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks
#include "led.h"

void vButtonTask(void* pvParameters)
{
	uint32_t btnState = 0;
	while(1)
	{
		halButtonGetState(&btnState);
		if (btnState)
		{
			halLEDOn();
		}
		else
		{
			halLEDOff();
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

int main(void)
{
	halSerialInit();
	halLEDInit();
	halButtonInit();

	xTaskCreate(vButtonTask, "ButtonTask", 512, NULL, 2u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
