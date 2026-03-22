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

int main(void)
{
	/*
	 * TaskFun_Args_t task1_args;
	 * TaskFun_Args_t task2_args;
	 *
	 * This two must not be local, since RTOS reqiores:
	 * 	"Data passed by void* args must exist through entire life of a task"
	 *
	 * After osKernelStart();
	 * System goes under control of RTOS, and main() "stops beeing program's main point"
	 * so scheduler switches tasks and STACK of main() might be overwritten.
	 *
	 * This might work but it is not a guarantee in embedded world. SO AVOID.
	 *
	 * Rule:
	 * 	Do not ever pass a local variable to a task that lives longer than the variable scope
	 * 	Local variables leave on the STACK.
	 * 	Global variables & dynamically allocated memory lives on the HEAP.
	 */

	halSerialInit();
	osKernelInitialize();

	task1_args.ptr = &cnt1;
	task1_args.step = 1;

	task2_args.ptr = &cnt2;
	task2_args.step = 100;

	osThreadNew(TaskFun, &task1_args, NULL);
	osThreadNew(TaskFun, &task2_args, NULL);

	printf("System ready \r\n");

	osKernelStart();

	while(1)
	{
	}
}
