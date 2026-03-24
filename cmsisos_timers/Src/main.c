#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

static volatile osEventFlagsId_t event_id;
static volatile uint32_t cnt_periodic_callback;
static volatile uint32_t cnt_once_callback;
static volatile uint32_t cnt_master;
static volatile uint32_t cnt_slave;

static volatile osTimerId_t timer1;
static volatile osTimerId_t timer2;
static volatile osTimerId_t timer3;

void Master(void* arg)
{
	cnt_master++;
	osEventFlagsSet(event_id, 0x1);
	osDelay(400);
}

void PeriodicCallback(void* arg)
{
	cnt_periodic_callback++;
}

void OnceCallback(void* arg)
{
	cnt_once_callback++;
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

	timer1 = osTimerNew(Master, osTimerPeriodic, NULL, NULL);
	timer2 = osTimerNew(PeriodicCallback, osTimerPeriodic, NULL, NULL);
	timer3 = osTimerNew(OnceCallback, osTimerOnce, NULL, NULL);
	osThreadNew(Slave, NULL, NULL);

	osTimerStart(timer1, 1000);
	osTimerStart(timer2, 500);
	osTimerStart(timer3, 5000);

	osKernelStart();

	while(1)
	{
	}
}
