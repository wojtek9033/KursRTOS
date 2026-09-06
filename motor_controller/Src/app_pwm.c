/*
 * app_pwm.c
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */

#include <stdint.h>

#include "app_pwm.h"
#include "pwm.h"

void appPWMInit()
{
	halPWMInit();
	halPWMForward();
	halPWMSetDutyCycle(0);
}
void appPWMSetCallback(void (*callback)(void))
{
	halPWMSetInterruptCallback(callback);
}

void appPWMSetDuty(float duty)
{
	int32_t duty_int = (int32_t)(duty*1000);
	halPWMSetDutyCycle(duty_int);
}

