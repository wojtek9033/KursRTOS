#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"
#include "task.h"
#include "timers.h"

#include "console.h"

/*
void vTimer1Callback(TimerHandle_t xTimer)
{
	srvConsolePrint("Line1\r\n", 0);
}

void vTimer2Callback(TimerHandle_t xTimer)
{
	srvConsolePrint("Line2\r\n", 0);
}
*/

BaseType_t cmdPing(char* prcWriteBuffer, size_t WriteBufferLen, const char *pcComandString)
{
	sniprintf(prcWriteBuffer, WriteBufferLen, "pong\r\n");
	return pdFALSE;
}

BaseType_t cmdAdd(char* prcWriteBuffer, size_t WriteBufferLen, const char *pcComandString)
{
	char *pcParameter1, *pcParameter2;
	BaseType_t xParameter1Len, xParameter2Len;

	pcParameter1 = FreeRTOS_CLIGetParameter(pcComandString, 1, &xParameter1Len);
	pcParameter2 = FreeRTOS_CLIGetParameter(pcComandString, 2, &xParameter2Len);

	uint32_t x1 = atoi(pcParameter1);
	uint32_t x2 = atoi(pcParameter2);

	snprintf(prcWriteBuffer, WriteBufferLen, "%lu\r\n", x1 + x2);

	return pdFALSE;
}

const CLI_Command_Definition_t xCommandList[] =
{
		{
				.pcCommand = "ping",
				.pcHelpString = "ping:\r\n Print pong in command line\r\n\r\n",
				.pxCommandInterpreter = cmdPing,
				.cExpectedNumberOfParameters = 0
		},
		{
				.pcCommand = "add",
				.pcHelpString = "add:\r\n Add two numbers\r\n\r\n",
				.pxCommandInterpreter = cmdAdd,
				.cExpectedNumberOfParameters = 2
		},
		{
				.pcCommand = NULL
		}
};

void registerCLICommands(const CLI_Command_Definition_t xCommandList[])
{
	for (int i = 0; xCommandList[i].pcCommand != NULL; i++)
	{
		FreeRTOS_CLIRegisterCommand(&xCommandList[i]);
	}
}

int main(void)
{
	srvConsoleInit();
	registerCLICommands(xCommandList);
	/*
	TimerHandle_t xTimer1 = xTimerCreate("Timer1", pdMS_TO_TICKS(500), pdTRUE, NULL, vTimer1Callback);
	TimerHandle_t xTimer2 = xTimerCreate("Timer1", pdMS_TO_TICKS(1000), pdTRUE, NULL, vTimer2Callback);

	xTimerStart(xTimer1, 0);
	xTimerStart(xTimer2, 0);
	*/

	vTaskStartScheduler();

	while(1)
	{
	}
}
