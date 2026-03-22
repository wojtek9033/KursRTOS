#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

/*
 *  This project showcases usage of the events. When Master task
 *  sets an event flag, the other one starts his work.
 */


static volatile osEventFlagsId_t event_id;
static volatile uint32_t cnt_master;
static volatile uint32_t cnt_slave;

void Master(void* arg)
{
	while(1)
	{
		osDelay(1000);
		cnt_master++;
		osEventFlagsSet(event_id, 0x1);
	}
}

void Slave(void* arg)
{
	while(1)
	{
		osEventFlagsWait(event_id, 0x1, osFlagsWaitAny, osWaitForever);
		cnt_slave++;
	}
}

int main(void)
{

	halSerialInit();
	osKernelInitialize();

	event_id = osEventFlagsNew(NULL);

	osThreadNew(Master, NULL, NULL);
	osThreadNew(Slave, NULL, NULL);

	osKernelStart();

	while(1)
	{
	}
}
