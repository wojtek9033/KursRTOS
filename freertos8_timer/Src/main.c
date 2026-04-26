#include <stdint.h>
#include <stdio.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks
#include "event_groups.h"
#include "timers.h"
#include "led.h"
#include "button.h"

#define EVT_BTN_PRESSED (1<<0)
#define EVT_TIMEOUT (1<<1)

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

typedef enum
{
	APP_IDLE = 0,
	APP_RUNNING = 10,
	APP_ERROR = 20
} AppState_t;

static volatile LEDMode_t ledMode;
static volatile AppState_t appState;
static volatile EventGroupHandle_t xEventGroup;
static volatile TimerHandle_t xTimer;

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
			xEventGroupSetBits(xEventGroup, EVT_BTN_PRESSED);
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void vControlTask(void* pvParameters)
{
	appState = APP_IDLE;
	ledMode = LED_MODE_OFF;

	while(1)
	{
		//eventBits is to store return mask - indicates what event happened - TN_PRESSED_EVT or TIMEOUT_EVT
		EventBits_t eventBits = xEventGroupWaitBits(xEventGroup, EVT_BTN_PRESSED | EVT_TIMEOUT, pdTRUE, pdFALSE, portMAX_DELAY);

		switch(appState)
		{
		case APP_IDLE:
			if (eventBits & EVT_BTN_PRESSED)
			{
				appState = APP_RUNNING;
				ledMode = LED_MODE_ON;

				if (xTimerStart(xTimer, pdMS_TO_TICKS(100)) == pdFAIL)
				{
					appState = APP_ERROR;
					ledMode = LED_MODE_BLINK;
				}
			}
			break;

		case APP_RUNNING:
			if (eventBits & EVT_TIMEOUT)
			{
				appState = APP_IDLE;
				ledMode = LED_MODE_OFF;
			}
			else if (eventBits & EVT_BTN_PRESSED)
			{
				appState = APP_ERROR;
				ledMode = LED_MODE_BLINK;
			}
			break;

		case APP_ERROR:
			if (eventBits & EVT_BTN_PRESSED)
			{
				appState = APP_IDLE;
				ledMode = LED_MODE_OFF;
			}
			break;
		}
	}
}

// Timers do have a special task, only for timers. All timers share the same task.
void vTimerCallback(TimerHandle_t xTimer)
{
	xEventGroupSetBits(xEventGroup, EVT_TIMEOUT);
}

int main(void)
{
	halSerialInit();
	halLEDInit();
	halButtonInit();

	xEventGroup = xEventGroupCreate();
	xTimer = xTimerCreate("Running Timer", pdMS_TO_TICKS(2000), pdFALSE, NULL, vTimerCallback);

	xTaskCreate(vButtonTask, "ButtonTask", 512, NULL, 1u, NULL);
	xTaskCreate(vLEDTask, "LEDTask", 512, NULL, 1u, NULL);
	xTaskCreate(vControlTask, "ControlTask", 512, NULL, 2u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
