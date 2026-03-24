#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

/*
 * This showcases a race condition - two tasks are trying to increment the same vairable.
 * The clue here is that cnt++ is not a atomic operation (in assembly, it is 5 cpu instructions).
 * Context switch can happen at any point of thease 5 instructions. This can lead to a situation
 * that both tasks are writting the exact same value to the counter (for instance, task1 read cnt
 * value, then the context has been switched to task2, task2 read cnt value, added 1 and wrote it
 * back, then, task1 added 1 to the value that has been read before task2 - the same value written
 * to cnt two times). So running this without mutex leads to cnt beeing lest than 200000.
 */

static volatile uint32_t cnt;
static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

static volatile osMutexId_t mutex;

void Task1(void* args)
{
	while(1)
	{
		cnt1++;
		if (cnt1 <= 100000)
		{
			osMutexAcquire(mutex, osWaitForever);
			cnt++;
			osMutexRelease(mutex);
		}
	}
}

void Task2(void* args)
{
	while(1)
	{
		cnt2++;
		if (cnt2 <= 100000)
		{
			osMutexAcquire(mutex, osWaitForever);
			cnt++;
			osMutexRelease(mutex);
		}
	}
}

int main(void)
{
	halSerialInit();
	osKernelInitialize();

	mutex = osMutexNew(NULL);

	osThreadNew(Task1, NULL, NULL);
	osThreadNew(Task2, NULL, NULL);

	printf("System ready \r\n");

	osKernelStart();

	while(1)
	{
	}
}
