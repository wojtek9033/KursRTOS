/*
 * utils_observer.h
 *
 *  Created on: May 30, 2026
 *      Author: wojci
 */


#ifndef UTILS_OBSERVER_H_
#define UTILS_OBSERVER_H_

#include <stdint.h>

typedef struct
{
	float error_gain;
	float damping;
	float angle;
	float speed;
	int pulses_per_rev;
} Observer_t;

void observerInit(Observer_t* handle);
void observerStep(Observer_t* handle, int32_t encoder,  float dt);
float observerGetAngle(Observer_t* handle);
float observerGetSpeed(Observer_t* handle);

#endif
