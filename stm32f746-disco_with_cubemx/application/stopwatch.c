#include "stopwatch.h"
#include <stdio.h>
#include <inttypes.h>
#include "stm32f7xx_hal.h"
#include "console.h"

void stopwatch_start(void)
{
	printf("time since start: ");
	console_hide_cursor();
}

bool stopwatch_step(void)
{
	uint32_t ms = HAL_GetTick();

	uint32_t sec = ms / 1000;
	ms %= 1000;
	uint32_t mn = sec / 60;
	sec %= 60;
	uint32_t hours = mn / 60;
	mn %= 60;

	printf("%04" SCNu32 ":%02" SCNu32 ":%02" SCNu32 ".%03" SCNu32, hours, mn, sec, ms);
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b"); // back as many characters as forward
	return true;
}

void stopwatch_stop(void)
{
	printf("\r\n");
	console_show_cursor();
}
