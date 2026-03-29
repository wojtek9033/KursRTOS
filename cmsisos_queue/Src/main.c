#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmsis_os.h"
#include "serial.h"

#define QUEUE_SIZE 4

volatile static osMessageQueueId_t queue;

void Producer1(void* args)
{
	uint32_t cnt = 0;
	while(1)
	{
		osMessageQueuePut(queue, &cnt, 0U, osWaitForever);
		cnt++;

		osDelay(rand() % 500);
	}
}

void Producer2(void* args)
{
	uint32_t cnt = 1000;
	while(1)
	{
		osMessageQueuePut(queue, &cnt, 0U, osWaitForever);
		cnt++;

		osDelay(rand() % 500);
	}
}

void Consumer(void* args)
{
	uint32_t data;
	while(1)
	{
		osMessageQueueGet(queue, &data, 0U, osWaitForever);
		printf("%ld\r\n", data);
		osDelay(rand() % 500);
	}
}

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	queue = osMessageQueueNew(QUEUE_SIZE, sizeof(uint32_t), NULL);

	osThreadNew(Producer1, NULL, NULL);
	osThreadNew(Producer2, NULL, NULL);
	osThreadNew(Consumer, NULL, NULL);

	printf("System ready \r\n");

	osKernelStart();

	while(1)
	{
	}
}
