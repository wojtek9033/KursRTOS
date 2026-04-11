#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdint.h>
#include "hal_common.h"

HAL_Status_t halButtonInit(void);
HAL_Status_t halButtonGetState(uint32_t *state);

#endif
