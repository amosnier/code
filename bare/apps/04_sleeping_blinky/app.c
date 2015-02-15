#include "led.h"
#include "clock_init.h"

int main(void)
{
	clock_init();
	BSP_LED_Init(LED_ORANGE);
	for (;;) {
		BSP_LED_Toggle(LED_ORANGE);
		HAL_Delay(1000); // ms
	}
}
