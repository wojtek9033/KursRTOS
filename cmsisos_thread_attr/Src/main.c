#include <stdint.h>
#include <stdio.h>
#include "cmsis_os.h"
#include "serial.h"

static volatile uint32_t cnt1;
static volatile uint32_t cnt2;

typedef struct {

	uint32_t* ptr;
	uint32_t step;

} TaskFun_Args_t;

void TaskFun(void* args)
{
	// cast to data type we know we will pass to this func
	TaskFun_Args_t* task_args = (TaskFun_Args_t*)args;
	uint32_t* ptr = task_args->ptr;
	uint32_t step = task_args->step;

	while(1)
	{
		(*ptr) += step;
	}
}

TaskFun_Args_t task1_args;
TaskFun_Args_t task2_args;

osThreadAttr_t task1_attr = {
	.name = "Task1"
};

osThreadAttr_t task2_attr = {
	.name = "Task2"
};


int main(void)
{

	halSerialInit();
	osKernelInitialize();

	task1_args.ptr = &cnt1;
	task1_args.step = 1;

	task2_args.ptr = &cnt2;
	task2_args.step = 100;

	osThreadNew(TaskFun, &task1_args, &task1_attr);
	osThreadNew(TaskFun, &task2_args, &task2_attr);

	printf("System ready \r\n");

	osKernelStart();

	while(1)
	{
	}
}
