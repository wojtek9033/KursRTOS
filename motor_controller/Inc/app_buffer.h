/*
 * app_buffer.h
 *
 *  Created on: May 24, 2026
 *      Author: wojci
 */

#ifndef APP_BUFFER_H_
#define APP_BUFFER_H_

#include <stdint.h>

#include "utils_buffer.h"

void appBufferInit();
void appBufferClear();
void appBufferPrint();
void appBufferPut(BufferElement_t data);

#endif /* APP_BUFFER_H_ */
