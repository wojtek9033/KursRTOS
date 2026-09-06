/*
 * encoder.h
 *
 *  Created on: May 20, 2026
 *      Author: wojci
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "hal_common.h"
#include <stdint.h>

HAL_Status_t halEncoderInit();
HAL_Status_t halEncoderRegisterCallback(void (*callback)(int32_t)); //signed to determine direction

#endif /* ENCODER_H_ */
