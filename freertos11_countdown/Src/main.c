#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "serial.h"

#include "FreeRTOS.h"   // base
#include "task.h"		// create & manage tasks
#include "queue.h"
#include "timers.h"
#include "message_buffer.h" //can handle data of different size - usage with text
#include "led.h"
#include "button.h"

#define MSG_BUFFER_LEN 256
#define MSG_LEN 64
#define MSG_CNT 4
typedef enum {
	MSG_BTN_PRESSED = 0,
	MSG_TIMEOUT = 1
} ControlMessage_t;

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
static volatile QueueHandle_t xQueue;
static volatile TimerHandle_t xTimer;
//static volatile MessageBufferHandle_t xMessageBuffer;
static volatile QueueHandle_t xConsoleQueue;

void sendConsoleMessage(char *msg)
{
//	size_t len = strlen(msg) + 1;
//	xMessageBufferSend(xMessageBuffer, msg, len, 0);
	xQueueSend(xConsoleQueue, msg, 0);
}

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
			ControlMessage_t msg = MSG_BTN_PRESSED;
			// msg will be copied anyway, so its local visibility is not a problem here
			// timeout 0 so if queue is full, program continues
			xQueueSend(xQueue, &msg, 0);
		}

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void vControlTask(void* pvParameters)
{
	appState = APP_IDLE;
	ledMode = LED_MODE_OFF;

	ControlMessage_t msg;

	while(1)
	{

		xQueueReceive(xQueue, &msg, portMAX_DELAY);

		switch(appState)
		{
		case APP_IDLE:
			if (msg == MSG_BTN_PRESSED)
			{
				appState = APP_RUNNING;
				ledMode = LED_MODE_ON;

				vTimerSetTimerID(xTimer, (void*) 0);
				if (xTimerStart(xTimer, pdMS_TO_TICKS(100)) == pdFAIL)
				{
					appState = APP_ERROR;
					ledMode = LED_MODE_BLINK;
					sendConsoleMessage("Error!\r\n");
				}
				else
				{
					sendConsoleMessage("Process is running.\r\n");
				}
			}
			break;

		case APP_RUNNING:
			if (msg == MSG_TIMEOUT)
			{
				appState = APP_IDLE;
				ledMode = LED_MODE_OFF;
				sendConsoleMessage("Process is finished.\r\n");
			}
			else if (msg == MSG_BTN_PRESSED)
			{
				appState = APP_ERROR;
				ledMode = LED_MODE_BLINK;
				xTimerStop(xTimer, 0);
				sendConsoleMessage("Process stopped.\r\n");
			}
			break;

		case APP_ERROR:
			if (msg == MSG_BTN_PRESSED)
			{
				appState = APP_IDLE;
				ledMode = LED_MODE_OFF;
				sendConsoleMessage("Error cleared \r\n");
			}
			break;
		}
	}
}

// Timers do have a special task, only for timers. All timers share the same task.
void vTimerCallback(TimerHandle_t xTimer)
{
	uint32_t cnt = (uint32_t) pvTimerGetTimerID(xTimer);
	cnt++;
	if (cnt >= 10)
	{
		ControlMessage_t msg = MSG_TIMEOUT;
		// msg will be copied anyway, so its local visibility is not a problem here
		// timeout 0 so if queue is full, program continues
		xQueueSend(xQueue, &msg, 0);
		cnt = 0;
		xTimerStop(xTimer, 0);
	}
	else
	{
		char msg[MSG_LEN];
		snprintf(msg, MSG_LEN, "Counter: %ul\r\n", cnt);
		sendConsoleMessage(msg);
	}

	vTimerSetTimerID(xTimer, (void*) cnt);
}

void vConsoleTask(void* pvParameters)
{
	char msg[MSG_LEN];

	while(1)
	{
		//xMessageBufferReceive(xMessageBuffer, msg, MSG_LEN, portMAX_DELAY);
		xQueueReceive(xConsoleQueue, msg, portMAX_DELAY);
		printf("%s", msg);
	}
}

int main(void)
{
	halSerialInit();
	halLEDInit();
	halButtonInit();

	xQueue = xQueueCreate(1, sizeof(ControlMessage_t));
	xTimer = xTimerCreate("Running Timer", pdMS_TO_TICKS(200), pdTRUE, (void*) 0, vTimerCallback);
	//xMessageBuffer = xMessageBufferCreate(MSG_BUFFER_LEN * sizeof(char));
	xConsoleQueue = xQueueCreate(MSG_CNT, MSG_LEN*sizeof(char));

	xTaskCreate(vButtonTask, "ButtonTask", 512, NULL, 1u, NULL);
	xTaskCreate(vLEDTask, "LEDTask", 512, NULL, 1u, NULL);
	xTaskCreate(vConsoleTask, "ConsoleTask", 512, NULL, 1u, NULL);
	xTaskCreate(vControlTask, "ControlTask", 512, NULL, 3u, NULL);

	printf("System ready \r\n");

	vTaskStartScheduler();

	while(1)
	{
	}
}
