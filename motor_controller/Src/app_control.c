/*
 * app_control.c
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "app_adc.h"
#include "app_pwm.h"
#include "app_control.h"
#include "app_buffer.h"
#include "app_encoder.h"

#include "utils_regulators.h"
#include "utils_observer.h"

/* Handles to actually running regulator */
static volatile RegulatorMethods_t* _regulatorMethods;
static void* _regulatorAttr = NULL;

/* Simple demo regulator input -> output */
static volatile RegulatorDirectAttr_t _regulatorDirectAttr;
static volatile RegulatorMethods_t _regulatorDirectMethods;
static volatile int _joystickEnabled;
static volatile int _bufferEnabled;

static volatile EventGroupHandle_t _xControlTrigger;
static volatile uint32_t _controlLoopCnt;

static volatile Observer_t _observer;

static volatile void _vControlLoopTask(void* pvParameters)
{
	while(1)
	{
		xEventGroupWaitBits(_xControlTrigger, 1, pdTRUE , pdFALSE, portMAX_DELAY);
		_controlLoopCnt++;

		float dt = 0.5e-3;
		int32_t encoder = appEncoderRead();
		observerStep(&_observer, encoder, dt);

		if (_bufferEnabled)
		{
			BufferElement_t data =
			{
				.encoder_data = encoder,
				.angle = (int32_t)(10000*observerGetAngle(&_observer)),
				.speed = (int32_t)(10000*observerGetSpeed(&_observer))
			};
			appBufferPut(data);
		}

		if (_joystickEnabled)
		{
			float target = appADCGetX();
			_regulatorMethods->setTarget(_regulatorAttr, target);
		}
		_regulatorMethods->step(_regulatorAttr, observerGetAngle(&_observer), observerGetSpeed(&_observer), dt);
		float duty = _regulatorMethods->getOutput(_regulatorAttr);
		appPWMSetDuty(duty);
	}
}

static volatile void _pwmCallback()
{
	BaseType_t xHigherTaskWoken = pdFALSE;
	xEventGroupSetBitsFromISR(_xControlTrigger, 1, &xHigherTaskWoken);

	portYIELD_FROM_ISR(xHigherTaskWoken);
}

void appControlInit()
{
	_joystickEnabled = 1;
	_bufferEnabled = 0;

	observerInit(&_observer);

	regulatorDirectInit(&_regulatorDirectAttr, &_regulatorDirectMethods);

	_regulatorMethods = &_regulatorDirectMethods;
	_regulatorAttr = &_regulatorDirectAttr;

	appPWMSetCallback(_pwmCallback);
	_xControlTrigger = xEventGroupCreate();
	xTaskCreate(_vControlLoopTask, "ControlLoopTask", 128, NULL, 2, NULL);
}

void appControlSetRegulatorDirect()
{
	_regulatorMethods = &_regulatorDirectMethods;
	_regulatorAttr = &_regulatorDirectAttr;

	_regulatorMethods->reset(_regulatorAttr);
}
void appControlSetRegulatorTarget(float target)
{
	_regulatorMethods->setTarget(_regulatorAttr, target);
}
void appControlJoystickEnable()
{
	_joystickEnabled = 1;
}
void appControlJoystickDisable()
{
	_joystickEnabled = 0;
}

void appControlBufferEnable()
{
	_bufferEnabled = 1;
}

void appControlBufferDisable()
{
	_bufferEnabled = 0;
}
