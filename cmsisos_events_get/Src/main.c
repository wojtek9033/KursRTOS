#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

#define MASTER_FLAG (1 << 0)

/*
 * This project is to showcase polling CPU for event, instead of blocking task.
 * Slave has higher priority than master, so if it does not block (do not have osEventFlagsWait
 * or does not do osDelay(), will fall in endless loop polling CPU
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
		osEventFlagsSet(event_id, MASTER_FLAG);
	}
}


void Slave(void* arg)
{
	uint32_t flags;
	while(1)
	{
		//osEventFlagsWait(event_id, MASTER_FLAG, osFlagsWaitAny, osWaitForever);

		do
		{
			flags = osEventFlagsGet(event_id);
			osDelay(1);
		} while ((flags & 0x1) == 0);

		osEventFlagsClear(event_id, MASTER_FLAG);
		cnt_slave++;
	}
}

osThreadAttr_t slave_attr = {
		.priority = osPriorityHigh
};

int main(void)
{

	halSerialInit();
	osKernelInitialize();

	event_id = osEventFlagsNew(NULL);

	osThreadNew(Master, NULL, NULL);
	osThreadNew(Slave, NULL, &slave_attr);

	osKernelStart();

	while(1)
	{
	}
}
