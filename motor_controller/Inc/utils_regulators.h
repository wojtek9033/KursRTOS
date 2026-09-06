/*
 * utils_regulators.h
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */

#ifndef UTILS_REGULATORS_H_
#define UTILS_REGULATORS_H_


// container for different control methods, aka class/object
typedef struct
{
	void (*reset)(void*);
	void (*step)(void*, float, float, float);
	float(*getOutput)(void*);
	void (*setTarget)(void*, float);
} RegulatorMethods_t;

typedef struct
{
	float duty;
} RegulatorDirectAttr_t;

void regulatorDirectInit(RegulatorDirectAttr_t * attr, RegulatorMethods_t* methods);

#endif /* UTILS_REGULATORS_H_ */
