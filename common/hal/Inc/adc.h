/*
 * adc.h
 *
 *  Created on: May 16, 2026
 *      Author: wojci
 */

#ifndef ADC_H_
#define ADC_H_

#include "hal_common.h"
#include <stdint.h>

HAL_Status_t halADCInit(void);
HAL_Status_t halADCRead(uint32_t* data); // read data Analog -> DC (4 channels)
HAL_Status_t halADCTrigger(void); // asynchronously trigger ADC conversion
HAL_Status_t halADCRegisterCallback(void (*callback)(uint32_t*)); // callback for interrupt from ADC
HAL_Status_t halADCSetInterruptPriority(uint32_t priority);
HAL_Status_t halADCStartInterruptMode(void);

#endif /* ADC_H_ */
