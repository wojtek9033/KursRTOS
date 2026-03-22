#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

void Task1()
{
	uint32_t freq = osKernelGetTickFreq();
	while(1)
	{
		printf("Ping\r\n");
		osDelay(500);
	}
}

/*
 * Note that it is important to not set too low stack size.
 * This will result in the system malfunction.
 * In this exercise the minimum stack size was calculated to 144 bytes, by
 * putting a breakpoint on the printf (main.c) and afterwards in the  __io_putchar (hal/Src/serial.c)
 * before the halSerialPut function
 */

osThreadAttr_t task1_attr={
		//.stack_size = 64
		.stack_size = 256
};

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	osThreadNew(Task1, NULL, &task1_attr);

	osKernelStart();

	while(1)
	{
	}
}
