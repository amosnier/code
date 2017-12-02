#include <stddef.h>
#include <stdbool.h>

#include "stm32f4xx_hal.h"

#include "scheduler.h"

#define MAX_SCHEDULED 1		/* Maximum number of scheduled functions */

struct function {
	void (*f)(void);
	uint32_t period;
	uint32_t latest;
};

static struct function functions[MAX_SCHEDULED];
static size_t nr_scheduled = 0;

/**
 * @brief SysTick ISR
 * @note  Only referred to from assembly startup file, visible for the linker
 *        but not actually part of the module's interface (not declared in the
 *        header file).
 * @note  The function is originally moved from the ST ISR file template, the
 *        function name is kept from there.
 */
void SysTick_Handler(void)
{
	for (int i = 0; i < MAX_SCHEDULED; i++) {
		struct function *p = &functions[i];
		uint32_t now = HAL_GetTick();
		if (now - p->latest >= p->period) {
			p->latest = now;
			p->f();
		}
	}
	HAL_IncTick(); /* The HAL and we need this! */
}

/**
 * @brief Schedule a function to run to completion a regular intervals
 * @param period: period in ms (run function every period ms)
 * @note  This function does not provide any overrun checking.
 * @note  This function shall be invoked before the start of the SysTick timer
 */
void schedule(void (f)(void), uint32_t period)
{
	assert_param(nr_scheduled < MAX_SCHEDULED);
	assert_param(HAL_GetTick() == 0);

	struct function *p = &functions[nr_scheduled++];
	p->f = f;
	p->period = period;
	/* Initiate the latest running time to "a long time ago", in order for
	 * the function to run immediately when the SysTick timer starts. From
	 * the perspective of time = 0, time = 1 is as far back as it gets
	 * (unsigned integers wrap around).
	 */
	p->latest = 1;
}
