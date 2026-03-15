#include "cmsis_os.h"

static volatile uint32_t cnt1 = 0;
static volatile uint32_t cnt2 = 0;

void Task1(void* args)
{
	while(1)
	{
		cnt1++;
		osThreadYield();
	}
}

void Task2(void* args)
{
	while(1)
	{
		cnt2++;
		osThreadYield();
	}
}

int main()
{
	osKernelInitialize();

	osThreadNew(Task1, NULL, NULL);
	osThreadNew(Task2, NULL, NULL);

	osKernelStart();

	while(1)
	{

	}

	return 0;
}
