#include "timebase.h"
#include "cmsis_os.h"

/*
 * A wrapper for osKernelGetTickCOunt from cmsis_os.h.
 * It is created to remove custom HAL (serial.c) dependency on
 * cmsis_os.h, so that the app remains portable
 */
uint32_t halGetTicks()
{
	return osKernelGetTickCount();
}
