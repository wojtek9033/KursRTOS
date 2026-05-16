#include "console.h"
#include "serial.h"
#include "services_common.h"

#include <string.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "message_buffer.h"
#include "queue.h"
#include "semphr.h"

#define CONSOLE_BUFFER_SIZE 256
#define CHARACTER_QUEUE_LEN 128
#define LINE_BUFFER_SIZE 128

static MessageBufferHandle_t _xConsoleMessageBuffer;
static SemaphoreHandle_t _xConsoleMutex;
static QueueHandle_t _xCharacterQueue;

static char _lineBuffer[LINE_BUFFER_SIZE];
static uint32_t _line_ptr = 0;

static char _outputBuffer[configCOMMAND_INT_MAX_OUTPUT_SIZE];

void _vTxTask(void *pvParameters)
{
	char buffer[CONSOLE_BUFFER_SIZE];
	while(1)
	{
		xMessageBufferReceive(_xConsoleMessageBuffer, buffer, CONSOLE_BUFFER_SIZE, portMAX_DELAY);
		printf("%s", buffer);
	}
}

void _cliProcessCharacter(char c)
{
	if (c == '\b') //backspace
	{
		if (_line_ptr > 0)
		{
		_line_ptr--;
		}
	}
	else
	{
		if (_line_ptr < LINE_BUFFER_SIZE - 1)
		{
			_lineBuffer[_line_ptr] = c;
			_line_ptr++;
		}
	}

}

void _cliProcessLine()
{
	_lineBuffer[_line_ptr] = 0; // last character must be 0
	_line_ptr = 0;

	//srvConsolePrint(_lineBuffer, 0);

	BaseType_t xMoreDataToFollow;
	do
	{
		xMoreDataToFollow = FreeRTOS_CLIProcessCommand(_lineBuffer, _outputBuffer, configCOMMAND_INT_MAX_OUTPUT_SIZE);
		srvConsolePrint(_outputBuffer, 0);
	}
	while (xMoreDataToFollow != pdFALSE);
}


void _vRxTask(void* pvParameters)
{
	char c;
	while(1)
	{
		xQueueReceive(_xCharacterQueue, &c, portMAX_DELAY);

		if (c == '\n')
		{
			_cliProcessLine();
		}
		else
		{
			_cliProcessCharacter(c);
		}
	}
}

void _rxCallback(char c)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xQueueSendFromISR(_xCharacterQueue, &c, &xHigherPriorityTaskWoken);

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

ServiceStatus_t srvConsoleInit()
{
	_xConsoleMutex = xSemaphoreCreateMutex();
	_xConsoleMessageBuffer = xMessageBufferCreate(CONSOLE_BUFFER_SIZE * sizeof(char));
	_xCharacterQueue = xQueueCreate(CHARACTER_QUEUE_LEN, sizeof(char));

	halSerialInit();
	halSerialRegisterCallback(_rxCallback);

	xTaskCreate(_vTxTask, "TxTask", 512, NULL, 1, NULL);
	xTaskCreate(_vRxTask, "RxTask", 512, NULL, 1, NULL);

	return SRV_OK;
}

ServiceStatus_t srvConsolePrint(const char* line, int32_t timeout_ms)
{
	TickType_t xTicksToWait;
	if (timeout_ms >= 0)
	{
		xTicksToWait = pdMS_TO_TICKS(timeout_ms);
	}
	else
	{
		xTicksToWait = portMAX_DELAY;
	}

	if (xSemaphoreTake(_xConsoleMutex, xTicksToWait) != pdPASS)
	{
		return SRV_TIMEOUT;
	}
	else
	{
		size_t bytesToSend = strlen(line) + 1;
		size_t bytesSent;
		bytesSent = xMessageBufferSend(_xConsoleMessageBuffer, line, bytesToSend, xTicksToWait);
		xSemaphoreGive(_xConsoleMutex);

		if (bytesSent == bytesToSend)
		{
			return SRV_OK;
		}
		else
		{
			return SRV_ERROR;
		}
	}
}

