/*
 * utils_regulators.c
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */

#include "utils_regulators.h"

static void _regulatorDirectReset(void*)
{

}

static void _regulatorDirectStep(void*, float, float, float)
{

}

static float _regulatorDirectGetOutput(void* handle)
{
	RegulatorDirectAttr_t* this = (RegulatorDirectAttr_t*)handle;
	return this->duty;
}

static void _regulatorDirectSetTarget(void* handle, float target)
{
	RegulatorDirectAttr_t* this = (RegulatorDirectAttr_t*)handle;
	this->duty = target;
}

void regulatorDirectInit(RegulatorDirectAttr_t* attr, RegulatorMethods_t* methods)
{
	attr->duty = 0.0f;
	methods->getOutput = _regulatorDirectGetOutput;
	methods->setTarget = _regulatorDirectSetTarget;
	methods->step = _regulatorDirectStep;
	methods->reset = _regulatorDirectReset;
}

