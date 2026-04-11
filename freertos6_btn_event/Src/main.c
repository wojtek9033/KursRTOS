#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks
#include "led.h"
#include "button.h"

typedef enum
{
	LED_MODE_OFF = 0,
	LED_MODE_ON = 1,
	LED_MODE_BLINK = 2
} LEDMode_t;

typedef enum
{
	LED_STATE_OFF = 0,
	LED_STATE_ON = 1
} LEDState_t;

static volatile LEDMode_t ledMode;

void vLEDTask(void* pvParameters)
{
	LEDState_t ledState = LED_STATE_OFF;
	halLEDOff();

	while(1)
	{
		switch (ledMode)
		{
		case (LED_MODE_OFF):
				halLEDOff();
				ledState = LED_STATE_OFF;
				break;
		case (LED_MODE_ON):
				halLEDOn();
				ledState = LED_STATE_ON;
				break;
		case (LED_MODE_BLINK):
				if (ledState == LED_STATE_OFF)
				{
					halLEDOn();
					ledState = LED_STATE_ON;
				}
				else
				{
					halLEDOff();
					ledState = LED_STATE_OFF;
				}
		}

		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

void vButtonTask(void* pvParameters)
{
	uint32_t btnState;
	uint32_t btnStatePrev;

	halButtonGetState(&btnState);
	ledMode = LED_MODE_OFF;

	while(1)
	{
		btnStatePrev = btnState;
		halButtonGetState(&btnState);

		if ((btnState == 0) && (btnStatePrev == 1))
		{
			switch(ledMode)
			{
			case LED_MODE_OFF:
				ledMode = LED_MODE_ON;
				break;
			case LED_MODE_ON:
				ledMode = LED_MODE_BLINK;
				break;
			case LED_MODE_BLINK:
				ledMode = LED_MODE_OFF;
				break;
			}
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

int main(void)
{
	halSerialInit();
	halLEDInit();
	halButtonInit();

	xTaskCreate(vButtonTask, "ButtonTask", 512, NULL, 1u, NULL);
	xTaskCreate(vLEDTask, "LedTask", 512, NULL, 1u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
