#include "led.h"
#include "scheduler.h"

#include "mcu_init.h"

static void toggle(void);

int main(void)
{
	schedule(toggle, 1000 /* ms */);
	mcu_init();
	BSP_LED_Init(LED_ORANGE);
	for (;;) {
	}
}

static void toggle(void)
{
	BSP_LED_Toggle(LED_ORANGE);
}
