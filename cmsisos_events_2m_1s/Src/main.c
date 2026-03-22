#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

/*
 * This showcases task synchronization between two masters and one slave
 * Master2 (faster) waits for Slave for the SLAVE2_FLAG, which is dependent
 * on the Task 1 (slower)
 */

#define MASTER1_FLAG (1 << 0)
#define MASTER2_FLAG (1 << 1)
#define SLAVE1_FLAG   (1 << 2)
#define SLAVE2_FLAG   (1 << 3)

static volatile osEventFlagsId_t event_id;
static volatile uint32_t cnt_master1;
static volatile uint32_t cnt_master2;
static volatile uint32_t cnt_slave;

void Master1(void* arg)
{
	while(1)
	{
		osDelay(1000);
		cnt_master1++;
		osEventFlagsSet(event_id, MASTER1_FLAG);
		osEventFlagsWait(event_id, SLAVE1_FLAG, osFlagsWaitAny, osWaitForever);
	}
}

void Master2(void* arg)
{
	while(1)
	{
		osDelay(500);
		cnt_master2++;
		osEventFlagsSet(event_id, MASTER2_FLAG);
		osEventFlagsWait(event_id, SLAVE2_FLAG, osFlagsWaitAny, osWaitForever);
	}
}

void Slave(void* arg)
{
	while(1)
	{
		osEventFlagsWait(event_id, MASTER1_FLAG | MASTER2_FLAG, osFlagsWaitAll, osWaitForever);
		cnt_slave++;

		osEventFlagsSet(event_id, SLAVE1_FLAG | SLAVE2_FLAG);
	}
}

int main(void)
{

	halSerialInit();
	osKernelInitialize();

	event_id = osEventFlagsNew(NULL);

	osThreadNew(Master1, NULL, NULL);
	osThreadNew(Master2, NULL, NULL);
	osThreadNew(Slave, NULL, NULL);

	osKernelStart();

	while(1)
	{
	}
}
