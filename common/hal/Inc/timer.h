#ifndef _TIMER_H
#define _TIMER_H

#include "hal_common.h"
#include <stdint.h>

HAL_Status_t halTimerInit(void);
HAL_Status_t halTimerStart(void);
HAL_Status_t halTimerSetInterruptPriority(uint32_t priority);
HAL_Status_t halTimerRegisterCallback(void (*callback) (void));

#endif
