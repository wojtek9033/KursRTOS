#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

void Task1(void* args)
{
	while(1)
	{
		cnt1++;
	}
}

void Task2(void* args)
{
	while(1)
	{
		cnt2++;
	}
}

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	osThreadNew(Task1, NULL, NULL);
	osThreadNew(Task2, NULL, NULL);

	printf("System ready \r\n");

	osKernelStart();

	while(1)
	{
	}
}
