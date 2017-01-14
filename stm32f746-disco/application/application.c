#include "console.h"

void application(void)
{
	console_init();
	console_print_welcome();
	console_start_rx();

	for (;;)
	{
		console_handle_rx_event();
	}
}
