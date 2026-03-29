#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmsis_os.h"
#include "serial.h"

#define QUEUE_SIZE 4

volatile static uint32_t queue[QUEUE_SIZE];
volatile static uint32_t queue_pos = 0;
volatile static uint32_t queue_err_full = 0;
volatile static uint32_t queue_err_empty = 0;

volatile osMutexId_t queue_mutex;
volatile osSemaphoreId_t queue_semaphore_filled;
volatile osSemaphoreId_t queue_semaphore_empty;

void queue_put(uint32_t data)
{
	osMutexAcquire(queue_mutex, osWaitForever);
	if (queue_pos < QUEUE_SIZE)
	{
		queue[queue_pos] = data;
		queue_pos++;
		queue_err_full = 0;
	}
	else
	{
		queue_err_full = 1;
	}
	osMutexRelease(queue_mutex); // if forgot or in wrong place, system will hang
}

uint32_t queue_pop()
{
	osMutexAcquire(queue_mutex, osWaitForever);
	uint32_t data = 0;
	if (queue_pos > 0)
	{
		data = queue[--queue_pos];
		queue_err_empty = 0;
	}
	else
	{
		queue_err_empty = 1;
		data = 0;
	}
	osMutexRelease(queue_mutex);
	return data;
}

void Producer(void* args)
{
	uint32_t cnt = 0;
	while(1)
	{
		osSemaphoreAcquire(queue_semaphore_filled, osWaitForever);
		/*
		 * with this semaphore filled, the producer can start its work only after
		 * some tokens became available - consumer popped (processed) data from queue.
		 * Logic: Can not put more data, if consumer did not release tokens - meaning
		 * it is not "full of work"
		 */
		if (queue_err_full == 0)
		{
			queue_put(cnt);
			cnt++;
			osSemaphoreRelease(queue_semaphore_empty);
			/*
			 * Produces puts tokens to semaphore empty, meaning "hey, I already produced some data"
			 */
		}

		osDelay(rand() % 300);
		/*
		 * in scenario where Producer puts data every 1 second, while the consumer
		 * tries constantly to pop the queue (it is empty before put), the empty
		 * flag is almost always true
		 */
	}
}

void Consumer(void* args)
{
	while(1)
	{
		osSemaphoreAcquire(queue_semaphore_empty, osWaitForever);
		/*
		 * with this semaphore empty, the consumer can start its work only after
		 * some tokens became available - producer has put the data into queue.
		 * Logic: Can not process data, if it is not available
		 */
		if (queue_err_empty == 0)
		{
			uint32_t data = queue_pop();
			printf("%ld\r\n", data);
		}
		osDelay(rand() % 900);
		osSemaphoreRelease(queue_semaphore_filled);
		/*
		 * Consumer puts tokens to semaphore filled, meaning "hey, I am done with processing"
		 */
	}
}

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	queue_mutex = osMutexNew(NULL);
	queue_semaphore_empty = osSemaphoreNew(QUEUE_SIZE, 0, NULL);
	queue_semaphore_filled = osSemaphoreNew(QUEUE_SIZE, QUEUE_SIZE, NULL);
	osThreadNew(Producer, NULL, NULL);
	osThreadNew(Consumer, NULL, NULL);

	printf("System ready \r\n");

	osKernelStart();

	while(1)
	{
	}
}
