#include <stdint.h>
#include "cmsis_os.h"

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
	osKernelInitialize();

	osThreadNew(Task1, NULL, NULL);
	osThreadNew(Task2, NULL, NULL);


	osKernelStart();

	while(1)
	{
	}
}
