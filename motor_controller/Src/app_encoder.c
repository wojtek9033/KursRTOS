/*
 * app_encoder.c
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */
#include <stdint.h>

#include "app_encoder.h"
#include "encoder.h"

static volatile int32_t _encoderCnt = 0;

static void _encoderCallback(int32_t dir)
{
	_encoderCnt += dir;
}

void appEncoderInit()
{
	halEncoderInit();
	halEncoderRegisterCallback(_encoderCallback);
}
int32_t appEncoderRead()
{
	return _encoderCnt;
}
