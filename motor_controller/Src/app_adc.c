/*
 * app_adc.c
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */

#include "app_adc.h"
#include "adc.h"

#include "FreeRTOS.h"
#include "timers.h"

static volatile float _x, _y, _ref_x, _ref_y;
static volatile int _calDone = 0;

static void _vTriggerADC(TimerHandle_t xTimer)
{
	halADCTrigger();
}

static void _adcCallback(uint32_t* data)
{
	if (_calDone == 0)
	{
		_ref_x = ((float)data[0])/2048.0;
		_ref_y = ((float)data[1])/2048.0;
		_calDone = 1;
	}
	_x = ((float)data[0])/2048.0 - _ref_x;
	_y = ((float)data[1])/2048.0 - _ref_y;
}

void appADCInit()
{
	halADCInit();
	TimerHandle_t xTriggerTimer = xTimerCreate("ADCTriggerTimer", pdMS_TO_TICKS(10), pdTRUE, NULL, _vTriggerADC);
	xTimerStart(xTriggerTimer, 0);

	halADCRegisterCallback(_adcCallback);
	halADCStartInterruptMode();
}

float appADCGetX()
{
	return _x;
}

float appADCGetY()
{
	return _y;
}

