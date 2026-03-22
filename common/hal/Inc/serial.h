#ifndef _SERIAL_H
#define _SERIAL_H

#include "hal_common.h"
#include <stdint.h>

HAL_Status_t halSerialInit(void);
HAL_Status_t halSerialPut(const char data);
HAL_Status_t halSerialPut_Timeout(const char data, uint32_t timeout);
HAL_Status_t halSerialSend(const char* txt);
HAL_Status_t halSerialSend_Timeout(const char* txt, uint32_t timeout);

#endif
