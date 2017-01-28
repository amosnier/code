#include "stopwatch.h"
#include <stdio.h>
#include <inttypes.h>
#include "stm32f7xx_hal.h"

static unsigned counter = 0;

void stopwatch_reset(void)
{
	counter = 0;
}

bool stopwatch_step(void)
{
	printf("time since start (ms): %" SCNu32 "\r\n", HAL_GetTick());
	if (++counter >= 8)
		return false;
	else
		return true;
}
