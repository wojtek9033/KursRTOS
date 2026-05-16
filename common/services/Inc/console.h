#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "services_common.h"
#include <stdint.h>

ServiceStatus_t srvConsoleInit();
ServiceStatus_t srvConsolePrint(const char* line, int32_t timeout_ms);

#endif
