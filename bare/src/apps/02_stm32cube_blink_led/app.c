#include "led.h"

static void busy_wait(void);

int main()
{
	BSP_LED_Init(LED_ORANGE);
	for (;;) {
		BSP_LED_Toggle(LED_ORANGE);
		busy_wait();
	}
}

static void busy_wait(void)
{
	for (int i = 0; i < 1000000; i++)
		;
}
