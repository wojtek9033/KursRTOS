/*
 * app_logic.c
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */
#include <stddef.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "FreeRTOS_CLI.h"

#include "app_control.h"
#include "app_logic.h"

typedef enum
{
	APP_EVENT_STEP_TEST_START,
	APP_EVENT_STEP_TEST_BACKWARD,
	APP_EVENT_STEP_TEST_DONE
} AppEvent_t;

typedef struct
{
	AppEvent_t event;
	void* payload;
} AppMessage_t;

static void (*_appStateHandler)(AppMessage_t) = NULL;
static void _appStateIdle(AppMessage_t msg);
static void _appStateStepTestForward(AppMessage_t msg);
static void _appStateStepTestBackward(AppMessage_t msg);

volatile static QueueHandle_t _xMessageQueue;

volatile static TimerHandle_t _xStepTestForwardTimer;
volatile static TimerHandle_t _xStepTestBackwardTimer;

void _stepTestFwdTimerHandler(TimerHandle_t xTimer)
{
	AppMessage_t msg=
	{
			.event = APP_EVENT_STEP_TEST_BACKWARD,
			.payload = NULL
	};
	xQueueSend(_xMessageQueue, &msg, pdMS_TO_TICKS(50));
}
void _stepTestBackTimerHandler(TimerHandle_t xTimer)
{
	AppMessage_t msg=
	{
			.event = APP_EVENT_STEP_TEST_DONE,
			.payload = NULL
	};
	xQueueSend(_xMessageQueue, &msg, pdMS_TO_TICKS(50));

}

BaseType_t _cliStepTestStart(char* pcWriteBuffer, size_t xWriteBufferLen, const char* commandString)
{
	AppMessage_t msg=
	{
			.event = APP_EVENT_STEP_TEST_START,
			.payload = NULL
	};
	xQueueSend(_xMessageQueue, &msg, pdMS_TO_TICKS(50));

	return pdFALSE;
}

CLI_Command_Definition_t cmdDef_cliStepTestStart =
{
		.pcCommand = "stepTest",
		.pcHelpString = "stepTest:\r\nTest step response\r\n\r\n",
		.pxCommandInterpreter = _cliStepTestStart,
		.cExpectedNumberOfParameters = 0
};

void vAppLogicTask(void* pvParameters)
{
	AppMessage_t msg;
	while(1)
	{
		xQueueReceive(_xMessageQueue, &msg, portMAX_DELAY);
		if (_appStateHandler != NULL)
		{
			_appStateHandler(msg);
		}
	}
}

void appLogicInit()
{
	FreeRTOS_CLIRegisterCommand(&cmdDef_cliStepTestStart);
	_appStateHandler = _appStateIdle;
	_xMessageQueue = xQueueCreate(1, sizeof(AppMessage_t));
	xTaskCreate(vAppLogicTask, "AppLogicTask", 128, NULL, 5, NULL);

	_xStepTestForwardTimer = xTimerCreate("StepTestFwdTimer", pdMS_TO_TICKS(700), pdFALSE, NULL, _stepTestFwdTimerHandler);
	_xStepTestBackwardTimer = xTimerCreate("StepTestBackTimer", pdMS_TO_TICKS(700), pdFALSE, NULL, _stepTestBackTimerHandler);
}
void appLogicStart()
{
	vTaskStartScheduler();
}

static void _appStateIdle(AppMessage_t msg)
{
	if (msg.event == APP_EVENT_STEP_TEST_START)
	{
		appControlJoystickDisable();
		appControlBufferEnable();
		appControlSetRegulatorDirect();
		appControlSetRegulatorTarget(1.0);
		xTimerStart(_xStepTestForwardTimer, 0);
		_appStateHandler = _appStateStepTestForward;
	}
}

static void _appStateStepTestForward(AppMessage_t msg)
{
	if (msg.event == APP_EVENT_STEP_TEST_BACKWARD)
	{
		appControlSetRegulatorTarget(-1.0);
		xTimerStart(_xStepTestBackwardTimer, 0);
		_appStateHandler = _appStateStepTestBackward;
	}
}
static void _appStateStepTestBackward(AppMessage_t msg)
{
	if (msg.event == APP_EVENT_STEP_TEST_DONE)
	{
		appControlBufferDisable();
		appControlSetRegulatorTarget(0);
		appControlJoystickEnable();
		_appStateHandler = _appStateIdle;
	}
}
