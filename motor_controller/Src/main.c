#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "console.h"

#include "app_pwm.h"
#include "app_adc.h"
#include "app_encoder.h"
#include "app_control.h"
#include "app_logic.h"
#include "app_buffer.h"

int main(void)
{
	srvConsoleInit();

	appBufferInit();
	appPWMInit();
	appADCInit();
	appEncoderInit();
	appControlInit();
	appLogicInit();

	appLogicStart();

	while (1)
	{

	}
}
