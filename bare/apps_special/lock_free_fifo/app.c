#include <stdbool.h>

#include "led.h"
#include "clock_init.h"

int main(void)
{
	bool error = false;

	clock_init();

	Led_TypeDef led = error ? LED_RED : LED_GREEN;

	BSP_LED_Init(led);

	for (;;) {
		BSP_LED_Toggle(led);
		HAL_Delay(1000); // ms
	}
}
