/*
 * utils_observer.c
 *
 *  Created on: May 30, 2026
 *      Author: wojci
 */

#include "utils_observer.h"

void observerInit(Observer_t* handle)
{
	handle->error_gain = 0.001;
	handle->damping = 60;
	handle->pulses_per_rev = 3840;
	handle->angle = 0;
	handle->speed = 0;
}
void observerStep(Observer_t* handle, int32_t encoder, float dt)
{
	float angle_pred = handle->angle + handle->speed * dt;
	float speed_pred = handle->speed * (1.0 - handle->damping * dt);

	float angle_err = (((float)(encoder))/handle->pulses_per_rev) - angle_pred;

	handle->angle = angle_pred + (handle->error_gain * angle_err);
	handle->speed = speed_pred + handle->error_gain * (angle_err)/dt;
}

float observerGetAngle(Observer_t* handle)
{
	return handle->angle;
}

float observerGetSpeed(Observer_t* handle)
{
	return handle->speed;
}
