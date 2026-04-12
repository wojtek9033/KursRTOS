#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks
#include "event_groups.h"
#include "led.h"
#include "button.h"

/*
 * Upgraded version of freertos6_btn_event. This one uses separate control task to
 * decouple LED Control from Button task. It utilizes event flags.
 */

#define BTN_PRESSED_EVT (1<<0)

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
static volatile EventGroupHandle_t xEventGroup;

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

	while(1)
	{
		btnStatePrev = btnState;
		halButtonGetState(&btnState);

		if ((btnState == 0) && (btnStatePrev == 1))
		{
			xEventGroupSetBits(xEventGroup, BTN_PRESSED_EVT);
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void vControlTask(void* pvParameters)
{
	ledMode = LED_MODE_OFF;
	while(1)
	{
		xEventGroupWaitBits(xEventGroup, BTN_PRESSED_EVT, pdTRUE, pdFALSE, portMAX_DELAY);
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
}

int main(void)
{
	halSerialInit();
	halLEDInit();
	halButtonInit();

	xEventGroup = xEventGroupCreate();

	xTaskCreate(vButtonTask, "ButtonTask", 512, NULL, 1u, NULL);
	xTaskCreate(vLEDTask, "LEDTask", 512, NULL, 1u, NULL);
	xTaskCreate(vControlTask, "ControlTask", 512, NULL, 2u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
