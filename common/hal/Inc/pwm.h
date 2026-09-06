/*
 * pwm.h
 *
 *  Created on: May 17, 2026
 *      Author: wojci
 */

#ifndef PWM_H_
#define PWM_H_

#include "hal_common.h"
#include <stdint.h>

HAL_Status_t halPWMInit();
HAL_Status_t halPWMStop();
HAL_Status_t halPWMForward();
HAL_Status_t halPWMBackward();
HAL_Status_t halPWMSetDutyCycle(int32_t duty);
HAL_Status_t halPWMSetInterruptCallback(void (*callback)(void));

#endif /* PWM_H_ */
