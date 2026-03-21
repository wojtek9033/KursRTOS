#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

void info (void)
{
	char infobuf[100];
	osVersion_t osv;
	osStatus_t status;

	status = osKernelGetInfo(&osv, infobuf, sizeof(infobuf));
	if (status == osOK) {
		printf("Kernel Information: %s\r\n", infobuf);
		printf("Kernel Version: 	%lu\r\n", osv.kernel);
		printf("Kernel API Version: %lu\r\n", osv.api);
	}
}

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	osKernelStart();

	while(1)
	{
	}
}
