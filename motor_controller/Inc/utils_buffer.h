/*
 * utils_buffer.h
 *
 *  Created on: May 24, 2026
 *      Author: wojci
 */

#ifndef UTILS_BUFFER_H_
#define UTILS_BUFFER_H_

#include <stdint.h>

#define BUFFER_LEN 8192

typedef struct
{
	int32_t encoder_data;
	int32_t angle;
	int32_t speed;
} BufferElement_t;

void bufferInit();
void bufferClear();
void bufferPut(BufferElement_t data);
void bufferIteratorRestart();
uint32_t bufferIteratorNext(BufferElement_t* data);

#endif /* UTILS_BUFFER_H_ */
