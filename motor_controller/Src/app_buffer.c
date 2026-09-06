/*
 * app_buffer.c
 *
 *  Created on: May 24, 2026
 *      Author: wojci
 */
#include <stdio.h>

#include "app_buffer.h"
#include "console.h"

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "task.h"
#include "semphr.h"

static volatile SemaphoreHandle_t _bufferMutex;

BaseType_t _cliPrintBuffer(char* pcWriteBuffer, size_t xWriteBufferLen, const char* commandString)
{
	appBufferPrint();
	return pdFALSE;
}

CLI_Command_Definition_t cmdDef_cliPrintBuffer =
{
		.pcCommand = "printBuffer",
		.pcHelpString = "printBuffer:\r\nPrints buffer\r\n\r\n",
		.pxCommandInterpreter = _cliPrintBuffer,
		.cExpectedNumberOfParameters = 0
};

void appBufferInit()
{
	bufferInit();
	_bufferMutex = xSemaphoreCreateMutex();
	FreeRTOS_CLIRegisterCommand(&cmdDef_cliPrintBuffer);
}
void appBufferClear()
{
	xSemaphoreTake(_bufferMutex, portMAX_DELAY);
	bufferClear();
	xSemaphoreGive(_bufferMutex);
}
void appBufferPrint()
{
	BufferElement_t data;
	bufferIteratorRestart();
	char txtBuffer[64];

	xSemaphoreTake(_bufferMutex, portMAX_DELAY);
	srvConsolePrint("Buffer:\r\n", -1);

	while(bufferIteratorNext(&data) == 0)
	{
		snprintf(txtBuffer, 64, "%ld %ld %ld\n\r", data.encoder_data, data.angle, data.speed);
		while (srvConsolePrint(txtBuffer, 10) == SRV_TIMEOUT)
		{
			vTaskDelay(1);
		}
	}
	xSemaphoreGive(_bufferMutex);
}

void appBufferPut(BufferElement_t data)
{
	xSemaphoreTake(_bufferMutex, portMAX_DELAY);
	bufferPut(data);
	xSemaphoreGive(_bufferMutex);
}


