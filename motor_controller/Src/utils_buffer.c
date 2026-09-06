/*
 * utils_buffer.c
 *
 *  Created on: May 24, 2026
 *      Author: wojci
 */
#include <string.h> //for memset()
#include "utils_buffer.h"

static volatile BufferElement_t _buffer[BUFFER_LEN];
static volatile int32_t _bufferPtr; // next element index
static volatile int32_t _bufferHead; // latest(actual) data index
static volatile int32_t _iteratorPtr;

void bufferInit()
{
	_bufferPtr = 0;
	_bufferHead = -1;
}

void bufferClear()
{
	_bufferPtr = 0;
	_bufferHead = -1;
	memset((void*)_buffer, 0, BUFFER_LEN*sizeof(BufferElement_t));
}

void bufferPut(BufferElement_t data)
{
	_buffer[_bufferPtr] = data;
	_bufferPtr++;
	if (_bufferPtr >= BUFFER_LEN)
	{
		_bufferPtr = 0;
	}

	if (_bufferPtr == _bufferHead + 1)
	{
		_bufferHead++;
		if (_bufferHead >= BUFFER_LEN - 1)
		{
			_bufferHead = -1;
		}
	}
}

void bufferIteratorRestart()
{
	_iteratorPtr = _bufferHead + 1;
}

uint32_t bufferIteratorNext(BufferElement_t* data)
{
	if (_iteratorPtr == _bufferPtr)
	{
		return 1; // All buffer data has been read
	}
	else
	{
		*data = _buffer[_iteratorPtr];
		_iteratorPtr++;
		if (_iteratorPtr >= BUFFER_LEN)
		{
			_iteratorPtr = 0;
		}
		return 0; // Can continue?
	}
}
